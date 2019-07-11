/*
 * BC_Expression_Binary.h
 *
 *  Created on: Dec 1, 2017
 *      Author: joseph
 */
#ifdef  __CUDACC__
#ifndef EXPRESSION_BINARY_POINTWISE_SAME_H_
#define EXPRESSION_BINARY_POINTWISE_SAME_H_


#include "Expression_Base.cu"
namespace BC {


template<class T, class op, class lv, class rv>
class binary_expression;

template<class T, class operation, class lv, class rv>
struct binary_expression : public expression<T, binary_expression<T, operation, lv, rv>> {

	operation oper;

	lv left;
	rv right;

	template<class L, class R>
	inline __attribute__((always_inline)) __BC_gcpu__ binary_expression(L l, R r) :
			left(l), right(r) {
	}

	inline __attribute__((always_inline)) __BC_gcpu__ auto operator [](int index) const -> decltype(oper(left[index], right[index])) {
		return oper(left[index], right[index]);
	}
};


}

#endif /* EXPRESSION_BINARY_POINTWISE_SAME_H_ */
#endif
