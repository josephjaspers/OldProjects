/*
 * BC_Expression_Binary.h
 *
 *  Created on: Dec 1, 2017
 *      Author: joseph
 */

#ifndef EXPRESSION_BINARY_POINTWISE_SAME_H_
#define EXPRESSION_BINARY_POINTWISE_SAME_H_


#include "Expression_Base.h"
namespace BC {


template<class T, class op, class lv, class rv>
class binary_expression;

template<class T, class operation, class lv, class rv>
class binary_expression : public expression<T, binary_expression<T, operation, lv, rv>> {
public:

	using this_type = binary_expression<T, operation, lv, rv>;
	operation oper;

	lv left;
	rv right;

	template<class L, class R>
	inline __attribute__((always_inline)) binary_expression(L l, R r) :
			left(l), right(r) {
	}

	inline __attribute__((always_inline)) binary_expression(const binary_expression<T, operation, lv, rv>&)  = default;


	inline __attribute__((always_inline)) auto operator [](int index) const {
		return oper(left[index], right[index]);
	}
};

}

#endif /* EXPRESSION_BINARY_POINTWISE_SAME_H_ */
