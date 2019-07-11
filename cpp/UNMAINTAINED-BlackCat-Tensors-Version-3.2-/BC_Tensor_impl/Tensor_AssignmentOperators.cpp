/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"
#include "Tensor.h"

template<typename number_type> Tensor<number_type>& Tensor<number_type>::operator=(const Scalar<number_type>& val) {

	Tensor_Operations<number_type>::fill(tensor, ranks, order, ld, val());
    alertUpdate();
    return *this;
}

template<typename number_type> inline Tensor<number_type>& Tensor<number_type>::operator=(const Tensor<number_type>& cpy) {
    if (this->isInitialized()) {
        this->assert_same_dimensions(cpy);

        Tensor_Operations<number_type>::copy(tensor, ranks, order, ld, cpy.tensor, cpy.ld);

    } else {
        Tensor_Operations<number_type>::initialize(tensor, cpy.size());
        order = cpy.order;
        ranks = new unsigned[order];
        BC::copy(ranks, cpy.ranks, order);
        ld = new unsigned[order];
        BC::copy(ld, cpy.ld, order);
        sz = cpy.size();

        Tensor_Operations<number_type>::copy(tensor, ranks, order, ld, cpy.tensor, cpy.ld);
    }
    alertUpdate();
    return *this;
}

template<typename number_type> Tensor<number_type>& Tensor<number_type>::operator=(Tensor<number_type>&& cpy) {


	if (isInitialized()) {
		assert_same_dimensions(cpy);

		if (tensor_ownership) {
			if (cpy.tensor_ownership) {
				Tensor_Operations<number_type>::destruction(tensor);
				tensor = cpy.tensor;

				delete[] ranks;
				ranks = cpy.ranks;

				cpy.reset_post_move();
			}
		} else {
			Tensor_Operations<number_type>::copy(tensor, ranks, order, ld, cpy.tensor, cpy.ld);
		}
	} else {
		sz = cpy.sz;
		order = cpy.order;

		if (cpy.tensor_ownership) {
			tensor = cpy.tensor;
			ranks = cpy.ranks;
			ld = cpy.ld;

			cpy.reset_post_move();
		} else {
	        Tensor_Operations<number_type>::initialize(tensor, size());
	        ranks = new unsigned[order];
	        BC::copy(ranks, cpy.ranks, order);
	        ld = new unsigned[order];
	        BC::copy(ld, cpy.ld, order);

	        Tensor_Operations<number_type>::copy(tensor, ranks, order, ld, cpy.tensor, cpy.ld);
		}
	}

    alertUpdate();
    return*this;
}

template<typename number_type>
Tensor<number_type>& Tensor<number_type>::operator= (std::initializer_list<number_type> vector) {

	if (isInitialized()){
		if (size() != vector.size()) {
			throw std::invalid_argument("operator =(initializer_list<number_type>)  Error: sz mismatch");
		}
		if (this->subTensor) {
			unsigned * ld_tmp = new unsigned[order];
			BC::init_leading_dimensions(ld_tmp, ranks, order);

		               Tensor_Operations<number_type>::copy(tensor, ranks, order, ld, vector.begin(), ld_tmp);
		               delete[] ld_tmp;
		} else {
			Tensor_Operations<number_type>::copy(tensor, vector.begin(), size());
		}
	} else {
	ranks = new unsigned[1];
	ranks[0] = vector.size();
	ld = new unsigned[1];
	ld[0] = 1;
	order = 1;
	sz = vector.size();

	Tensor_Operations<number_type>::initialize(tensor, size());
	Tensor_Operations<number_type>::copy(tensor, vector.begin(), size());
	}

    alertUpdate();
	return *this;
}
