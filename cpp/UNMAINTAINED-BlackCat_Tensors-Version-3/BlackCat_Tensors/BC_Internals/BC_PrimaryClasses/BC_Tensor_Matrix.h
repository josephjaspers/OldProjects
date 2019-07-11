/*
 * BC_Tensor_Matrix.h
 *
 *  Created on: Dec 18, 2017
 *      Author: joseph
 */

#ifndef BC_TENSOR_MATRIX_H_
#define BC_TENSOR_MATRIX_H_

#include "../BlackCat_Internal_GlobalUnifier.h"
#include "BC_Tensor_Vector.h"
namespace BC {

template<class T, int row, int col, class lib, class LD>
class Matrix : public Tensor_Core<T, Matrix<T, row, col, lib, LD>, lib, Inner_Shape<row, col>, LD> {

public:
	using parent_class      = Tensor_Core<T, Matrix<T, row, col, lib>, lib, Inner_Shape<row, col>, LD>;
	using this_type         = Matrix<T, row, col, lib, LD>;

	using parent_class::parent_class;
	using parent_class::operator=;

	template<class U, class alt_LD> Matrix(const Matrix<U, row, col, lib, alt_LD>& mat) { (*this) = mat; }

	const Matrix<unary_expression_transpose_mat<T, this_type>, col, row, lib, typename DEFAULT_LD<Inner_Shape<col, row>>::type> t() const {
		return Matrix<unary_expression_transpose_mat<T, this_type>, col, row, lib>(*this, this->array);
	}
	      Vector<T, row, lib, LD> operator [] (int index)  {
		return Vector<T, row, lib, LD>(&this->array[index] * row);
	}
	const Vector<T, row, lib, LD> operator [] (int index) const  {
		return Vector<T, row, lib, LD>(&this->array[index] * row);
	}

};
}


#endif /* BC_TENSOR_MATRIX_H_ */
