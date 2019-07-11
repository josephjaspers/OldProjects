/*

 * BC_Expression_Base.h
 *
 *  Created on: Dec 11, 2017
 *      Author: joseph
 */

#ifdef  __CUDACC__
#ifndef EXPRESSION_BASE_H_
#define EXPRESSION_BASE_H_
namespace BC {

#include <cuda.h>
#include "../BlackCat_Internal_Definitions.h"


template<class T, class derived>
struct expression {
	using type = derived;
	using scalar_type = T;
};

template<class T, class derived>
struct non_linear_expression : expression<T, derived> {
	using type = derived;
	using scalar_type = T;
};



}

#endif /* EXPRESSION_BASE_H_ */
#endif
