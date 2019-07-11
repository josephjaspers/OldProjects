/*
 * BC_Expression_Base.h
 *
 *  Created on: Dec 1, 2017
 *      Author: joseph
 */

#ifndef BC_EXPRESSION_BASE_H_
#define BC_EXPRESSION_BASE_H_

/*
 * This is an identity class
 * (no real implementation)
 */

#include "BC_ArrayType_ArrayWrapper_Base.h"

template<class derived>
struct expression : BC_ArrayWrapper<derived> {

	using type = derived;

};

#endif /* BC_EXPRESSION_BASE_H_ */
