/*
 * BC_ArrayWrapper_Base.h
 *
 *  Created on: Dec 8, 2017
 *      Author: joseph
 */

#ifndef BC_ARRAYTYPE_ARRAYWRAPPER_BASE_H_
#define BC_ARRAYTYPE_ARRAYWRAPPER_BASE_H_

/*
 * This class is the superclass of any class that has a default functor_type
 * in regards to TensorBase class as a non-pointer (T instead of T*)
 * Generally BC_ArrayWrapper subclasses are expressions_types and/or
 *
 * other array classes.
 *
 */

template<class derived>
class BC_ArrayWrapper {
	using type = derived;
};




#endif /* BC_ARRAYTYPE_ARRAYWRAPPER_BASE_H_ */
