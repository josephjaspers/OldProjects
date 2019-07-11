/*
 * Superclass_Tensors.h
 *
 *  Created on: Oct 29, 2017
 *      Author: joseph
 */

#ifndef SUPERCLASS_TENSORS_H_
#define SUPERCLASS_TENSORS_H_
#include "Accessors.h"

/*
 * Asserts the minimal amount methods/fields for this Tensor class
 */

template<class T, class Math_lib, class InternalAccessor>
class Tensor_King {
public:

	InternalAccessor tensor;

	template<typename ... params>
	Tensor_Ace(params&... fields) : tensor(fields...) {
		/*empty*/
	}

	const InternalAccessor& accessor() const { return tensor; }
		  InternalAccessor& accessor()		 { return tensor; }

	virtual int size() const = 0;
	virtual int order() const = 0;
	virtual int order(int index) const = 0;

	template<class U, class A>
	void assert_same_size(const Tensor_King<U, Math_lib, A>& t) {
		if (size() != t.size()) {
			throw std::invalid_argument("assert same size failure");
		}
	}
	template<class c>
	void assert_same_size(const c& t) {
		if (size() != t.size()) {
			throw std::invalid_argument("assert same size failure");
		}
	}
	int max(int a, int b) {
		return a > b ? a : b;
	}

	template<class U, class A>
	void assert_same_dimensions(const Tensor_King<U,Math_lib, A>& t) {

		for (int i = 0; i < max(order(), t.order()); ++i) {
			if (order(i) != t.order(i)) {
				throw std::invalid_argument("assert same dimensionality failure");

			}
		}
	}

	virtual ~Tensor_King() = default;
};



#endif /* SUPERCLASS_TENSORS_H_ */
