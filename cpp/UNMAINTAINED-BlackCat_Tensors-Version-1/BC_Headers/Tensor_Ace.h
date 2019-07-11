#ifndef TENSOR_ACE_H_
#define TENSOR_ACE_H_

#include <stdexcept>

class Tensor_Ace {

public:
	virtual int size() const = 0;
	virtual int dimension(int index) const = 0;
	virtual int leading_dimension(int index) const = 0;
	virtual int order() const = 0;

	bool same_size(const Tensor_Ace&) const;
	bool same_dimensions(const Tensor_Ace&) const;

	void assert_same_size(const Tensor_Ace&) const;
	void assert_same_dimensions(const Tensor_Ace&) const;

	virtual ~Tensor_Ace() {};

};
int max(int a, int b) {
	return a > b ? a : b;
}

bool Tensor_Ace::same_size(const Tensor_Ace& tens) const {
	return size() == tens.size();
}

bool Tensor_Ace::same_dimensions(const Tensor_Ace& tens) const {
	for (int i = 0; i < max(tens.order(), order()); ++i) {
		if (dimension(i) != tens.dimension(i)) {
			return false;
		}
	}
	return true;
}

void Tensor_Ace::assert_same_size(const Tensor_Ace& tens) const {
	if (!same_size(tens)) {
		throw std::invalid_argument("size mismatch");
	}
}

void Tensor_Ace::assert_same_dimensions(const Tensor_Ace& tens) const {
	if (!same_dimensions(tens)) {
		throw std::invalid_argument("dimension mismatch");
	}
}

#endif /* TENSOR_ACE_H_ */

