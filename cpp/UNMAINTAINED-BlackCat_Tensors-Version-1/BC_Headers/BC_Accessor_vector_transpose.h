/*
 * BC_Accessor_vector_transpose.h
 *
 *  Created on: Nov 11, 2017
 *      Author: joseph
 */

#ifndef BC_ACCESSOR_VECTOR_TRANSPOSE_H_
#define BC_ACCESSOR_VECTOR_TRANSPOSE_H_

#include "BC_Accessor_continuous.h"

template<class T, class Math_lib>
struct vector_transpose_accessor : public continuous<T, Math_lib> {

	vector_transpose_accessor<T, Math_lib>(continuous<T, Math_lib>& parent) :
			continuous<T, Math_lib>(parent) {

	}

	int dimension(int index) const override {
		return index == 1 ? this->shape[0] : 1;
	}
};

#endif /* BC_ACCESSOR_VECTOR_TRANSPOSE_H_ */
