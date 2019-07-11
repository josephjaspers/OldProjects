/*
 * General_Accessor.h
 *
 *  Created on: Nov 9, 2017
 *      Author: joseph
 */

#ifndef GENERAL_ACCESSOR_H_
#define GENERAL_ACCESSOR_H_

#include "BC_Accessor_continuous.h"

class Operation {

	//--------------------------Operations for buffers, they work best with continuous Tensors, though non-continuous functors work as well -------------------//
	template<typename T>
	struct mul {
		template<typename lv, typename rv>
		__attribute__((always_inline)) static T calc(const lv& left, const rv& right) {
			return left * right;
		}
		template<typename lv, typename rv>
		__attribute__((always_inline)) static void calc(T& to, const lv& left, const rv& right) {
			to = left * right;
		}
	};
	template<typename T>
	struct div {
		template<typename lv, typename rv>
		__attribute__((always_inline)) static T calc(const lv& left, const rv& right) {
			return left / right;
		}
		template<typename lv, typename rv>
		__attribute__((always_inline)) static void calc(T& to, const lv& left, const rv& right) {
			to = left / right;
		}
	};
	template<typename T>
	struct add {
		template<typename lv, typename rv>
		__attribute__((always_inline)) static inline T calc(const lv& left, const rv& right) {
			return left + right;
		}
		template<typename lv, typename rv>
		__attribute__((always_inline)) static void calc(T& to, const lv& left, const rv& right) {
			to = left + right;
		}
	};
	template<typename T>
	struct sub {
		template<typename lv, typename rv>
		__attribute__((always_inline)) static T calc(const lv& left, const rv& right) {
			return left - right;
		}
		template<typename lv, typename rv>
		__attribute__((always_inline)) static void calc(T& to, const lv& left, const rv& right) {
			to = left - right;
		}
	};
};

template<typename T, typename Math_lib, class... operation>
struct buffer : accessor_ace<T, Math_lib> {


	__attribute__((always_inline)) buffer<T, Math_lib, lv, rv, operation>(lv l, rv r) :
			left(l), right(r) {
	}
	/*
	 * We utilize the max function to retun the max of the general accessor (size, dimension, etc)
	 * This is to handle cases where one of the sides is a scalar and the other is a tensor of some unknown dimension
	 *
	 * Alternatively I may just create a template specific version to handle Scalars, however this is the easiest method currently
	 * for purely pointwise operations --- other operations IE dotproduct will have a unique buffer type
	 */
	static int max(int a, int b) {
		return a > b ? a : b;
	}
	int size() const override {
		return max(left.size(), right.size());
	}
	int dimension(int index) const override {
		return max(left.dimension(index), right.dimension(index));
	}
	int leading_dimension(int index) const override {
		return max(left.leading_dimension(index), right.leading_dimension(index));
	}
	int order() const override {
		return max(left.order(), right.order());
	}
	__attribute__((always_inline)) T operator [](const int& index) const {
		return operation::calc(left[index], right[index]);
	}
	const T* getData() const {
		throw std::invalid_argument("attempting to call getData on Buffer -bug in code");
	}
	const int* getShape() const {
		throw std::invalid_argument("attempting to call getShape on Buffer -bug in code");
	}
	const int* getLeadingDimensionShape() const {
		throw std::invalid_argument("attempting to call getLeadingShape on Buffer -bug in code");
	}
	T* getData() {
		throw std::invalid_argument("attempting to call getData on Buffer -bug in code");
	}
	int* getShape() {
		throw std::invalid_argument("attempting to call getShape on Buffer -bug in code");
	}
	int* getLeadingDimensionShape() {
		throw std::invalid_argument("attempting to call getLeadingShape on Buffer -bug in code");
	}
	virtual ~buffer<T, Math_lib, lv, rv, operation>() = default;
};

#endif /* GENERAL_ACCESSOR_H_ */
