/*
 * Flags.h
 *
 *  Created on: Nov 10, 2017
 *      Author: joseph
 */

#ifndef FLAGS_H_
#define FLAGS_H_

#include "Accessor_Core.h"

template<class T, class Math_lib>
struct transpose_accessor : accessor_ace<T, Math_lib> {

	static int calculate_size(int* shape, int order) {
		int sz = 1;
		for (int i = 0; i < order; ++i) {
			sz *= shape[i];
		}
		return sz;
	}

	T* data;
	int* shape;
	int* ld;
	int degree;

	transpose_accessor<T, Math_lib>(accessor_ace<T, Math_lib>& parent) {
		data = const_cast<T*>(parent.getData());
		ld = const_cast<int*>(parent.getLeadingDimensionShape());
		shape = const_cast<int*>(parent.getShape());
		degree = parent.order();
	}

	int ld_row() const {
		return ld[0];
	}
	int row() const {
		return shape[1];
	}
	int col() const {
		return shape[0];
	}
	int size() const override {
		return shape[order()];
	}
	int dimension(int index) const override {
		if (index > 1)
			return 1;
		else
			return index == 0 ? shape[1] : shape[0];
	}
	virtual int leading_dimension(int index) const override {
		if (index > 1)
			return 1;
		else
			return index == 0 ? ld[1] : ld[0];
	}
	int order() const override {
		return degree;
	}
	__attribute__((always_inline)) T& operator [](int index) {
		return data[floor(index / row()) + (index % row()) * ld_row()];
	}
	__attribute__((always_inline)) const T& operator[](int index) const {
		return data[(int) floor(index / row()) + (index % row()) * ld_row()];
	}
	bool hasShape() const {
		return true;
	}
	const T* getData() const override {
#ifndef BLACKCAT_DISABLE_TRANSPOSE_WARNINGS
		std::cout << "Warning: transpose accessor method -\"const int* getData() const\" called \n"
				<< "this returns the data (T*) of the original tensor (not the transposed) \n-- Define: BLACKCAT_DISABLE_TRANSPOSE_WARNINGS to disable this message"
				<< std::endl;
#endif
		return data;
	}
	const int* getShape() const override {
#ifndef BLACKCAT_DISABLE_TRANSPOSE_WARNINGS
		std::cout << "Warning: transpose accessor method -\"const int* getShape() const\" called \n"
				<< "this returns the shape (int*) of the original tensor (not the transposed) \n-- Define: BLACKCAT_DISABLE_TRANSPOSE_WARNINGS to disable this message"
				<< std::endl;
#endif
		return shape;
	}
	const int* getLeadingDimensionShape() const override {
#ifndef BLACKCAT_DISABLE_TRANSPOSE_WARNINGS
		std::cout << "Warning: transpose accessor method -\"const int* getLeadingDimensionShape() const\" called \n"
				<< "this returns the leading_dimension (int*) of the original tensor (not the transposed) \n-- Define: BLACKCAT_DISABLE_TRANSPOSE_WARNINGS to disable this message"
				<< std::endl;
#endif
		return shape;
	}
	T* getData() override {
#ifndef BLACKCAT_DISABLE_TRANSPOSE_WARNINGS
		std::cout << "Warning: transpose accessor method -\"const int* getData() const\" called \n"
				<< "this returns the data (T*) of the original tensor (not the transposed) \n-- Define: BLACKCAT_DISABLE_TRANSPOSE_WARNINGS to disable this message"
				<< std::endl;
#endif
		return data;
	}
	int* getShape() override {
#ifndef BLACKCAT_DISABLE_TRANSPOSE_WARNINGS
		std::cout << "Warning: transpose accessor method -\"const int* getShape() const\" called \n"
				<< "this returns the shape (int*) of the original tensor (not the transposed) \n-- Define: BLACKCAT_DISABLE_TRANSPOSE_WARNINGS to disable this message"
				<< std::endl;
#endif
		return shape;
	}
	int* getLeadingDimensionShape() override {
#ifndef BLACKCAT_DISABLE_TRANSPOSE_WARNINGS
		std::cout << "Warning: transpose accessor method -\"const int* getLeadingDimensionShape() const\" called \n"
				<< "this returns the leading_dimension (int*) of the original tensor (not the transposed) \n-- Define: BLACKCAT_DISABLE_TRANSPOSE_WARNINGS to disable this message"
				<< std::endl;
#endif
		return shape;
	}
	virtual ~transpose_accessor<T, Math_lib>() = default;
};

#endif /* FLAGS_H_ */
