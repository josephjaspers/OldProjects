/*
 * Tensor_Lv2_Core_impl.h
 *
 *  Created on: Jan 2, 2018
 *      Author: joseph
 */

#ifndef TENSOR_LV2_CORE_IMPL_H_
#define TENSOR_LV2_CORE_IMPL_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace BC {

template<class T, class deriv, class MATHLIB, bool Utility_Function_Supported>
struct Tensor_Utility {

	deriv& asDerived() {
		return static_cast<deriv&>(*this);
	}
	const deriv& asDerived() const {
		return static_cast<const deriv&>(*this);
	}

void printExpression() const {
	for (int i = 0; i < this->asDerived().size(); ++i) {
		std::cout << this->asDerived().data()[i] << " ";
	}
	std::cout << std::endl;
}


};
template<class scalar_type, class deriv, class MATHLIB>
struct Tensor_Utility<scalar_type, deriv, MATHLIB, true> {

/*
 *  Tensor_Base specialization (for primary tensors -- we enable these utility methods)
 */

	deriv& asDerived() {
		return static_cast<deriv&>(*this);
	}
	const deriv& asDerived() const {
		return static_cast<const deriv&>(*this);
	}

	void randomize(scalar_type lb, scalar_type ub) {
		MATHLIB::randomize(asDerived().data(), lb, ub, asDerived().size());
	}
	void fill(scalar_type value) {
		MATHLIB::fill(asDerived().data(), value, asDerived().size());
	}
	void zero() {
		MATHLIB::zero(asDerived().data(), asDerived().size());
	}
	void zeros() {
		MATHLIB::zero(asDerived().data(), asDerived().size());
	}
	void print() const {
		MATHLIB::print(asDerived().data(), asDerived().InnerShape(), asDerived().rank(), 8);
	}
	void print(int precision) const {
		MATHLIB::print(asDerived().data(), asDerived().InnerShape(), asDerived().rank(), precision);
	}

	void printSparse() const {
		MATHLIB::printSparse(asDerived().data(), asDerived().InnerShape(), asDerived().rank(), 8);
	}
	void printSparse(int precision) const {
		MATHLIB::printSparse(asDerived().data(), asDerived().InnerShape(), asDerived().rank(), precision);
	}


	void reset(std::vector<int> dimensions = std::vector<int>(0)) {
		this->asDerived().resetShape(dimensions); //dimensions auto converts to type  shape_packet<_generic>
		MATHLIB::destroy(asDerived().data());
		MATHLIB::initialize(asDerived().data(), asDerived().size());
	}

	void write(std::ofstream& os) {

		scalar_type* data = new scalar_type[asDerived().size()];
		MATHLIB::DeviceToHost(data, asDerived().data(), asDerived().size());
		os << asDerived().rank() << ',';
		for (int i = 0; i < asDerived().rank(); ++i) {
			os << asDerived().dimension(i) << ',';
		}
		for (int i = 0; i < asDerived().size() - 1; ++i) {
			os << asDerived().data()[i] << ',';
		}
		os << asDerived().data()[asDerived().size() - 1];
		os << '\n';

	}
	void read(std::ifstream& is, bool read_dimensions = true, bool overrideDimensions = true) {
		if (!is.good()) {
			std::cout << "File open error - returning " << std::endl;
			return;
		}

		std::vector<scalar_type> data;
		unsigned read_values = 0;

			std::string tmp;
			std::getline(is, tmp, '\n');

			std::stringstream ss(tmp);
			scalar_type val;

			if (ss.peek() == ',')
				ss.ignore();

			while (ss >> val) {
				data.push_back(val);
				++read_values;
				if (ss.peek() == ',')
					ss.ignore();
			}

		if (read_dimensions) {
			std::vector<int> dims((int)data[0]);
			for (int i = 0; i < dims.size(); ++i) {
				dims[i] = data[i + 1];
			}
			if (overrideDimensions) {
			asDerived().reset(dims);
			}
			MATHLIB::HostToDevice(asDerived().data(), &data[data[0] + 1], asDerived().size());
		} else {
			MATHLIB::HostToDevice(asDerived().data(), &data[0], asDerived().size());
		}

	}
};

}



#endif /* TENSOR_LV2_CORE_IMPL_H_ */
