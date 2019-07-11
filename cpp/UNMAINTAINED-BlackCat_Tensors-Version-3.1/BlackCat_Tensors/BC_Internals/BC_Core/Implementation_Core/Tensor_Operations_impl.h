/*
 * Tensor_Core.h
 *
 *  Created on: Dec 30, 2017
 *      Author: joseph
 */

#ifndef TENSOR_HEAD_H_
#define TENSOR_HEAD_H_

//#include "../../BC_MetaTemplateFunctions/Adhoc.h"
//#include "BC_Expressions/Expression_Binary_Pointwise_Same.cu"
//#include "BC_Expressions/Expression_Binary_Functors.cu"
#include "../../BC_Expressions/Expression_Unary_Pointwise.cu"

namespace BC {

template<class, class> struct Scalar;
template<class, class> struct Vector;
template<class, class> struct Matrix;

template<class,class>struct Tensor_Operations_impl;

template<class A, class B>
struct alternate_asterix_denoter {
	//This class is returned from the overloaded unary (*) operator, we use it to create a secondary subset of operators IE **, %*
	const Tensor_Operations_impl<A, B>& ref;
	const Tensor_Operations_impl<A, B>& operator() () const { return ref; }
	const Tensor_Operations_impl<A, B>& get () const { return ref; }

	alternate_asterix_denoter(Tensor_Operations_impl<A, B>& r) : ref(r) {}
};

template<class derived, class TRAITS>
struct Tensor_Operations_impl {

	using evaluation_type 	= typename TRAITS::evaluation_type;		//The type returned when instant evaluation is required
	using functor_type 		= typename TRAITS::functor_type;		//The data-type passed to expressions
	using scalar_type 		= typename TRAITS::scalar_type;			//The array_type of GenuineTensors and the Evaluation Type for ExpressionTensors
	using math_library 		= typename TRAITS::math_library;

	using this_type = derived;
	using traits 	= TRAITS;

	template<class param_deriv, class param_traits, class functor>
	struct impl {
		//Determines the return type of pointwise operations
		static constexpr int SCALAR = 0;

		using param_functor_type = typename Tensor_Operations_impl<param_deriv, param_traits>::functor_type;

		using type =
				typename MTF::IF_ELSE<derived::RANK() != SCALAR && param_deriv::RANK() != SCALAR, //Neither are scalar
					typename MTF::expression_substitution<binary_expression<scalar_type, functor, functor_type, param_functor_type>, derived>::type,
					typename MTF::IF_ELSE<derived::RANK() == SCALAR && param_deriv::RANK() == SCALAR,
						typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, functor, functor_type, param_functor_type>, derived>::type,
						typename MTF::IF_ELSE<derived::RANK() == SCALAR,
							typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, functor, functor_type, param_functor_type>, derived    >::type,
							typename MTF::expression_substitution<binary_expression_scalar_R<scalar_type, functor, functor_type, param_functor_type>, param_deriv>::type
						>::type
					>::type
				>::type;

		using unary_type = typename MTF::expression_substitution<unary_expression<scalar_type, functor, functor_type>, derived>::type;
	};

	template<class param_deriv, class param_traits>
	struct dp_impl {
		//Determines the return type dotproducts (including pointwise scalar operations)
		using param_functor_type = typename Tensor_Operations_impl<param_deriv, param_traits>::functor_type;
		static constexpr bool lv_scalar = derived::RANK() == 0;
		static constexpr bool rv_scalar = param_deriv::RANK() == 0;
		static constexpr bool scalar_mul = lv_scalar || rv_scalar;
		using greater_type = typename MTF::IF_ELSE<(derived::RANK() > param_deriv::RANK()), derived, param_deriv>::type;
		using lesser_type = typename MTF::IF_ELSE<(derived::RANK() < param_deriv::RANK()), derived, param_deriv>::type;

		static constexpr int ORDER = scalar_mul ? greater_type::RANK() : derived::RANK() == 1 && param_deriv::RANK() == 1 ? 2 : lesser_type::RANK();

		static constexpr bool evaluate_to_vector = derived::RANK() == 2 && param_deriv::RANK() == 1;
		static constexpr bool evaluate_to_matrix = derived::RANK() == 2 && param_deriv::RANK() == 2;
		static constexpr bool evaluate_to_mat_vv = derived::RANK() == 1 && param_deriv::RANK() == 1;
		static constexpr bool evaluate_to_dominant = derived::RANK() == 0 || param_deriv::RANK() == 0;

