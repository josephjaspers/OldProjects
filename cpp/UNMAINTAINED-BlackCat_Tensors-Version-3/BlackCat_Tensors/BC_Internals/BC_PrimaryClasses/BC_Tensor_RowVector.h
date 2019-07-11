/*
 * BC_Tensor_RowRowVector.h
 *
 *  Created on: Dec 19, 2017
 *      Author: joseph
 */



#ifndef BC_TENSOR_ROWRowVector_H_
#define BC_TENSOR_ROWRowVector_H_

#include "../BlackCat_Internal_GlobalUnifier.h"
#include "BC_Tensor_Scalar.h"
namespace BC {
template<class, int, int, class, class>
class Matrix;


template<class T, int row, class lib, //default = CPU,
		class LD // default = typename DEFAULT_LD<Inner_Shape<row>>::type
>
class RowVector : public Tensor_Core<T, RowVector<T, row, lib, LD>, lib, Inner_Shape<1, row>, typename DEFAULT_LD<Inner_Shape<1, row>>::type> {

public:

	using parent_class = Tensor_Core<T, RowVector<T, row, lib, LD>, lib, Inner_Shape<1, row>, typename DEFAULT_LD<Inner_Shape<1, row>>::type>;
	using this_type = RowVector<T, row, lib, LD>;
	using parent_class::parent_class;
	using parent_class::operator=;

	template<class U, class alt_LD> RowVector(const RowVector<U, row, lib, alt_LD>&  vec) : parent_class() { (*this) = vec; }

	const Vector<T, row, lib, LD> t() const {
		return Vector<T, row, lib, LD>(this->data());
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

#endif /* BC_TENSOR_ROWRowVector_H_ */
