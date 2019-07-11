/*
 * BC_Tensor_Cube.h
 *
 *  Created on: Dec 18, 2017
 *      Author: joseph
 */

#ifndef BC_TENSOR_CUBE_H_
#define BC_TENSOR_CUBE_H_




#include "../BlackCat_Internal_GlobalUnifier.h"
#include "BC_Tensor_Vector.h"
namespace BC {
template<class T, int row, int col, int depth, class lib,class LD>
class Cube : public Tensor_Core<T, Cube<T, row,col, depth, lib>, lib, Inner_Shape<row, col, depth>, typename DEFAULT_LD<Inner_Shape<row, col, depth>>::type> {


public:
	using parent_class = Tensor_Core<T, Cube<T, row, col, depth, lib>, lib, Inner_Shape<row, col, depth>, typename DEFAULT_LD<Inner_Shape<row, col, depth>>::type>;
	using this_type = Cube<T, row, col, depth, lib>;
	using parent_class::operator =;
	using parent_class::parent_class;

	template<class U, class alt_LD>	Cube(const Cube<U, row, col, depth, lib>&  vec) : parent_class() { (*this) = vec; }

		  Matrix<T, row, col, lib, LD> operator [] (int index) {
		return Matrix<T, row, col, lib, LD>(& this->array[index * row * col]);
	}
	const Matrix<T, row, col, lib, LD> operator [] (int index) const {
			return Matrix<T, row, col, lib, LD>(& this->array[index * row * col]);
	}

};
}

#endif /* BC_TENSOR_CUBE_H_ */
