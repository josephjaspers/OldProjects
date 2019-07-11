/*
 * BC_Tensor_Base.h
 *
 *  Created on: Dec 12, 2017
 *      Author: joseph
 */

#ifndef TENSOR_LV4_CORE_H_
#define TENSOR_LV4_CORE_H_

#include "Tensor_Lv3_Array_Utility.h"
#include "Tensor_Lv3_Expr_Utility.h"

namespace BC {

	template<class,class>
	struct unaryExpression_negation;

template<
class T,										//The internal array type
class derived,									//The derived class
class math_lib,					    		    //Math_library
class inner_shape,
class outer_shape = typename DEFAULT_LD<inner_shape>::type
>
struct Tensor_Core :

		MTF::IF_ELSE<MTF::AND<Tensor_FunctorType<T>::supports_utility_functions, MTF::isPrimitive<T>::conditional>::conditional,								//if supports_utility_functions
		BC_Tensor_Utility_Array<T, derived, math_lib, inner_shape, outer_shape>,						//		inherit from Utility_Array
		BC_Tensor_Utility_Expression<T, derived, math_lib, inner_shape, outer_shape>>::type				//else
																										//		inherit from Utility_expression
	{
	using this_type    = derived;
	using functor_type = typename  Tensor_Type<T, derived, math_lib, Tensor_Shape<inner_shape, outer_shape>>::functor_type;
	using parent_class =
					typename MTF::IF_ELSE<MTF::AND<Tensor_FunctorType<T>::supports_utility_functions, MTF::isPrimitive<T>::conditional>::conditional,								//if supports_utility_functions
					BC_Tensor_Utility_Array<T, derived, math_lib, inner_shape, outer_shape>,						//		inherit from Utility_Array
					BC_Tensor_Utility_Expression<T, derived, math_lib, inner_shape, outer_shape>>::type;			//else


	/*
	 * What's happening?
	 *
	 * 	Each of these pointwise operator accepts a Tensor_Base<U (anytype), deriv (any derived), math_lib(same), dimensions...(same)>
	 *  and returns a derived class of type binary_expression<T, math_function, functor_type, param::functor_type>.
	 *
	 *  The replace_front metatemplate function is called to assist in the conversion from type T to binary_expression.
	 *  IE Vector<T, 100> will be replaced to Vector<bin_expr, 100>.
	 */

	template<class... params>  Tensor_Core(const params&...  p) : parent_class(p...) {}
	Tensor_Core() = default;


	Tensor_Core(std::initializer_list<int> inner) : parent_class(nullptr) {
		this->initInner(inner);
		this->initOuter(inner);
		math_lib::initialize(this->array, this->size());
	}

	template<class U, class alt_LD, class deriv>
	derived& operator = (const Tensor_Core<U, deriv, math_lib, inner_shape, alt_LD>& tensor) {
		math_lib::copy(this->data(), tensor.data(), this->size());
		return static_cast<derived&>(*this);
	}
private:
	template<class U, class deriv, class ld>
	struct param_types {
		using core_type  = Tensor_Core<U, derived, math_lib, inner_shape, ld>;


		using add = typename BC_Substitute_Type::Identity<binary_expression<T, BC::add, functor_type, typename core_type::functor_type>, this_type>::type;
		using sub = typename BC_Substitute_Type::Identity<binary_expression<T, BC::sub, functor_type, typename core_type::functor_type>, this_type>::type;
		using div = typename BC_Substitute_Type::Identity<binary_expression<T, BC::div, functor_type, typename core_type::functor_type>, this_type>::type;
		using mul = typename BC_Substitute_Type::Identity<binary_expression<T, BC::mul, functor_type, typename core_type::functor_type>, this_type>::type;

		using add_scal = typename BC_Substitute_Type::Identity<binary_expression_scalar_R<T, BC::add, functor_type, typename core_type::functor_type>, this_type>::type;
		using sub_scal = typename BC_Substitute_Type::Identity<binary_expression_scalar_R<T, BC::sub, functor_type, typename core_type::functor_type>, this_type>::type;
		using div_scal = typename BC_Substitute_Type::Identity<binary_expression_scalar_R<T, BC::div, functor_type, typename core_type::functor_type>, this_type>::type;
		using mul_scal = typename BC_Substitute_Type::Identity<binary_expression_scalar_R<T, BC::mul, functor_type, typename core_type::functor_type>, this_type>::type;

	};
public:

//	const auto operator - () const {
//		return typename BC_Substitute_Type::Identity<unaryExpression_negation<T, functor_type>,this_type>::type(this->data());
//	}

	template<class U, class deriv, class ld>
	typename param_types<U, deriv, ld>::add operator + (const Tensor_Core<U, deriv, math_lib, inner_shape, ld>& rv) {
		return typename param_types<U, deriv, ld>::add(this->data(), rv.data());
	}

	template<class U, class deriv, class ld>
	typename param_types<U, deriv, ld>::sub operator - (const Tensor_Core<U, deriv, math_lib, inner_shape, ld>& rv) {
		return typename param_types<U, deriv, ld>::sub(this->data(), rv.data());
	}

	template<class U, class deriv, class ld>
	typename param_types<U, deriv, ld>::div operator / (const Tensor_Core<U, deriv, math_lib, inner_shape, ld>& rv) {
		return typename param_types<U, deriv, ld>::div(this->data(), rv.data());
	}

	template<class U, class deriv, class ld>
	typename param_types<U, deriv, ld>::mul operator % (const Tensor_Core<U, deriv, math_lib, inner_shape, ld>& rv) {
		return typename param_types<U, deriv, ld>::mul(this->data(), rv.data());
	}
//Scalar methods

	template<class U, class deriv, class ld>
	typename param_types<U, deriv, ld>::add_scal operator + (const Tensor_Core<U, deriv, math_lib, Inner_Shape<1>, ld>& rv) {
		return typename param_types<U, deriv, ld>::add_scal(this->data(), rv.data());
	}

	template<class U, class deriv, class ld>
	typename param_types<U, deriv, ld>::add_scal operator - (const Tensor_Core<U, deriv, math_lib, Inner_Shape<1>, ld>& rv) {
		return typename param_types<U, deriv, ld>::add_scal(this->data(), rv.data());
	}

	template<class U, class deriv, class ld>
	typename param_types<U, deriv, ld>::add_scal operator / (const Tensor_Core<U, deriv, math_lib, Inner_Shape<1>, ld>& rv) {
		return typename param_types<U, deriv, ld>::add_scal(this->data(), rv.data());
	}

	template<class U, class deriv, class ld>
	typename param_types<U, deriv, ld>::add_scal operator % (const Tensor_Core<U, deriv, math_lib, Inner_Shape<1>, ld>& rv) {
		return typename param_types<U, deriv, ld>::add_scal(this->data(), rv.data());
	}
};
}

