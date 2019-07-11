/*
 * Accessor_Kings.h
 *
 *  Created on: Nov 8, 2017
 *      Author: joseph
 */

#ifndef ACCESSOR_KINGS_H_
#define ACCESSOR_KINGS_H_

#include "BC_Accessor_continuous.h"

//abstract
template<typename T, typename Math_lib>
struct Scalar_Accessor : accessor_ace<T, Math_lib> {

	int size() const {
		return 1;
	}
	int dimension(int index) const {
		return 1;
	}
	int leading_dimension(int index) const {
		return 0;
	}
	int order() const {
		return 1;
	}
	bool hasShape() const {
		return false;
	}

	const int* getShape() const override {
		return nullptr;
	}
	const int* getLeadingDimensionShape() const override {
		return nullptr;
	}
};

template<typename T, typename Math_lib>
struct StackScalarAccessor : public Scalar_Accessor<T, Math_lib>, public value_accessor<T, Math_lib> {

	T scalar;

	StackScalarAccessor<T, Math_lib>(T s) :
			scalar(s) {
	}
	;

	int size() const {
		return 1;
	}
	int dimension(int index) const {
		return 1;
	}
	int leading_dimension(int index) const {
		return 0;
	}
	int order() const {
		return 1;
	}
	bool hasShape() const {
		return false;
	}

	T operator[](int index) override {
		return scalar;
	}
	const T operator[](int index) const override {
		return scalar;
	}

	const T* getData() const {
		throw std::invalid_argument("getData called on StackScalarAccessor bug");
	}
	const int* getShape() const override {
		return nullptr;
	}
	const int* getLeadingDimensionShape() const override {
		return nullptr;
	}
	T* getData() {
		throw std::invalid_argument("getData called on StackScalarAccessor bug");
	}
	int* getShape() override {
		return nullptr;
	}
	int* getLeadingDimensionShape() override {
		return nullptr;
	}
};

template<typename T, typename Math_lib>
struct ReferenceScalarAccessor : public Scalar_Accessor<T, Math_lib>, public reference_accessor<T, Math_lib> {

	T* scalar;
	ReferenceScalarAccessor<T, Math_lib>(T* s) :
			scalar(s) {
	}
	;

	int size() const {
		return 1;
	}
	int dimension(int index) const {
		return 1;
	}
	int leading_dimension(int index) const {
		return 0;
	}
	int order() const {
		return 1;
	}
	bool hasShape() const {
		return false;
	}

	T& operator [](int index) {
		return *scalar;
	}
	const T& operator[](int index) const {
		return *scalar;
	}

	const T* getData() const override {
		return scalar;
	}
	const int* getShape() const override {
		return nullptr;
	}
	const int* getLeadingDimensionShape() const override {
		return nullptr;
	}

	T* getData() override {
		return scalar;
	}
	int* getShape() override {
		return nullptr;
	}
	int* getLeadingDimensionShape() override {
		return nullptr;
	}
};

#endif /* ACCESSOR_KINGS_H_ */
