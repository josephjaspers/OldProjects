/*
 * Superclass_Tensors.h
 *
 *  Created on: Oct 29, 2017
 *      Author: joseph
 */

#ifndef SUPERCLASS_TENSORS_H_
#define SUPERCLASS_TENSORS_H_
#include "BC_Accessor_continuous.h"

/*
 * Asserts the minimal amount methods/fields for this Tensor class
 */

template<class T, class Math_lib, class InternalAccessor>
class Tensor_King : public Tensor_Ace {
public:

	InternalAccessor tensor;

	const bool tensor_ownership;
	const bool shape_ownership;

	template<typename ... params>
	Tensor_King(bool ary_own, bool shape_own, params ... fields) :
			tensor(fields...), tensor_ownership(ary_own), shape_ownership(shape_own) {
		/*empty*/
	}
	~Tensor_King<T, Math_lib, InternalAccessor>() {
		if (tensor_ownership)
			Math_lib::destroy(tensor.getData());
		if (shape_ownership)
			Math_lib::destroy(tensor.getShape());
	}

	const InternalAccessor& accessor() const {
		return tensor;
	}
	InternalAccessor& accessor() {
		return tensor;
	}

	int size() const override final {
		return tensor.size();
	}
	int dimension(int index) const override final {
		return tensor.dimension(index);
	}
	int order() const override final {
		return tensor.order();
	}
	int leading_dimension(int index) const override final {
		return tensor.leading_dimension(index);
	}
};

#endif /* SUPERCLASS_TENSORS_H_ */
