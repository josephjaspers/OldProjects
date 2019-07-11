#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"
#include "Tensor.h"

template<typename number_type, class TensorOperations>
void Tensor<number_type, TensorOperations>::reset_post_move() {
#ifndef BLACKCAT_DISABLE_ADVANCED_CHECKS
	if (!tensor_ownership) {
		throw std::invalid_argument("ID_Tensor reset -- cannot reset a subtensor");
	}
#endif
	sz = 0;
	tensor = nullptr;
	ranks = nullptr;
	ld = nullptr;

	sz = 0;
	order = 0;

}

template<typename number_type, class TensorOperations>
void Tensor<number_type, TensorOperations>::reset() {
#ifndef BLACKCAT_DISABLE_ADVANCED_CHECKS
	if (!tensor_ownership) {
		throw std::invalid_argument("ID_Tensor reset -- cannot reset a subtensor");
	}
#endif

	TensorOperations::destruction(tensor);
	TensorOperations::destruction(ranks);
	TensorOperations::destruction(ld);

	sz = 0;
	tensor = nullptr;
	ranks = nullptr;
	ld = nullptr;
	order = 0;

}

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::reshape(Shape new_shape) {
#ifndef BLACKCAT_DISABLE_ADVANCED_CHECKS
	if (!tensor_ownership) {
		throw std::invalid_argument("ID_Tensor reset -- cannot reset a subtensor");
	}
	unsigned new_sz = 1;
	for (auto iter = new_shape.begin(); iter != new_shape.end(); ++iter) {
		new_sz *= *iter;
	}

	if (size() != new_sz) {
		throw std::invalid_argument("reshape sz mismatch");
	}
#endif

	TensorOperations::destruction(ranks);
	TensorOperations::destruction(ld);
	order = new_shape.size();
	ranks = new unsigned[order];
	ld = new unsigned[order];

	BC::copy(ranks, &new_shape[0], order);
	BC::init_leading_dimensions(ld, ranks, order);

	return *this;
}
template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::flatten() {
#ifndef BLACKCAT_DISABLE_ADVANCED_CHECKS
	if (!tensor_ownership) {
		throw std::invalid_argument("ID_Tensor reset -- cannot reset a subtensor");
	}
#endif
	reshape({ size(), 1 });
	order = 1;

	return *this;
}