		static constexpr bool short_params = lv_scalar || rv_scalar;

		using mulType      =   typename MTF::IF_ELSE<lv_scalar || rv_scalar,
									typename MTF::IF_ELSE<lv_scalar,
										typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, mul, functor_type, param_functor_type>, param_deriv>::type,
										typename MTF::expression_substitution<binary_expression_scalar_R<scalar_type, mul, functor_type, param_functor_type>, derived	 >::type
									>::type,
								void>::type;

		using vecType 		= 	typename MTF::IF_ELSE<evaluate_to_vector,
								typename MTF::expression_substitution<binary_expression_dotproduct<scalar_type, functor_type, param_functor_type, math_library>,param_deriv>::type, void>::type;

		using matType 		= 	typename MTF::IF_ELSE<evaluate_to_matrix,
								typename MTF::expression_substitution<binary_expression_dotproduct<scalar_type, functor_type, param_functor_type, math_library>,param_deriv>::type, void>::type;

		using outerType 	= 	typename MTF::IF_ELSE<evaluate_to_mat_vv,
								typename MTF::expression_substitution<binary_expression_dotproduct<scalar_type, functor_type, param_functor_type, math_library>,
								Matrix<functor_type, math_library>>::type, void>::type;

		using type 			= 	typename MTF::IF_ELSE<evaluate_to_vector, vecType,
									typename MTF::IF_ELSE<evaluate_to_matrix, matType,
										typename MTF::IF_ELSE<evaluate_to_mat_vv, outerType,
											typename MTF::IF_ELSE<evaluate_to_dominant, mulType, void
											>::type
										>::type
									>::type
								>::type;
		using expression_type = typename MTF::front<type>::type;
	};

	template<class deriv, class traits> void  assert_same_size(const Tensor_Operations_impl<deriv ,traits>& tensor) const {
#ifdef	BLACKCAT_TENSORS_ASSERT_VALID
		if ((asBase().size() != tensor.asBase().size()) && (this->asBase().RANK() != 0 && tensor.asBase().RANK() != 0)) {
			std::cout << "this_dims "; asBase().printDimensions();
			std::cout << "\n param_dims "; tensor.asBase().printDimensions();
			std::cout << "\n";
			throw std::invalid_argument("Tensor by Tensor operation - size mismatch - ");
		}
		assert_same_ml(tensor);
#endif
	}

	template<class deriv, class traits>
	void assert_same_ml(const Tensor_Operations_impl<deriv ,traits>& tensor) const {
#ifdef BLACKCAT_TENSORS_ASSERT_VALID
		static_assert(MTF::same<math_library, typename Tensor_Operations_impl<deriv,traits>::math_library>::conditional, "math_library must be identical");
#endif
	}

	//Returns the class returned as its most derived member
	const derived& asBase() const { return static_cast<const derived&>(*this); }
		  derived& asBase() 	  { return static_cast<	     derived&>(*this); }
	//Return expression or array of Tensor (both support iterating with bracket operator [])
	const functor_type& data() const { return static_cast<const derived&>(*this).array; }
		  functor_type& data()		 { return static_cast<		derived&>(*this).array; }
	//if it is not an expression Return the tensor as a reference to itself else return the evaluation of the tensor
	const evaluation_type eval() const;
		  evaluation_type eval();

	//dot_product type 1 -- cool thing there are two operator * overloads --> (if you add an arbitrary template param with a default, you can do in class specialization)
	//This is the overload that handles point-wise multiplication between scalars and tensors

	template<class pDeriv, class pTraits, class voider = typename std::enable_if<dp_impl<pDeriv,pTraits>::short_params || dp_impl<pDeriv,pTraits>::short_params>::type>
	typename dp_impl<pDeriv, pTraits>::type operator *(const Tensor_Operations_impl<pDeriv, pTraits>& param) const {
		if (dp_impl<pDeriv,pTraits>::short_params)
			return typename dp_impl<pDeriv, pTraits>::type(asBase().expression_packet(), this->data(), param.data());
		else
			return typename dp_impl<pDeriv, pTraits>::type(param.asBase().expression_packet(), this->data(), param.data());
	}

