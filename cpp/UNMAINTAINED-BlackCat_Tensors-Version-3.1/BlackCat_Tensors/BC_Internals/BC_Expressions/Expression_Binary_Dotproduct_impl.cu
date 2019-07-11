/*
 * Expression_Binary_Dotproduct_impl2.h
 *
 *  Created on: Jan 23, 2018
 *      Author: joseph
 */
#ifdef  __CUDACC__
#ifndef EXPRESSION_BINARY_DOTPRODUCT_IMPL2_H_
#define EXPRESSION_BINARY_DOTPRODUCT_IMPL2_H_

#include "../BC_MetaTemplateFunctions/Simple.h"
#include "../BC_MetaTemplateFunctions/Adhoc.h"

#include <type_traits>
#include "Expression_Binary_Functors.cu"

namespace BC {

template<class, class, class, class > class binary_expression_scalar_R;
template<class, class, class, class > class binary_expression_scalar_L;
template<class, class > class unary_expression_transpose;
template<class, class, class, class> class binary_expression;
template<class, class > class expression;
class mul;



/*
 * a = M x K
 * b = K x N
 * c = M x N
 */

template<class> struct self_eval { static constexpr bool conditional = false; };
template<class T, class lv, class rv> struct self_eval<binary_expression<T, assign, lv, rv>> { static constexpr bool conditional = true; };

//conditional indicates whether or not the array needs to be evaluated
template<class T> struct add_ptr { using type = T*; };

//Generic (Unknown Expression)
template<class T, class enabler = void> struct evaluate {
	static constexpr bool conditional = true;
		static constexpr bool transpose = false;
		static constexpr bool scalar = false;

		template<typename param> static typename add_ptr<typename MTF::determine_scalar<T>::type>::type getScalar(const param& p) {
			return nullptr;
		}
		template<typename param> static auto getArray(const param& p) {
			return p;
		}
};
//Standard Functor_type
template<class T> struct evaluate<T*> {
	static constexpr bool conditional = false;
	static constexpr bool transpose = false;
	static constexpr bool scalar = false;

	template<typename param> static T* getScalar(const param& p) {
		return nullptr;
	}
	template<typename param> static auto getArray(const param& p) {
		return p;
	}
};

template<class T, class U>
struct evaluate<unary_expression_transpose<T, U*>> {

	static constexpr bool conditional = false;
	static constexpr bool transpose = true;
	static constexpr bool scalar = false;
	template<typename param> static T* getScalar(const param& p) {
		return nullptr;
	}
	template<typename param> static auto getArray(const param& p) {
		return p.array;
	}
};

template<class T, class lv, class rv>
struct evaluate<binary_expression<T, assign, lv, rv>> {

	static constexpr bool conditional = true;
	static constexpr bool transpose = false;
	static constexpr bool scalar = false;
	template<typename param> static T* getScalar(const param& p) {
		return nullptr;
	}
	template<typename param> static auto getArray(const param& p) {
		return p;
	}
};


//Simple Scalar by tensor R
template<class T, class lv, class rv> struct evaluate<
		binary_expression_scalar_R<T, mul, lv*, rv*>> {
	static constexpr bool conditional = false;
	static constexpr bool transpose = false;
	static constexpr bool scalar = true;

	template<typename param> static auto getScalar(const param& p) {
		return p.right;
	}
	template<typename param> static auto getArray(const param& p) {
		return p.left;
	}
};
//Simple Scalar by tensor L
template<class T, class lv, class rv> struct evaluate<
		binary_expression_scalar_L<T, mul, lv*, rv*>> {
	static constexpr bool conditional = false;
	static constexpr bool transpose = false;
	static constexpr bool scalar = true;

	template<typename param> static auto getScalar(const param& p) {
		return p.left;
	}
	template<typename param> static auto getArray(const param& p) {
		return p.right;
	}
};

//scalar R with unary transposition on inside
template<class T, class U, class rv, class V>
struct evaluate<
		binary_expression_scalar_R<T, mul,
				unary_expression_transpose<U, V*>, rv*>> { //change tensor to enable only if primitive

	static constexpr bool conditional = false;
	static constexpr bool transpose = true;
	static constexpr bool scalar = true;

	template<typename param> static auto getScalar(const param& p) {
		return p.right;
	}
	template<typename param> static auto getArray(const param& p) {
		return p.left.array;
	}

};

//scalar L with unary transposition on inside
template<class T, class U, class lv, class V>
struct evaluate<
		binary_expression_scalar_L<T, mul, lv*,
				unary_expression_transpose<U, V*>>> { //change tensor to enable only if primitive

	static constexpr bool conditional = false;
	static constexpr bool transpose = true;
	static constexpr bool scalar = true;

	template<typename param> static auto getScalar(const param& p)  { return p.left; }
	template<typename param> static auto getArray(const param& p)  { return p.right.array; }

};
//is a binary_expression (double already evaluated)

//transpose with inside scalar
template<class T, class lv, class rv, class U>
struct evaluate< unary_expression_transpose<U, binary_expression_scalar_R<T, mul, lv*, rv*>>> {

	static constexpr bool conditional = false;
	static constexpr bool transpose = true;
	static constexpr bool scalar = true;

	template<typename param> static auto getScalar(const param& p)  { return p.array.right; }
	template<typename param> static auto getArray(const param& p)  { return p.array.left; }
}; //is a binary_expression (expression by scalar)

template<class T, class lv, class rv, class U>
struct evaluate< unary_expression_transpose<U, binary_expression_scalar_L<T, mul, lv*, rv*>>> {

	static constexpr bool conditional = false;
	static constexpr bool transpose = true;
	static constexpr bool scalar = true;


	template<typename param> static auto getScalar(const param& p)  { return p.array.left; }
	template<typename param> static auto getArray(const param& p)  { return p.array.left; }
}; //is a binary_expression (scalar by expression)

}

#endif /* EXPRESSION_BINARY_DOTPRODUCT_IMPL2_H_ */
#endif
