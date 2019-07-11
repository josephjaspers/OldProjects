/*
 * Accessors.h
 *
 *  Created on: Oct 29, 2017
 *      Author: joseph
 */

#ifndef ACCESSORS_H_
#define ACCESSORS_H_

/*
 *
 * Accessors are wrapper classes that are utilized when the data within a Tensor is non-continuous or in the case of a scalar any call to the bracket []
 * which is utilized throughout the buffered system returns the same value
 *
 */
#include"CPU.h"

//Buffer accessor --> handles the computations of two tensors
template<typename T, class lv, class rv, class oper>
struct buffer_accessor {

	oper operation;
	lv left;
	rv right;

	buffer_accessor(const lv l, const rv r) :
			left(l), right(r) {
		/*empty*/
	}
	T operator [](int index) const {
		return operation(left, right, index);
	}
};

//Superclass for most (non-buffer) accessors -- contains methods for general functionality
template<typename T, class Math_lib>
struct std_structure {

	T* ary;
	bool ownership = true;

	std_structure() {
		ary = nullptr;
	}

	std_structure(const std_structure<T, Math_lib>& copy) {
		this->ary = copy.ary;
		this->disable_ownership();
	}

	std_structure<T, Math_lib>(const T* ary) {
		this->ary = const_cast<T*>(ary);
	}

	void assignPtr(T* ary) {
		this->ary = ary;
	}
	T* getPtr() {
		return ary;
	}
	const T* getPtr() const {
		return ary;
	}

	virtual int indexOf(int index)const = 0;

	void initialize(int size) {
		initialize(ary, size);
	}

	void disable_ownership() {
		ownership = false;
	}

	virtual bool isMoveable() = 0;

	virtual T& operator[](int index) = 0;
	const virtual T& operator[](int index) const = 0;

	virtual ~std_structure<T, Math_lib>() {
		if (ownership)
			Math_lib::destroy(ary);
	}
};

template<typename T, class Math_lib>
struct continuous : public std_structure<T, Math_lib> {
	using std_structure<T, Math_lib>::std_structure;

	continuous<T, Math_lib>(int size) {
		this->ary = new T[size];
	}
	continuous<T, Math_lib>(const T* ary) {
		this->ary = const_cast<T*>(ary);
	}
	const T& operator[](int index) const final {
		return this->ary[index];
	}
	T& operator[](int index) {
		return this->ary[index];
	}


	bool isMoveable() {
		return true;
	}
	int indexOf(int index) const {
		return index;
	}
};

template<typename T, class Math_lib>
struct row : public std_structure<T, Math_lib> {
	using std_structure<T, Math_lib>::std_structure;
	int increment = 1;

	row(int increment) {
		this->ary = nullptr;
		this->incremnet = increment;
	}
	row<T, Math_lib>(T* ary, int inc) {
		this->ary = ary;
		this->increment = inc;
	}
	T& operator[](int index) final {
		return this->ary[index * increment];
	}
	const T& operator[](int index) const final {
		return this->ary[index * increment];
	}

	int indexOf(int index) const {
		return increment * index;
	}
};

template<typename T, class Math_lib>
struct singleton : public std_structure<T, Math_lib> {
	using std_structure<T, Math_lib>::std_structure;

	singleton<T, Math_lib>(T* scalar) :
			std_structure<T, Math_lib>(scalar) {
	}

	T& operator[](int index) final {
		return this->ary[0];
	}
	const T& operator[](int index) const final {
		return this->ary[0];
	}
	bool isMoveable() {
		return false;
	}

	int indexOf(int index) const  {
		return 0;
	}
};

template<typename T, class Math_lib>
struct singleton_stack {

	T value;
	singleton_stack<T, Math_lib>(T scalar) {
		value = scalar;
	}

	T operator[](int index) {
		return value;
	}
	const T operator[](int index) const {
		return value;
	}

};
template<typename T, class Math_lib>
struct sub_Matrix : public std_structure<T, Math_lib> {
	int ld_difference;
	int dimension;

	int iteration = -1;

	template<typename ... param>
	sub_Matrix(int dimension, int leading_dimensions, param ... fields) :
			std_structure<T, Math_lib>(fields...) {

		ld_difference = leading_dimensions - dimension; // the difference between the row/column and leading dimension
		this->dimension = dimension;			//the row or column of the matrix (depending if col major or row major)
	}

	T& operator[] (int index) {
		return this->ary[index + (index % dimension) * ld_difference];
	}
	const T& operator[] (int index) const {
		return this->ary[index + (index % dimension) * ld_difference];
	}

	int indexOf(int index) const {
		return index + (index % dimension) * ld_difference;
	}
};

#endif /* ACCESSORS_H_ */