	/*
	 * a = M x K
	 * b = K x N
	 * c = M x N
	 */
	//Dot product
	template<class pDeriv, class pTraits,
		class voider = typename std::enable_if<!dp_impl<pDeriv,pTraits>::short_params && !dp_impl<pDeriv,pTraits>::short_params>::type, int foo = 0>
	typename dp_impl<pDeriv, pTraits>::type operator *(const Tensor_Operations_impl<pDeriv, pTraits>& param) const {
		assert_same_ml(param);
		return typename dp_impl<pDeriv, pTraits>::type(asBase().dotproduct_packet(dp_impl<pDeriv, pTraits>::ORDER, param.asBase().asShape()), this->data(), param.data(),
			asBase().rows(), param.asBase().cols(), asBase().cols(),
			asBase().LD_rows(), param.asBase().LD_rows(), 0);
	}

	//This allows you to do the operator ** as a point-wise multiplication operation
	const alternate_asterix_denoter<derived, TRAITS> operator * () const {
		return alternate_asterix_denoter<derived, TRAITS>(this);
	}
	 alternate_asterix_denoter<derived, TRAITS> operator * ()  {
		return alternate_asterix_denoter<derived, TRAITS>(*this);
	}
	//pointwise multiplication
	template<class pDeriv, class pTraits>
	typename impl<pDeriv, pTraits, mul>::type operator *(const alternate_asterix_denoter<pDeriv, pTraits>& param) const {
		assert_same_size(param.get());
		return typename impl<pDeriv, pTraits, mul>::type(asBase().expression_packet(), this->data(), param.get().data());
	}
	template<class pDeriv, class pTraits>
	typename impl<pDeriv, pTraits, assign>::type operator ==(const Tensor_Operations_impl<pDeriv, pTraits>& param) {
		assert_same_size(param);
		return typename impl<pDeriv, pTraits, assign>::type(asBase().expression_packet(), this->data(), param.data());
	}

	template<class pDeriv, class pTraits>	//creates an expression that allows you to chain together 2 pointwise operations (of the same size)
	typename impl<pDeriv, pTraits, combine>::type operator &&(const Tensor_Operations_impl<pDeriv, pTraits>& param) {
		assert_same_size(param);
		return typename impl<pDeriv, pTraits, combine>::type(asBase().expression_packet(), this->data(), param.data());
	}
	template<class pDeriv, class pTraits>
	derived& operator =(const Tensor_Operations_impl<pDeriv, pTraits>& param) {
		assert_same_size(param);
		math_library::copy(asBase().data(), param.asBase().data(), this->asBase().size());
		return static_cast<derived&>(*this);
	}

