/*
 * Matrix.h
 *
 *  Created on: Nov 9, 2017
 *      Author: joseph
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vector.h"

template<class T, class Math_lib = CPU_MATHEMATICS, class access = continuous<T, Math_lib>>
class Matrix : public Tensor_Queen<T, Math_lib, access> {
public:

	explicit Matrix<T, Math_lib, access>(int rows, int cols) : Tensor_Queen<T, Math_lib, access>({rows, cols}) {
		/*empty*/
	}

	Vector<T, Math_lib, continuous<T, Math_lib>> operator[] (int index) {
		return Vector<T, Math_lib, continuous<T, Math_lib>>(*this, index);
	}

	const Vector<T, Math_lib, continuous<T, Math_lib>> operator[] (int index) const {
		return Vector<T, Math_lib, continuous<T, Math_lib>>(*this, index);
	}

	Matrix<T, Math_lib, access>& operator = (Matrix<T, Math_lib, access> mat) {
		Math_lib::copy(this->tensor, mat.accessor(), this->size());
		return *this;
	}

	template<typename U, class A>
	Matrix<T, Math_lib, access>& operator = (const Tensor_Queen<U, Math_lib, A>& tq) {
		this->assert_same_size(tq);
		Math_lib::copy(this->tensor, tq.accessor(), this->size());
		return *this;
	}

//	Matrix<T, Math_lib, access> operator * (const Matrix<T, Math_lib, access> m) {
//		Matrix<T, Math_lib, access> mul(this->dimension(0), m.dimension(1));
//		Math_lib::matmul(mul.accessor(), this->accessor(), this->dimension(0), this->dimension(1), m.accessor(), m.dimension(1));
//		return mul;
//	}

};

#endif /* MATRIX_H_ */
