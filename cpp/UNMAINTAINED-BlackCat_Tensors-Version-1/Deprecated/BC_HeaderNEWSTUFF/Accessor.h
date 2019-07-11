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
template <typename T, class lv, class rv, class oper>
struct buffer_accessor {

	oper operation;
	const rv right;
	const lv left;

	buffer_accessor(const lv l, const rv r) : left(l), right(r) {

	}
	T operator [] (int index) const {
		return operation(left[index, right[index]]);
	}
};

template<typename T, class destructor>
struct std_structure {
	T* ary;

	std_structure() {
		ary = nullptr;
	}
	std_structure<T, destructor>(T* ary) {
		this->ary = ary;
	}
	std_structure<T, destructor>(int array_sz) {
		this->ary = new T[sz];
	}


	void assignPtr(T* ary) {
		this->ary = ary;
	}
	T* getPtr() {
		return ary;
	}

	template<typename Math_lib>
	void initialize(int size) {
		Math_lib::initialize(ary, size);
	}


	virtual bool isMoveable() = 0;

	virtual T& operator[](int index) = 0;
	const virtual T& operator[](int index) const = 0;

	virtual ~std_structure<T, destructor>() {
		destructor::finish(ary);
	}
};

template<typename T, class destructor>
struct continuous : public std_structure<T,destructor> {
	using std_structure<T, destructor>::std_structure;

	T& operator[](int index) final {
		return this->ary[index];
	}
	const T& operator[](int index) const final {
		return this->ary[index];
	}
	bool isMoveable() {
		return true;
	}
};

template<typename T, class Math_lib>
struct row : public std_structure<T,Math_lib> {
	using std_structure<T, destructor>::std_structure;
	int increment = 1;

	row(int increment) {
		this->ary = nullptr;
		this->incremnet = increment;
	}
	row<T, destructor>(T* ary, int inc) {
		this->ary = ary;
		this->increment = inc;
	}
	T& operator[](int index) final {
		return this->ary[index * increment];
	}
	const T& operator[](int index) const final {
		return this->ary[index * increment];
	}
};

template<typename T, class destructor>
struct singleton : public std_structure<T, destructor> {
	using std_structure<T, destructor>::std_structure;

	T& operator[](int index) final {
		return this->ary[0];
	}
	const T& operator[](int index) const final {
		return this->ary[0];
	}
	bool isMoveable() {
		return false;
	}
};

#endif /* ACCESSORS_H_ */
