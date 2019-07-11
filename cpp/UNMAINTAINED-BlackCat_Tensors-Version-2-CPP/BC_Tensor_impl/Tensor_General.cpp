#include "Tensor.h"
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"

template<typename number_type, class TensorOperations>
inline void Tensor<number_type, TensorOperations>::fill(number_type val) {
	subTensor ? TensorOperations::fill(tensor, ranks, order, ld, val) : TensorOperations::fill(tensor, val, sz);
}

template<typename number_type, class TensorOperations>
inline void Tensor<number_type, TensorOperations>::randomize(number_type lower_bound, number_type upper_bound) {
	TensorOperations::randomize(tensor, lower_bound, upper_bound, size());
}

template<typename number_type, class TensorOperations>
void Tensor<number_type, TensorOperations>::zeros() {
	subTensor ? TensorOperations::fill(tensor, ranks, order, ld, (number_type) 0) : TensorOperations::zeros(tensor, sz);
}
template<typename number_type, class TensorOperations>
Scalar<number_type, TensorOperations> Tensor<number_type, TensorOperations>::max() const {
	Scalar<number_type, TensorOperations> max_val;
	TensorOperations::max(max_val.scalar, tensor, ranks, ld, order);
	return max_val;
}

template<typename number_type, class TensorOperations>
Scalar<number_type, TensorOperations> Tensor<number_type, TensorOperations>::min() const {
	Scalar<number_type, TensorOperations> min_val;
	TensorOperations::min(min_val.scalar, tensor, ranks, ld, order);
	return min_val;
}
//
template<typename number_type, class TensorOperations>
std::pair<Scalar<number_type, TensorOperations>, Tensor<unsigned, CPU>> Tensor<number_type, TensorOperations>::max_index() const {

	std::pair<Scalar<number_type, TensorOperations>, Tensor<unsigned, CPU>> dataHolder;
	Scalar<number_type, TensorOperations> max_val(0);
	Tensor<unsigned, CPU> index(order);

	unsigned* tmp_index;
	TensorOperations::initialize(tmp_index, order);

	CPU::max_index(max_val.scalar, tmp_index, tensor, ranks, ld, order);

	TensorOperations::port_copy_device_to_host(index.data(), tmp_index, order);
	TensorOperations::destruction(tmp_index);

	dataHolder.first = max_val;

	dataHolder.second = index;

	return dataHolder;
}

template<typename number_type, class TensorOperations>
std::pair<Scalar<number_type, TensorOperations>, Tensor<unsigned, CPU>> Tensor<number_type, TensorOperations>::min_index() const {
	std::pair<Scalar<number_type, TensorOperations>, Tensor<unsigned, CPU>> dataHolder;
	Scalar<number_type, TensorOperations> max_val(0);
	Tensor<unsigned, CPU> index(order);

	unsigned* tmp_index;
	TensorOperations::initialize(tmp_index, order);

	CPU::min_index(max_val.data(), tmp_index, tensor, ranks, ld, order);

	TensorOperations::port_copy_device_to_host(index.data(), tmp_index, order);
	TensorOperations::destruction(tmp_index);

	dataHolder.first = max_val;
	dataHolder.second = index;

	return dataHolder;
}

template<typename number_type, class TensorOperations>
inline Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::transpose() const {
	return Tensor<number_type, TensorOperations>(*this, true, true);
}

template<typename number_type, class TensorOperations>
const Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::T() const {
	return Tensor<number_type, TensorOperations>(*this, true, true);
}

template<typename number_type, class TensorOperations> void Tensor<number_type, TensorOperations>::print() const {

	std::cout << "--- --- --- --- --- --- --- " << std::endl;
	TensorOperations::print(tensor, ranks, ld, order);
	std::cout << "--- --- --- --- --- --- --- " << std::endl;
}

template<typename number_type, class TensorOperations> void Tensor<number_type, TensorOperations>::read(std::ifstream& is) {
	reset();

	is >> order;
	is >> sz;

	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	TensorOperations::initialize(tensor, sz);
	for (unsigned i = 0; i < order; ++i) {
		is >> ranks[i];
		is >> ld[i];
	}
	for (unsigned i = 0; i < sz; ++i) {
		is >> tensor[i];
	}
}

template<typename number_type, class TensorOperations> void Tensor<number_type, TensorOperations>::readCSV(std::ifstream& is) {
	if (!is.good()) {
		std::cout << "File open error - returning " << std::endl;
		return;
	}
	reset();

	std::vector<number_type> data;
	while (is.good()) {
		std::string tmp;
		std::getline(is, tmp, '\n');

		std::stringstream ss(tmp);
		double val;
		while (ss >> val) {
			data.push_back(val);
			if (ss.peek() == ',')
				ss.ignore();
		}
	}

	order = 1;
	sz = data.size();
	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	ranks[0] = data.size();
	ld[0] = data.size();

	TensorOperations::initialize(tensor, sz);
	TensorOperations::port_copy(tensor, &data[0], sz);

}
template<typename number_type, class TensorOperations> void Tensor<number_type, TensorOperations>::readCSV(std::ifstream& is, unsigned numb_values) {
	if (!is.good()) {
		std::cout << "File open error - returning " << std::endl;
		return;
	}
	reset();

	std::vector<number_type> data;

	unsigned read_values = 0;
	while (is.good() && read_values != numb_values) {
		std::string tmp;
		std::getline(is, tmp, '\n');

		std::stringstream ss(tmp);
		double val;

		if (ss.peek() == ',')
			ss.ignore();

		while (ss >> val) {
			data.push_back(val);
			++read_values;
			if (ss.peek() == ',')
				ss.ignore();
		}
	}

	order = 1;
	sz = read_values;
	TensorOperations::unified_initialize(ranks, order);
	TensorOperations::unified_initialize(ld, order);
	ranks[0] = read_values;
	ld[0] = 1;

	TensorOperations::initialize(tensor, sz);
	TensorOperations::port_copy(tensor, &data[0], sz);
}
template<typename number_type, class TensorOperations> void Tensor<number_type, TensorOperations>::write(std::ofstream& is) {
	is << order << ' ';
	is << sz << ' ';

	for (unsigned i = 0; i < order; ++i) {
		is << ranks[i] << ' ';
		is << ld[i] << ' ';
	}
	for (unsigned i = 0; i < sz; ++i) {
		is << tensor[i] << ' ';
	}
}
