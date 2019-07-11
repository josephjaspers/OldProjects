/* SCALAR_H_ */
/*
 * Scalar.h
 *
 *  Created on: Oct 27, 2017
 *      Author: joseph
 */

#ifndef BlackCat_VECTOR_H_
#define BlackCat_VECTOR_H_

#include "Scalar.h"
#include "Tensor_Buffers.h"
#include <iostream>
#include "Accessors.h"
#include "CPU.h"
#include "Scalar.h"
#include "Tensor_Queen.h"

template<class T,												//T the object type
		class Math_lib = CPU_MATHEMATICS,						//Math_lib the library for certain functions
		template<class, class > class Accessor = continuous>   	//the destructor
class Vector : public Tensor_Queen<T, Math_lib, Accessor<T, Math_lib>> {

	//------------------------------------------------------------------------ Friends --------------------------------------------------------------------//

	template<class U, class Ml, template<class, class > class A>
	friend class Vector;

	template<class U2, class Ml2, template<class, class > class A>
	friend class Matrix;
	//------------------------------------------------------------------------ Friends --------------------------------------------------------------------//

protected:
	using Tensor_Queen<T, Math_lib, Accessor<T, Math_lib>>::tensor;

	//------------------------------------------------------------------------ Constructor for sub_accesses (private) --------------------------------------------------------------------

	//Constructor for subVector
	Vector<T, Math_lib, Accessor>(const Tensor_Queen<T, Math_lib, Accessor<T,Math_lib>>& v, int index, int size) :
			Tensor_Queen<T, Math_lib, Accessor<T, Math_lib>>(v, index, {size}) {
	}

	//should always be a matrix
	template<class A>
	Vector<T, Math_lib, Accessor>(const Tensor_Queen<T, Math_lib, A>& super, int index) :
																	//multiply index by rows to the correct column
			Tensor_Queen<T, Math_lib, Accessor<T, Math_lib>>(super,index) {
	}

public:

	// ----------------------------------------------------------------------------- Public Constructors -----------------------------------------------------------------------------
	Vector<T, Math_lib, Accessor>(int size) :
			Tensor_Queen<T, Math_lib, Accessor<T, Math_lib>>(size) {
	}

	virtual ~Vector<T, Math_lib, Accessor>() = default;

	// ----------------------------------------------------------------------------- Accessor Methods --------------------------------------------------------------------------------

	//access a scalar
	Id_Scalar<T, Math_lib> operator [](int index) {
		return Id_Scalar<T, Math_lib>(&this->accessor()[index]);
	}
	const Id_Scalar<const T, Math_lib> operator [](int index) const {
		return Id_Scalar<const T, Math_lib>(&this->accessor()[index]);
	}

	//access a sub_vector
	Vector<T, Math_lib, Accessor> operator ()(int sub_vector_index, int sub_vector_length) {
		return Vector<T, Math_lib, Accessor>(*this, sub_vector_index, sub_vector_length);
	}

	//access a sub_vector
	const Vector<T, Math_lib, Accessor> operator ()(int sub_vector_index, int sub_vector_length) const {
		return Vector<T, Math_lib, Accessor>(*this, sub_vector_index, sub_vector_length);
	}

	// ----------------------------------------------------------------------------- Assignment operators ------------------------------------------------------------------------------------------
	Vector<T, Math_lib, Accessor>& operator =(const Vector<T, Math_lib, Accessor>& ary) {
		Math_lib::copy(tensor, ary.accessor(), this->size());
		return *this;
	}

	template<class U, template<class, class > class A>
	Vector<T, Math_lib, Accessor>& operator =(const Vector<U, Math_lib, A>& ary) {
		Math_lib::copy(tensor, ary.accessor(), this->size());
		return *this;
	}

	template<class U, class A>
	Vector<T, Math_lib, Accessor>& operator =(const Tensor_King<U, Math_lib, A>& ary) {
		Math_lib::copy(tensor, ary.accessor(), this->size());
		return *this;
	}

	template<class U, class A>
	Vector<T, Math_lib, Accessor>& operator =(const Tensor_King<U, Math_lib, A>& ary) {
		Math_lib::copy(tensor, ary.accessor(), this->size());
		return *this;
	}
};

#endif
