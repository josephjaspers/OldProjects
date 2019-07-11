#include "Tensor.h"
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"

//------------------------------------- Scalar Accessor-------------------------------------//

template<typename number_type, class TensorOperations> Scalar<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator()(unsigned index) {
	return Scalar<number_type, TensorOperations>(&tensor[index], false);
}

template<typename number_type, class TensorOperations> const Scalar<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator()(unsigned index) const {
	return Scalar<number_type, TensorOperations>(&tensor[index], false);
}

//------------------------------------- Index Tensor Constructor------------------------------------//

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(const Tensor<number_type, TensorOperations>& super_tensor, unsigned index) :
		tensor_ownership(false), subTensor(super_tensor.subTensor), rank_ownership(false), ld_ownership(false) {

	unsigned tensor_index = 1;
	for (unsigned i = 0; i < super_tensor.order - 1; ++i) {
		tensor_index *= super_tensor.ranks[i];
	}
	tensor_index *= index;

	this->tensor = &super_tensor.tensor[tensor_index];
	this->ranks = super_tensor.ranks;
	this->ld = super_tensor.ld;
	this->order = super_tensor.order > 0 ? super_tensor.order - 1 : 0;

	this->sz = super_tensor.sz / super_tensor.ranks[order];
}

//------------------------------------- Index Tensor Operator-------------------------------------//

template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator[](unsigned index) {

#ifndef BLACKCAT_DISABLE_RUNTIME_CHECKS
	if (index >= rank(order - 1)) {
		throw std::invalid_argument("Operator[] out of bounds -- Rank - dim: " + std::to_string(order) + " Index: " + std::to_string(index));
	}
#endif

	return Tensor<number_type, TensorOperations>(*this, index);
}

template<typename number_type, class TensorOperations> const Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator[](unsigned index) const {

#ifndef BLACKCAT_DISABLE_RUNTIME_CHECKS
	if (index >= rank(order - 1)) {
		std::cout << " index = " << index << "rank at outer order = " << rank(order - 1) << std::endl;
		throw std::invalid_argument("Operator[] out of bounds -- Rank - dim: " + std::to_string(order) + " Index: " + std::to_string(index));
	}
#endif

	return Tensor<number_type, TensorOperations>(*this, index);

}

//------------------------------------SUBTENSOR -------------------------------------//
template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator()(Shape index, Shape shape) {

	return Tensor<number_type, TensorOperations>(*this, index, shape);
}

template<typename number_type, class TensorOperations> const Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator()(Shape index, Shape shape) const {

	return Tensor<number_type, TensorOperations>(*this, index, shape);
}

//------------------------------Constructor for generating a sub tensor (NOT AN INDEX TENSOR)------------------------------//

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(const Tensor<number_type, TensorOperations>& super_tensor, Shape index, Shape shape) :
		tensor_ownership(false), rank_ownership(true), ld_ownership(false), subTensor(true) {
	if (super_tensor.order != index.size() || shape.size() > index.size()) {
		throw std::invalid_argument("Non-definitive index given for subTensor");
	}

	sz = BC::calc_sz(&shape[0], shape.size());
	order = shape.size();
	TensorOperations::unified_initialize(ranks, order);
	ld = super_tensor.ld;
	BC::copy(ranks, &shape[0], order);

	unsigned t_id = 0;
	for (int i = 0; i < index.size(); ++i) {
		t_id += super_tensor.ld[i] * index[index.size() - i - 1];
	}
	tensor = &super_tensor.tensor[t_id];
}

