/*
 * Expression_Unary_Pointwise.cu
 *
 *  Created on: Jan 25, 2018
 *      Author: joseph
 */
#ifdef  __CUDACC__
#ifndef EXPRESSION_UNARY_POINTWISE_CU_
#define EXPRESSION_UNARY_POINTWISE_CU_

#include "Expression_Base.cu"
namespace BC {
template<class T, class operation, class value>
class unary_expression : public expression<T, unary_expression<T, operation, value>> {
public:

	using this_type = unary_expression<T, operation, value>;
	operation oper;

	value data;

	inline __attribute__((always_inline)) __BC_gcpu__ unary_expression(value v) :
			data(v) {
	}
	inline __attribute__((always_inline)) __BC_gcpu__ auto operator [](int index) const {
		return oper(data[index]);
	}
};

}



#endif /* EXPRESSION_UNARY_POINTWISE_CU_ */
#endif