	template<class pDeriv, class pTraits>
	typename impl<pDeriv, pTraits, add>::type operator +(const Tensor_Operations_impl<pDeriv, pTraits>& param) const {
		assert_same_size(param);
		return typename impl<pDeriv, pTraits, add>::type(asBase().expression_packet(), this->data(), param.data());
	}
	template<class pDeriv, class pTraits>
	typename impl<pDeriv, pTraits, sub>::type operator -(const Tensor_Operations_impl<pDeriv, pTraits>& param) const {
		assert_same_size(param);
		return typename impl<pDeriv, pTraits, sub>::type(asBase().expression_packet(), this->data(), param.data());
	}
	template<class pDeriv, class pTraits>
	typename impl<pDeriv, pTraits, div>::type operator /(const Tensor_Operations_impl<pDeriv, pTraits>& param) const {
		assert_same_size(param);
		return typename impl<pDeriv, pTraits, div>::type(asBase().expression_packet(), this->data(), param.data());
	}
	template<class pDeriv, class pTraits>
	typename impl<pDeriv, pTraits, mul>::type operator %(const Tensor_Operations_impl<pDeriv, pTraits>& param) const {
		assert_same_size(param);
		return typename impl<pDeriv, pTraits, mul>::type(asBase().expression_packet(), this->data(), param.data());
	}
	template<class pDeriv, class pTraits>
	derived& operator +=(const Tensor_Operations_impl<pDeriv, pTraits>& param) {
		assert_same_size(param);
		return *this = typename impl<pDeriv, pTraits, add>::type(asBase().expression_packet(), this->data(), param.data());
	}
	template<class pDeriv, class pTraits>
	derived& operator -=(const Tensor_Operations_impl<pDeriv, pTraits>& param) {
		assert_same_size(param);
		return *this = typename impl<pDeriv, pTraits, sub>::type(asBase().expression_packet(), this->data(), param.data());
	}
	template<class pDeriv, class pTraits>
	derived& operator /=(const Tensor_Operations_impl<pDeriv, pTraits>& param) {
		assert_same_size(param);
		return *this = typename impl<pDeriv, pTraits, div>::type(asBase().expression_packet(), this->data(), param.data());
	}
	template<class pDeriv, class pTraits>
	derived& operator %=(const Tensor_Operations_impl<pDeriv, pTraits>& param) {
		assert_same_size(param);
		return *this = typename impl<pDeriv, pTraits, mul>::type(asBase().expression_packet(), this->data(), param.data());
	}
	//Lets you create custom expressions
	template<class functor>
	auto unExpr(functor f) const {
		return typename impl<derived, TRAITS, functor>::unary_type(asBase().expression_packet(), asBase().data());
	}
	template<class d2, class t2, class functor>
	auto binExpr(functor f, const Tensor_Operations_impl<d2, t2>& rv) {
		return typename impl<d2, t2, functor>::type(asBase().expression_packet(), asBase().data(), rv.asBase().data());
	}
	template<class functor>
	auto unExpr() const {
		return typename impl<derived, TRAITS, functor>::unary_type(asBase().expression_packet(), asBase().data());
	}
	template<class functor, class d2, class t2>
	auto binExpr(const Tensor_Operations_impl<d2, t2>& rv) {
		return typename impl<d2, t2, functor>::type(asBase().expression_packet(), asBase().data(), rv.asBase().data());
	}

	//These methods do no have any implementation. They are specifically used for std::declval to allow subclasses to get these types
	evaluation_type getEvaluation_type() 	const;
	functor_type 	getFunctor_type() 		const;
	scalar_type 	getScalar_type() 		const;
	math_library 	getMathLibrary_type() 	const;
	this_type 		getThis_type() 			const;
	traits 			getTraits_type() 		const;
};



}

#endif /* TENSOR_CORE_H_ */


