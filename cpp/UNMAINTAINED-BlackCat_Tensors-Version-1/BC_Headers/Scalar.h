/*
 * Scalar.h
 *
 *  Created on: Nov 9, 2017
 *      Author: joseph
 */

#ifndef SCALAR_H_
#define SCALAR_H_

#include "CPU.h"
#include "BC_Accessor_scalar.h"
#include "Tensor_Queen.h"

template<typename T, class Math_lib = CPU_MATHEMATICS>
class Scalar : public Tensor_Queen<T, Math_lib, StackScalarAccessor<T, Math_lib>> {
public:
	Scalar<T, Math_lib>(T scalar) :
			Tensor_Queen<T, Math_lib, StackScalarAccessor<T, Math_lib>>(false, scalar) {
		/*empty*/
	}

	operator T() const {
		return this->accessor()[0];
	}

	Scalar<T, Math_lib>& operator =(const Scalar<T, Math_lib>& s) {
		Math_lib::copy(this->tensor, s.tensor, this->size());
		return *this;
	}

	template<typename U, class A>
	Scalar<T, Math_lib>& operator =(const Tensor_Queen<U, Math_lib, A>& tq) {
		this->assert_same_size(tq);

		Math_lib::copy(this->accessor(), tq.accessor(), this->size());
		return *this;
	}
};


template<typename T, class Math_lib = CPU_MATHEMATICS>
class Id_Scalar : public Tensor_Queen<T, Math_lib, ReferenceScalarAccessor<T, Math_lib>> {
protected:

	template<typename T2, class ml, class A>
	friend class Vector;

	Id_Scalar<T, Math_lib>(T* scal) : Tensor_Queen<T, Math_lib,ReferenceScalarAccessor<T, Math_lib>>(false, scal) {
		/*empty*/
	}
public:
	Id_Scalar<T, Math_lib>& operator = (Id_Scalar<T, Math_lib> s) {
		Math_lib::copy(this->tensor, s.tensor, this->size());
		return *this;
	}

	//THIS NEEDS TO BE CHANGED ONCE CUDA IS IMPLEMENTED
	operator T() const {
		return this->accessor()[0];
	}

	template<typename U, class A>
	Id_Scalar<T, Math_lib>& operator = (const Tensor_Queen<U, Math_lib, A>& tq) {
		this->assert_same_size(tq);

		Math_lib::copy(this->accessor(), tq.accessor(), this->size());
		return *this;
	}
};

#endif /* SCALAR_H_ */
