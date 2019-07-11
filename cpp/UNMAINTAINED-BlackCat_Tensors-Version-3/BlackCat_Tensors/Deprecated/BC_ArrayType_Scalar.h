/*
 * BC_Accessor_Scalar.h
 *
 *  Created on: Dec 2, 2017
 *      Author: joseph
 */

#ifndef BC_ARRAYTYPE_SCALAR_H_
#define BC_ARRAYTYPE_SCALAR_H_


#include "BC_ArrayType_Base.h"

/*
 * This class is currently not used -- it is an alternative
 * to utilzing binary_pointwise_scalar_L/R
 */

template<class T, class ml>
struct accessor_scalar : BC_Array_Type<accessor_scalar<T, ml>> {
	 T scalar;

	 accessor_scalar(T& scal) : scalar(scal) {};

	 T& operator [] (int index) { return scalar; }
	 const T& operator [] (int index) const { return scalar;}
};


#endif /* BC_ARRAYTYPE_SCALAR_H_ */
