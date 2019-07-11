/*
 * Vector.h
 *
 *  Created on: Nov 9, 2017
 *      Author: joseph
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "Scalar.h"
#include "Tensor_Queen.h"
#include "BC_Accessor_vector_transpose.h"

template<class T, class Math_lib = CPU_MATHEMATICS, class Accessor = continuous<T, Math_lib>>
class Vector : public Tensor_Queen<T, Math_lib, Accessor> {
protected:
	template<class t2, class ml, class a>
	friend class Matrix;

	///the accessor for this constructor should always be the default continuous
	template<typename A>
	Vector<T, Math_lib, Accessor>(const Tensor_Queen<T, Math_lib, A>& parent, int index) :
			/*
			 * const_cast does not defy-constness as this subtensor will return as a constant value if the parent tensor is const
			 */
			Tensor_Queen<T, Math_lib, Accessor>(false, const_cast<T*>(&parent.accessor()[index * parent.dimension(0)]), const_cast<int*>(parent.accessor().getShape()), 1) {
	}

	template<typename A>
	Vector<T, Math_lib, Accessor>(const Vector<T, Math_lib, Accessor>& parent, int index, int type) :
			/*
			 * const_cast does not defy-constness as this subtensor will return as a constant value if the parent tensor is const
			 */
			Tensor_Queen<T, Math_lib, Accessor>(false, const_cast<T*>(false, &parent.accessor()[index * parent.dimension(0)]), const_cast<int*>(parent.accessor().getShape()),
					1) {
	}
public:

	//shadows the parent version
	Tensor_Queen<T, Math_lib, vector_transpose_accessor<T, Math_lib>> t() {
		return Tensor_Queen<T, Math_lib, vector_transpose_accessor<T, Math_lib>>(false, this->accessor());
	}


	explicit Vector<T, Math_lib, Accessor>(int rows) :
			Tensor_Queen<T, Math_lib, Accessor>({ rows }) {
		/*empty*/
	}

	Id_Scalar<T, Math_lib> operator[](int index) {
		return Id_Scalar<T, Math_lib>(&this->tensor[index]);
	}

	const Id_Scalar<T, Math_lib> operator[](int index) const {
		return Id_Scalar<T, Math_lib>(&this->tensor[index]);
	}

	Vector<T, Math_lib, Accessor>& operator =(Vector<T, Math_lib, Accessor> vector) {
		Math_lib::copy(this->tensor, vector.accessor(), this->size());
		return *this;
	}

	template<typename U, class A>
	Vector<T, Math_lib, Accessor>& operator =(const Tensor_Queen<U, Math_lib, A>& tq) {
		Math_lib::copy(this->tensor, tq.accessor(), this->size());
		return *this;
	}

};

#endif /* VECTOR_H_ */
