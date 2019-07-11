/*
 * Accessor_Core.h
 *
 *  Created on: Nov 11, 2017
 *      Author: joseph
 */

#ifndef ACCESSOR_CORE_H_
#define ACCESSOR_CORE_H_

#include "Tensor_Ace.h"

/*
 * all accessors must inherit from accessor_ace
 * and either value accessor or reference accessor
 */

template<typename T, typename Math_lib>
struct accessor_ace : public Tensor_Ace {

	virtual const T* getData() const = 0;
	virtual const int* getShape() const = 0;
	virtual const int* getLeadingDimensionShape() const = 0;

	//non-const
	virtual T* getData() = 0;
	virtual int* getShape() = 0;
	virtual int* getLeadingDimensionShape() = 0;

	virtual ~accessor_ace() = default;
};

template<typename T, typename Math_lib>
struct value_accessor : public accessor_ace<T, Math_lib> {

	__attribute__((always_inline)) virtual T operator [](int index) = 0;
	__attribute__((always_inline)) virtual const T operator[](int index) const = 0;
	virtual ~value_accessor() = default;
};

template<typename T, typename Math_lib>
struct reference_accessor : public accessor_ace<T, Math_lib> {

	__attribute__((always_inline)) virtual T& operator [](int index) = 0;
	__attribute__((always_inline)) virtual const T& operator[](int index) const = 0;
	virtual ~reference_accessor() = default;
};

#endif /* ACCESSOR_CORE_H_ */
