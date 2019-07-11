/*
 * BC_Tensor_Base2.h
 *
 *  Created on: Dec 12, 2017
 *      Author: joseph
 */

#ifndef BC_TENSOR_VECTOR_H_
#define BC_TENSOR_VECTOR_H_

#include "../BlackCat_Internal_GlobalUnifier.h"
#include "BC_Tensor_Scalar.h"
namespace BC {


//frwd dec
template<class, int, class, class>
class RowVector;

template<class, int, int, class, class>
class Matrix;

template<class T, int row, class lib, class LD>
class Vector : public Tensor_Core<T, Vector<T, row, lib, LD>, lib, Inner_Shape<row>, LD> {

public:

	using parent_class = Tensor_Core<T, Vector<T, row, lib, LD>, lib, Inner_Shape<row>, typename DEFAULT_LD<Inner_Shape<row>>::type>;
	using parent_class::parent_class;
	using parent_class::operator=;

	template<class U, class alt_LD> Vector(const Vector<U, row, lib, alt_LD>&  vec) { (*this) = vec; }


	const RowVector<T, row, lib, LD> t() const {
		return RowVector<T, row, lib, LD>(this->data());
	}


	template<int sub_row>
	const Scalar<T, lib> operator [] (int index) const {
		return Scalar<T, lib>(&(this->array[index]));
	}
		  Scalar<T, lib> operator [] (int index) {
		return Scalar<T, lib>(&(this->array[index]));
	}
};
}
#include "BC_Tensor_RowVector.h"
#include "BC_Tensor_Matrix.h"
#endif /* BC_TENSOR_VECTOR_H_ */
