/*
 * Expression_Unary_Negation.h
 *
 *  Created on: Dec 26, 2017
 *      Author: joseph
 */
#ifdef  __CUDACC__
#ifndef EXPRESSION_UNARY_NEGATION_H_
#define EXPRESSION_UNARY_NEGATION_H_

#include "Expression_Base.cu"
namespace BC {
template<class, class >
class Array_Type;

template<class T, class functor_type>
struct unaryExpression_negation: expression<T, unaryExpression_negation<T, functor_type>> {

	functor_type array;

	unaryExpression_negation(functor_type cpy) :
			array(cpy) {
	}

	T operator [](int index) const {
		return -array[index];
	}
};

}

#endif /* EXPRESSION_UNARY_NEGATION_H_ */
#endif
