/*
 * BC_Accessor.h
 *
 *  Created on: Dec 2, 2017
 *      Author: joseph
 */

#ifndef BC_ARRAYTYPE_BASE_H_
#define BC_ARRAYTYPE_BASE_H_

#include "BC_ArrayType_ArrayWrapper_Base.h"
#include "BC_Expression_Base.h"

template<class derived>
struct BC_Array_Type : BC_ArrayWrapper<derived> {
	using type = derived;
};

//Identity class, no implementation

#endif /* BC_ARRAYTYPE_BASE_H_ */
