/*
 * Matrix.h
 *
 *  Created on: Nov 5, 2017
 *      Author: joseph
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vector.h"

template<class T,												//T the object type
		class Math_lib = CPU_MATHEMATICS,						//Math_lib the library for certain functions
		template<class, class > class Accessor = continuous>   	//the destructor

class Matrix : public Tensor_Queen<T, Math_lib, Accessor<T, Math_lib>> {

protected:

	using Tensor_Queen<T, Math_lib, Accessor<T, Math_lib>>::tensor;

	template<class U, class Ml, template<class, class > class A>
	friend class Vector;

	template<class U2, class Ml2, template<class, class > class A>
	friend class Matrix;
public:

	//basic constructor
	Matrix<T, Math_lib, Accessor>(int rows, int cols) :
			Tensor_Queen<T, Math_lib, Accessor<T, Math_lib>>(rows, cols) {

	}
	//-----------------------------------------------data accessors --------------------------------//
	const Vector<T, Math_lib, continuous> operator [](int index) const {
		return Vector<T, Math_lib, continuous>(*this, index * this->order(1));
	}

	Vector<T, Math_lib, continuous> operator [](int index) {
		return Vector<T, Math_lib, continuous>(*this, index * this->order(1));
	}



#include "BC_Matrix_Mul.h"
	Matrix<T, Math_lib, continuous> operator * (Matrix<T,Math_lib, continuous> mat) const {


		Matrix<T, Math_lib, continuous> mul(this->order(0), mat.order(1));

		mul.zero();

		Math_lib::matmul(mul.accessor().getPtr(),this->order(0), this->order(1),this->accessor().getPtr(), mat.accessor().getPtr(), mat.order(1));

		return mul;
	}

	///-----------------------------------------assignment operators ---------------------------------//
	Matrix<T, Math_lib, Accessor>& operator =(const Matrix<T, Math_lib, Accessor>& ary) {
		this->assert_same_size(ary);
		Math_lib::copy(tensor, ary.accessor(), this->size());
		return *this;
	}

	template<class U, template<class, class > class A>
	Matrix<T, Math_lib, Accessor>& operator =(const Matrix<U, Math_lib, A>& ary) {
		this->assert_same_size(ary);
		Math_lib::copy(tensor, ary.accessor(), this->size());
		return *this;
	}

	template<class U, class A>
	Matrix<T, Math_lib, Accessor>& operator =(const Tensor_King<U, Math_lib, A>& ary) {
		this->assert_same_size(ary);
		Math_lib::copy(tensor, ary.accessor(), this->size());
		return *this;
	}
};

#endif /* MATRIX_H_ */