//
////Matrix Vec mul
//	template<class U, int rows, class LD, class voider = std::enable_if<MTF::same<evaluation_type, derived&>::conditional>>
//	auto operator *(const vec<U, rows, math_library, LD>& param) const {
//
//		return typename
//		MTF::IF_ELSE<Identity::RANK == 2,
//				vec<
//					binary_expression_dotproduct<
//							scalar_type, functor_type, typename MTF::determine_functor<U>::type, math_library,
//							derived::COMPILE_TIME_ROWS(), derived::COMPILE_TIME_ROWS(), 1,  //dims
//							derived::COMPILE_TIME_ROWS(), rows, derived::COMPILE_TIME_LD_ROWS(),
//							derived::transposed(), false>,
//					derived::COMPILE_TIME_ROWS(), math_library, typename default_OS<math_library, derived::COMPILE_TIME_ROWS()>::type>,
//				void
//		>::type(this->data(), param.data());
//	}
//
//	//mat mat
//	template<class U, int rows, int cols, class LD>
//	auto operator *(const mat<U, rows, cols, math_library, LD>& param) const {
//		return typename
//		MTF::IF_ELSE<Identity::RANK == 2,
//				mat<
//					binary_expression_dotproduct<
//							scalar_type, functor_type, typename MTF::determine_functor<U>::type, math_library,
//							derived::COMPILE_TIME_ROWS(), derived::COMPILE_TIME_ROWS(), cols,  //dims
//							derived::COMPILE_TIME_ROWS(), rows, derived::COMPILE_TIME_LD_ROWS(),
//							derived::transposed(), false>,
//					derived::COMPILE_TIME_ROWS(), cols, math_library, typename default_OS<math_library, derived::COMPILE_TIME_ROWS(), cols>::type>,
//				void
//		>::type(this->data(), param.data());
//	}
//
//	//Mat by RowVec OR Vec by RowVec
//	template<class U, int cols, class LD>
//	auto operator *(const rowVec<U, cols, math_library, LD>& param) const {
//		return typename
//		MTF::IF_ELSE<true,
//				mat<
//					binary_expression_dotproduct<
//							scalar_type, functor_type, typename MTF::determine_functor<U>::type, math_library,	//Eval,type, left functor_Type, right functor_type,
//							derived::COMPILE_TIME_ROWS(), derived::COMPILE_TIME_ROWS(), cols,   //MNK
//							derived::COMPILE_TIME_ROWS(), cols, derived::COMPILE_TIME_LD_ROWS(), //LD
//							derived::transposed(), false>,
//					derived::COMPILE_TIME_ROWS(), cols, math_library, typename default_OS<math_library, derived::COMPILE_TIME_ROWS(), cols>::type>,
//				void
//		>::type(this->data(), param.data());
//	}
//
//	template<class U>
//	typename scalar_impl<U*>::add_expression operator +(const Scalar<U, math_library>& param) const {
//		return typename scalar_impl<U*>::add_expression(asBase().expression_packet(), this->data(), param.data());
//	}
//	template<class U>
//	typename scalar_impl<U*>::sub_expression operator -(const Scalar<U, math_library>& param) const {
//		return typename scalar_impl<U*>::sub_expression(asBase().expression_packet(), this->data(), param.data());
//	}
//	template<class U>
//	typename scalar_impl<U*>::div_expression operator /(const Scalar<U, math_library>& param) const {
//		return typename scalar_impl<U*>::div_expression(asBase().expression_packet(), this->data(), param.data());
//	}
//	template<class U>
//	typename scalar_impl<U*>::mul_expression operator %(const Scalar<U, math_library>& param) const {
//		return typename scalar_impl<U*>::mul_expression(asBase().expression_packet(), this->data(), param.data());
//	}
//
//	template<class U>
//	derived& operator +=(const Scalar<U, math_library>& param) {
//		asBase() = typename scalar_impl<U*>::add_expression(asBase().expression_packet(), this->data(), param.data());
//		return asBase();
//	}
//	template<class U>
//	derived& operator -=(const Scalar<U, math_library>& param) {
//		asBase() = typename scalar_impl<U*>::sub_expression(asBase().expression_packet(), this->data(), param.data());
//		return asBase();
//	}
//	template<class U>
//	derived& operator /=(const Scalar<U, math_library>& param) {
//		asBase() = typename scalar_impl<U*>::div_expression(asBase().expression_packet(), this->data(), param.data());
//		return asBase();
//	}
//	template<class U>
//	derived& operator %=(const Scalar<U, math_library>& param) {
//		asBase() = typename scalar_impl<U*>::mul_expression(asBase().expression_packet(), this->data(), param.data());
//		return asBase();
//	}
//
//	template<class U>
//	struct scalar_impl {
//			using add_expression = typename std::conditional<derived::RANK() == 0,
//				typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, add, functor_type, U>, derived>::type,
//				typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, add, functor_type, U>, derived>::type>::type;
//
//		using sub_expression = typename std::conditional<derived::RANK() == 0,
//				typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, sub, functor_type, U>, derived>::type,
//				typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, sub, functor_type, U>, derived>::type>::type;
//
//
//		using div_expression = typename std::conditional<derived::RANK() == 0,
//				typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, div, functor_type, U>, derived>::type,
//				typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, div, functor_type, U>, derived>::type>::type;
//
//		using mul_expression = typename std::conditional<derived::RANK() == 0,
//				typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, mul, functor_type, U>, derived>::type,
//				typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, mul, functor_type, U>, derived>::type>::type;
//
//	};


