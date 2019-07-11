#include "Tensor.h"
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor() : tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {
	sz = 0;
	order = 0;
	tensor = nullptr;
	ranks = nullptr;
	ld = nullptr;
}

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(const Tensor<number_type, TensorOperations>& cpy) : tensor_ownership(true), rank_ownership(true), ld_ownership(true),subTensor(false) {

	order = cpy.order;
	sz = cpy.sz;

	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);

	BC::copy(ranks, cpy.ranks, order);
	BC::init_leading_dimensions(ld, cpy.ranks, order);

	TensorOperations::initialize(tensor, size());
    subTensor || cpy.subTensor ? TensorOperations::copy(tensor, ranks, order, ld, cpy.tensor, cpy.ld) : TensorOperations::copy(tensor, cpy.tensor, sz);

}

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(Tensor<number_type, TensorOperations> && cpy) : tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {

	order = cpy.order;
	sz = cpy.sz;

	if (cpy.tensor_ownership) {
		tensor = cpy.tensor;
		ranks = cpy.ranks;
		ld = cpy.ld;
		cpy.reset_post_move();
	} else {
		TensorOperations::initialize(tensor, size());

		TensorOperations::unified_initialize(ranks, order);
		TensorOperations::unified_initialize(ld, order);
		BC::copy(ranks, cpy.ranks, order);
		BC::init_leading_dimensions(ld, cpy.ranks, order);

        subTensor || cpy.subTensor ? TensorOperations::copy(tensor, ranks, order, ld, cpy.tensor, cpy.ld) : TensorOperations::copy(tensor, cpy.tensor, sz);
	}
}
template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(const Tensor<number_type, TensorOperations>& cpy, bool copy_values) :tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {
	sz = cpy.sz;
	order = cpy.order;

	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	BC::copy(ranks, cpy.ranks, order);
	BC::init_leading_dimensions(ld, cpy.ranks, order);

	TensorOperations::initialize(tensor, size());
	if (copy_values) {
        subTensor || cpy.subTensor ? TensorOperations::copy(tensor, ranks, order, ld, cpy.tensor, cpy.ld) : TensorOperations::copy(tensor, cpy.tensor, sz);
	}
}
template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(const Tensor<number_type, TensorOperations>& cpy, bool copy_values, bool cpy_trans) : tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {
	sz = cpy.sz;

	order = cpy.order == 1 ? 2 : cpy.order;
	//order = cpy.order;


	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);

	BC::copy(ranks, cpy.ranks, order);

	if (cpy_trans) {
		if (order > 0)
			ranks[0] = cpy.cols();
		if (order > 1)
			ranks[1] = cpy.rows();
	}
	BC::init_leading_dimensions(ld, ranks, order);
	TensorOperations::initialize(tensor, sz);

	if (copy_values) {
		if (cpy_trans) {
			for (int i = 0; i < total_matrices(); ++i) {
				unsigned index = i * matrix_size();

				TensorOperations::transpose(&tensor[index], ld[1], &cpy.tensor[index], cpy.rows(), cpy.cols(), cpy.ld[1]);
			}
		}
		 else {
		        subTensor || cpy.subTensor ? TensorOperations::copy(tensor, ranks, order, ld, cpy.tensor, cpy.ld) : TensorOperations::copy(tensor, cpy.tensor, sz);
		}
	}
}

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(unsigned m, unsigned n, unsigned k, unsigned p) :
tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {

	order = 4;
	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	ranks[0] = m;
	ranks[1] = n;
	ranks[2] = k;
	ranks[3] = p;

	sz = BC::calc_sz(ranks, order);
	BC::init_leading_dimensions(ld, ranks, order);

	TensorOperations::initialize(tensor, size());

}

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(unsigned m, unsigned n, unsigned k) :
tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {
	order = 3;

	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	ranks[0] = m;
	ranks[1] = n;
	ranks[2] = k;

	BC::init_leading_dimensions(ld, ranks, order);
	sz = m * n * k;
	TensorOperations::initialize(tensor, size());
}

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(unsigned m, unsigned n) :
tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false){
	order = 2;

	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	ranks[0] = m;
	ranks[1] = n;

	sz = m * n;

	BC::init_leading_dimensions(ld, ranks, order);
	TensorOperations::initialize(tensor, size());
}

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(unsigned m) :
tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {
	order = 1;

	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	ranks[0] = m;
	sz = m;
		BC::init_leading_dimensions(ld, ranks, order);
		TensorOperations::initialize(tensor, size());
}

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(std::initializer_list<unsigned> init_ranks) :
tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {

	order = init_ranks.size();
	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	TensorOperations::port_copy(ranks, init_ranks.begin(), order);

	sz = BC::calc_sz(ranks, order);
	BC::init_leading_dimensions(ld, ranks, order);
	TensorOperations::initialize(tensor, size());
}
typedef std::vector<unsigned> Shape;

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::Tensor(const Shape& shape) :
tensor_ownership(true), rank_ownership(true), ld_ownership(true), subTensor(false) {

	order = shape.size();
	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	sz = 1;
	BC::copy(ranks, &shape[0], shape.size());
	for (unsigned i = 0; i < shape.size(); ++i) {
		sz *= shape[i];
	}
	BC::init_leading_dimensions(ld, ranks, order);
	TensorOperations::initialize(tensor, size());
}

template<typename number_type, class TensorOperations>
std::vector<unsigned> Tensor<number_type, TensorOperations>::getShape() const {
	std::vector<unsigned> s = Shape(order);

	for (int i = 0; i < order; ++i) {
		s[i] = ranks[i];
	}
	return s;
}
template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations>::~Tensor() {

	if (tensor_ownership) {
		TensorOperations::destruction(tensor);
		tensor = nullptr;
	}
	if (rank_ownership) {
		TensorOperations::destruction(ranks);
		ranks = nullptr;
	}
	if (ld_ownership) {
		TensorOperations::destruction(ld);
		ld = nullptr;
	}

}

