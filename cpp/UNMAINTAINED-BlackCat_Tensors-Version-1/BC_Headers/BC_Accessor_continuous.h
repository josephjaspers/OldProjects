/*
 * Accessor.h
 *
 *  Created on: Nov 8, 2017
 *      Author: joseph
 */

#ifndef ACCESSOR_H_
#define ACCESSOR_H_

#include "Tensor_Ace.h"
#include "Accessor_Core.h"
#include <initializer_list>
#include <iostream>
#include <cmath>

/*
 *
 * All sub tensors must inherit from reference or stack accessor
 * and additionally should extend Tensor_Ace or Accessor
 *
 * trivial accessor is an empty class meaning to reflect the derived class
 * is an accessor however it does not define fileds: shape, sz or degree,
 * this is generally in respect to Scalar accessor (which do not need such fields)
 *or vectors which do not need the shape field
 *
 */

template<typename T, typename Math_lib>
struct continuous : accessor_ace<T, Math_lib> {

	static int calculate_size(int* shape, int order) {
		int sz = 1;
		for (int i = 0; i < order; ++i) {
			sz *= shape[i];
		}
		return sz;
	}

	T* data;
	int* shape;
	int degree;

	continuous<T, Math_lib>(T* data, std::initializer_list<int> dims) :
			degree(dims.size()) {

		Math_lib::unified_initialize(shape, dims.size() + 1);
		Math_lib::copy_stack(shape, dims.begin(), dims.size());
		shape[order()] = calculate_size(shape, degree);
		this->data = data;
	}

	continuous<T, Math_lib>(std::initializer_list<int> dims) :
			degree(dims.size()) {

		Math_lib::unified_initialize(shape, dims.size() + 1);
		Math_lib::copy_stack(shape, dims.begin(), dims.size());
		shape[order()] = calculate_size(shape, degree);
		Math_lib::initialize(data, size());
	}

	//this is for subtensor (continuous) construction only
	continuous<T, Math_lib>(T* data, int* shape, int order) :
			degree(order) {
		this->data = data;
		this->shape = shape;
	}

	continuous<T, Math_lib>(accessor_ace<T, Math_lib>& parent) {
		this->data = const_cast<T*>(parent.getData());
		this->shape = const_cast<int*>(parent.getShape());
		this->degree = parent.order();
	}

	int size() const override {
		return shape[order()];
	}
	virtual int dimension(int index) const override {
		return index < order() ? shape[index] : 1;
	}
	virtual int leading_dimension(int index) const override {
		return index < order() ? index > 0 ? shape[index - 1] : 0 : 0;
	}
	int order() const override {
		return degree;
	}
	__attribute__((always_inline)) inline T& operator [](const int& index) {
		return data[index];
	}
	__attribute__((always_inline)) inline const T& operator[](const int& index) const {
		return data[index];
	}
	bool hasShape() const {
		return true;
	}
	const T* getData() const override {
		return data;
	}
	const int* getShape() const override {
		return shape;
	}
	const int* getLeadingDimensionShape() const override {
		return shape;
	}

	T* getData() override {
		return data;
	}
	int* getShape() override {
		return shape;
	}
	int* getLeadingDimensionShape() override {
		return shape;
	}
	virtual ~continuous<T, Math_lib>() = default;

};

#endif /* ACCESSOR_H_ */