//
//		using sub_expression =
//				typename MTF::IF_ELSE<derived::RANK() != SCALAR && param_deriv::RANK() != SCALAR, //Neither are scalar
//						typename MTF::expression_substitution<binary_expression<scalar_type, sub, functor_type, param_functor_type>, derived>::type,
//						typename MTF::IF_ELSE<derived::RANK() == SCALAR && param_deriv::RANK() == SCALAR,
//							typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, sub, functor_type, param_functor_type>, derived>::type,
//								typename MTF::IF_ELSE<derived::RANK() == SCALAR,
//									typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, sub, functor_type, param_functor_type>, derived    >::type,
//									typename MTF::expression_substitution<binary_expression_scalar_R<scalar_type, sub, functor_type, param_functor_type>, param_deriv>::type
//							>::type
//						>::type
//				>::type;
//
//		using div_expression =
//				typename MTF::IF_ELSE<derived::RANK() != SCALAR && param_deriv::RANK() != SCALAR, //Neither are scalar
//						typename MTF::expression_substitution<binary_expression<scalar_type, div, functor_type, param_functor_type>, derived>::type,
//						typename MTF::IF_ELSE<derived::RANK() == SCALAR && param_deriv::RANK() == SCALAR,
//							typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, div, functor_type, param_functor_type>, derived>::type,
//								typename MTF::IF_ELSE<derived::RANK() == SCALAR,
//									typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, div, functor_type, param_functor_type>, derived    >::type,
//									typename MTF::expression_substitution<binary_expression_scalar_R<scalar_type, div, functor_type, param_functor_type>, param_deriv>::type
//							>::type
//						>::type
//				>::type;
//
//		using mul_expression =
//						typename MTF::IF_ELSE<derived::RANK() != SCALAR && param_deriv::RANK() != SCALAR, //Neither are scalar
//								typename MTF::expression_substitution<binary_expression<scalar_type, mul, functor_type, param_functor_type>, derived>::type,
//								typename MTF::IF_ELSE<derived::RANK() == SCALAR && param_deriv::RANK() == SCALAR,
//									typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, mul, functor_type, param_functor_type>, derived>::type,
//										typename MTF::IF_ELSE<derived::RANK() == SCALAR,
//											typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, mul, functor_type, param_functor_type>, derived    >::type,
//											typename MTF::expression_substitution<binary_expression_scalar_R<scalar_type, mul, functor_type, param_functor_type>, param_deriv>::type
//									>::type
//								>::type
//						>::type;

//	template<class param_deriv, class param_traits, class functor>
//	struct custom_impl {
//		static constexpr int SCALAR = 0;
//
//		//Determines the return type of Tensor by Tensor operations
//		using param_functor_type = typename Tensor_Operations_impl<param_deriv, param_traits>::functor_type;
//
//		using binary_type =
//				typename MTF::IF_ELSE<derived::RANK() != SCALAR && param_deriv::RANK() != SCALAR, //Neither are scalar
//						typename MTF::expression_substitution<binary_expression<scalar_type, functor, functor_type, param_functor_type>, derived>::type,
//						typename MTF::IF_ELSE<derived::RANK() == SCALAR && param_deriv::RANK() == SCALAR,
//							typename MTF::expression_substitution<binary_expression_scalar_LR<scalar_type, functor, functor_type, param_functor_type>, derived>::type,
//								typename MTF::IF_ELSE<derived::RANK() == SCALAR,
//									typename MTF::expression_substitution<binary_expression_scalar_L<scalar_type, functor, functor_type, param_functor_type>, derived    >::type,
//									typename MTF::expression_substitution<binary_expression_scalar_R<scalar_type, functor, functor_type, param_functor_type>, param_deriv>::type
//							>::type
//						>::type
//				>::type;
//
//		using unary_type = typename MTF::expression_substitution<unary_expression<scalar_type, functor, functor_type>, derived>::type;
//	};

//	//------------------- auto convert to scalar -----------------//
//	auto operator * (scalar_type scalar) const {
//		return (*this) * Scalar<scalar_type, math_library>(scalar);
//	}
//	auto operator + (scalar_type scalar) const {
//		return (*this) + Scalar<scalar_type, math_library>(scalar);
//	}
//	auto operator - (scalar_type scalar) const {
//		return (*this) - Scalar<scalar_type, math_library>(scalar);
//	}
//	auto operator / (scalar_type scalar) const {
//		return (*this) / Scalar<scalar_type, math_library>(scalar);
//	}
//	auto operator % (scalar_type scalar) const {
//		return (*this) % Scalar<scalar_type, math_library>(scalar);
//	}
//	auto& operator += (scalar_type scalar) const {
//		return (*this) += Scalar<scalar_type, math_library>(scalar);
//	}
//	derived& operator -= (scalar_type scalar) const {
//		return asBase() -= Scalar<scalar_type, math_library>(scalar);
//	}
//	derived& operator /= (scalar_type scalar) const {
//		return asBase() /= Scalar<scalar_type, math_library>(scalar);
//	}
//	auto& operator %= (scalar_type scalar) const {
//		return (*this) %= Scalar<scalar_type, math_library>(scalar);
//	}

