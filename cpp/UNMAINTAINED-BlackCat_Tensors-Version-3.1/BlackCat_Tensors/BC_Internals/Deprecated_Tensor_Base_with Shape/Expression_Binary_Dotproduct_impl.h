/*
 * Expression_Binary_Dotproduct_impl.h
 *
 *  Created on: Jan 15, 2018
 *      Author: joseph
 */

#ifndef EXPRESSION_BINARY_DOTPRODUCT_IMPL_H_
#define EXPRESSION_BINARY_DOTPRODUCT_IMPL_H_

#include "Expression_Unary_MatrixTransposition.cu"
#include "Expression_Binary_Pointwise_Scalar.cu"
#include "Expression_Binary_Functors.cu"
#include "Expression_Binary_Pointwise_Same.cu"


#include "../BC_MetaTemplateFunctions/Adhoc.h"


namespace BC {

//forward decleration:
template<class T, class parent> struct unary_expression_transpose;

template<class T, class parent>
using transpose_flag = unary_expression_transpose<T, parent>;

//Adhoc - meta-template to determine if the array_type needs an evaluation
template<class T> struct needs_evaluation     { static constexpr bool conditional = true; };
template<class T> struct needs_evaluation<T*> { static constexpr bool conditional = false; };																	//
template<class T, class deriv>        struct needs_evaluation<expression<T, deriv>> { static constexpr bool conditional = true; };								//Is default array (already evaluated)
template<class T, class lv, class rv> struct needs_evaluation<binary_expression_scalar_R<T, mul, lv*, rv*>> { static constexpr bool conditional = false; };		//is a binary_expression (double already evaluated)
template<class T, class lv, class rv> struct needs_evaluation<binary_expression_scalar_L<T, mul, lv*, rv*>> { static constexpr bool conditional = false; };		//is a binary_expression (double already evaluated)
template<class T, class lv, class rv> struct needs_evaluation<binary_expression_scalar_R<T, mul, lv , rv*>> { static constexpr bool conditional = true; };		//is a binary_expression (expression by scalar)
template<class T, class lv, class rv> struct needs_evaluation<binary_expression_scalar_L<T, mul, lv*, rv >> { static constexpr bool conditional = true; };		//is a binary_expression (scalar by expression)

template<class T, class lv, class rv, class op> struct needs_evaluation<binary_expression<T, op, lv , rv*>> { static constexpr bool conditional = true; };		//is a binary_expression (expression by scalar)
template<class T, class lv, class rv, class op> struct needs_evaluation<binary_expression<T, op, lv*, rv >> { static constexpr bool conditional = true; };		//is a binary_expression (scalar by expression)
template<class T, class lv, class rv, class op> struct needs_evaluation<binary_expression<T, op, lv*, rv*>> { static constexpr bool conditional = true; };		//is a binary_expression (expression by scalar)

//The helper class that assists in extracting scalars (if there are scalar-expressions) and/or evaluating the array_types if need be
/*
 * The receiving class does not know who has ownership of the array (it may or may not) create a new array.
 * If it does than it should be destroyed (to avoid memleak).
 * This is the purpose of needs_evaluation<class...>. This determines if it was evaluated (and ergo, needs destruction)
 *
 * The class is (unfortunately) tightly coupled with the rest of the expression format in BlackCat_Tensors
 * However, it is able to easily evaluate other expressions (despite maybe losing a few performance points with custom-scalar-mat expressions)
 * But assuming we maintain scalar-mat/vector expressions from BlackCat_Tensors, the evaluation code it will be optimal
 */

//--------------------------------------------------------------Right Side MatrixMul Handler----------------------------------------------------------------------------//


//================ Expression =======================//

template<class T, class voider = void> struct extract_dp_Bside {
	static constexpr bool fast_trans = false;

	static const auto getScalar(const T ary) { return nullptr; }

	template<class ml> static const typename MTF::determine_scalar<T>::type* getArray(const T ary, int size, ml) {
		typename MTF::determine_scalar<T>::type* eval;
		ml::initialize(eval, size);
		ml::copy(eval, ary, size);
		return eval;

	}
};

//================ Normal Array =======================//

//Array (right)
template<class T> struct extract_dp_Bside<T*> {
	static constexpr bool fast_trans = false;

	static const auto getScalar(const T* ary) { return nullptr; }

	//The array_type is an expression -- evaluate the array
	template<class ml> static const T* getArray(const T* ary, int size,ml) {
		return ary;
	}
};

//================ Transposition =======================//

//Fast transpose (right) (generic)
template<class T, class parent> struct extract_dp_Bside<unary_expression_transpose<T, parent>> {
	static constexpr bool fast_trans = true;

	static const auto getScalar(const unary_expression_transpose<T, parent>& ary) { return nullptr; }

	//The array_type is an expression -- evaluate the array
	template<class ml> static const T* getArray(const unary_expression_transpose<T, parent>& param, int size,ml) {
		return param.root.data();
	}
};

//Fast Transpose // different type
template<class T, class U, class parent, class lv>
struct extract_dp_Bside<binary_expression_scalar_L<T, mul, lv, unary_expression_transpose<U, parent>>,
typename std::enable_if<MTF::isPrimitive<T>::conditional>::type> {
	static constexpr bool fast_trans = true;

	static const T* getScalar(const binary_expression_scalar_L<T, mul, lv, unary_expression_transpose<U, parent>>& param) {
		return param.left;
	}
	template<class ml> static const T* getArray (const binary_expression_scalar_L<T, mul, lv, unary_expression_transpose<U, parent>>& param, int size, ml) {
		return param.right.root.data();
	}
};

//transpose expression (super fast)
template<class T, class U, class parent, class rv>
struct extract_dp_Bside<binary_expression_scalar_R<T, mul, unary_expression_transpose<U, parent>, rv>,
typename std::enable_if<MTF::isPrimitive<T>::conditional>::type> {
	static constexpr bool fast_trans = true;

	static const T* getScalar(const binary_expression_scalar_R<T, mul, unary_expression_transpose<U, parent>, rv>& param) {
		return param.right;
	}
	template<class ml> static const T* getArray (const binary_expression_scalar_R<T, mul, unary_expression_transpose<U, parent>, rv>& param, int size, ml) {
		return param.left.root.data();
	}
};

//--------------------------------------------------------------Left Side MatrixMul Handler----------------------------------------------------------------------------//

//================ Defaults =======================//


//Expression (left)
template<class T, class voider = void> struct extract_dp {
	static constexpr bool fast_trans = false;

	static const auto getScalar(const T ary) {
		return nullptr;
	}

	//The array_type is an expression -- evaluate the array
	template<class ml> static const typename MTF::determine_scalar<T>::type* getArray(const T ary, int size, ml) {

		typename MTF::determine_scalar<T>::type* eval;
		ml::initialize(eval, size);
		ml::copy(eval, ary, size);

		return eval;
	}
};

//Array (left)
template<class T> struct extract_dp<T*> {
	static constexpr bool fast_trans = false;

	static const T* getScalar(const T* ary) { return nullptr; }

	//The array_type is an expression -- evaluate the array
	template<class ml> static const T* getArray(const T* ary, int size, ml) {
		return ary;
	}
};
//================Scalar Expression - Super Fast=======================//


//Scalar expression (right-hand fast)
template<class T, class lv, class rv> struct extract_dp<binary_expression_scalar_R<T, mul, lv*, rv>> {
	static constexpr bool fast_trans = false;

	static const auto getScalar(const binary_expression_scalar_R<T, mul, lv*, rv>& param) { return param.right; }
	template<class ml> static const lv* getArray(const binary_expression_scalar_R<T, mul, lv*, rv>& param, int size, ml) { return param.left; }
};

//Scalar expression (left-hand fast)
template<class T, class lv, class rv> struct extract_dp<binary_expression_scalar_L<T, mul, lv, rv*>> {
	static constexpr bool fast_trans = false;

	static const auto getScalar(const binary_expression_scalar_R<T, mul, lv, rv*>& param) { return param.left; }
	template<class ml> static const lv* getArray (const binary_expression_scalar_R<T, mul, lv, rv*>& param, int size, ml) { return param.right; }
};

//================Scalar Expression - Partial Fast=======================//

//Scalar expression (right-hand partial-fast)
template<class T, class lv, class rv> struct extract_dp<binary_expression_scalar_R<T, mul, lv, rv>> {
	static constexpr bool fast_trans = false;

	static const T* getScalar(const binary_expression_scalar_R<T, mul, lv, rv>& param) { return param.right; }
	template<class ml> static const typename MTF::determine_scalar<T>::type* getArray(const binary_expression_scalar_R<T, mul, lv, rv>& param, int size, ml) {

		typename MTF::determine_scalar<T>::type* eval;
		ml::initialize(eval, size);
		ml::copy(eval, param.left, size);

		return eval;
	}
};


//Scalar expression (left-hand partial-fast)
template<class T, class lv, class rv> struct extract_dp<binary_expression_scalar_L<T, mul, lv, rv>> {
	static constexpr bool fast_trans = false;

	static const T* getScalar(const binary_expression_scalar_R<T, mul, lv, rv>& param) {
		return param.left;
	}
	template<class ml> static const typename MTF::determine_scalar<T>::type* getArray (const binary_expression_scalar_R<T, mul, lv, rv>& param, int size, ml) {
		typename MTF::determine_scalar<T>::type* eval;
		ml::initialize(eval, size);
		ml::copy(eval, param.right, size);

		return eval;
	}
};

//================ Transposition =======================//


//transpose expression (super fast) //This gets disabled if its an expression at which point its faster just to evaluate
template<class T, class parent> struct extract_dp<unary_expression_transpose<T, parent>, typename std::enable_if<MTF::isPrimitive<T>::conditional>::type> {
	static constexpr bool fast_trans = true;

	static const T* getScalar(const unary_expression_transpose<T, parent>& param) {

		return nullptr;
	}
	template<class ml> static const T* getArray (const unary_expression_transpose<T, parent>& param, int size, ml) {
		return param.root.data();
	}
};

//================ Transposition * Scalar =======================//

//transpose expression (super fast)
template<class T, class parent, class lv>
struct extract_dp<binary_expression_scalar_L<T, mul, lv, unary_expression_transpose<T, parent>>,
std::enable_if<MTF::isPrimitive<T>::conditional::type>> {
	static constexpr bool fast_trans = true;

	static const T* getScalar(const binary_expression_scalar_L<T, mul, lv, unary_expression_transpose<T, parent>>& param) {
		return param.left;
	}
	template<class ml> static const T* getArray(const binary_expression_scalar_L<T, mul, lv, unary_expression_transpose<T, parent>>& param, int size, ml) {
		return param.right.root.data();
	}
};

//transpose expression (super fast)
template<class T, class parent, class rv>
struct extract_dp<binary_expression_scalar_R<T, mul, unary_expression_transpose<T, parent>, rv>,
std::enable_if<MTF::isPrimitive<T>::conditional::type>> {
	static constexpr bool fast_trans = true;

	static const T* getScalar(const binary_expression_scalar_R<T, mul, unary_expression_transpose<T, parent>, rv>& param) {
		return param.right;
	}
	template<class ml> static const T* getArray(const binary_expression_scalar_R<T, mul, unary_expression_transpose<T, parent>, rv>& param, int size, ml) {
		return param.left.root.data();
	}
};
}



#endif /* EXPRESSION_BINARY_DOTPRODUCT_IMPL_H_ */