#endif /* TENSOR_LV4_CORE_H_ */



		//DEPRECATED CONSTRUCTORS + ASSIGNMENT OPERATORS
		//	Tensor_Base(      my_type&& tensor) : parent_class(tensor.data()) {}
		//	Tensor_Base(const my_type&  tensor) { (*this) = tensor; }
		//	Tensor_Base(      derived&& tensor) : parent_class(tensor.data()) {} //derived move
		//	Tensor_Base(const derived&  tensor) { (*this) = tensor; }			 //standard
		//
		//	template<class U>
		//	Tensor_Base(const typename BC_Substitute_Type::Identity<U, this_type>::type& tensor) { *this = tensor; };
		//	template<class U> Tensor_Base(const typename std::enable_if<false, typename BC_Substitute_Type::Identity<U, absolute_type>::type>::type& tensor) { *this = tensor; };
		//
		//
		//	this_type& operator = (my_type&& tensor) {
		//		functor_type tmp = this->data();
		//				this->array = tensor.data();
		//				tensor.array = tmp;
		//		return this->eval();
		//	}
		//
		//	template<class alt_outer>
		//	this_type& operator = (const typename Tensor_Base<T, derived, math_lib, inner_shape, alt_outer>::absolute_shape& tensor) {
		//		static_assert(grandparent_class::ASSIGNABLE, "is non assignable (use Eval() to evaluate expression-tensors)");
		//
		//		this->size() > 9999 ?
		//				math_lib::copy(this->data(), tensor.data(), this->size()) :
		//				math_lib::copy_single_thread(this->data(), tensor.data(), this->size());
		//
		//		return *this;
		//	}
		//
		//
		//	//This is protected from attempting to assign from a binary_expression because binary_expression tensors always have default LD
		//	template<class alt_outer> Tensor_Base(      typename Tensor_Base<T, derived, math_lib, inner_shape, alt_outer>::absolute_type&& tensor) { (*this) = tensor; }
		//	template<class alt_outer> Tensor_Base(const typename Tensor_Base<T, derived, math_lib, inner_shape, alt_outer>::absolute_type&  tensor) { (*this) = tensor; }


