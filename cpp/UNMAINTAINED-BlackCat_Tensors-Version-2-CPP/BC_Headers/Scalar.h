/*
 * Scalar.h
 *
 *  Created on: Aug 15, 2017
 *      Author: joseph
 */

#ifndef SCALAR_H_
#define SCALAR_H_
#include "BLACKCAT_CPU_MATHEMATICS.h"
#include "CPU.h"

#include <iostream>
template<typename number_type, typename TensorOperations = CPU>
class Scalar {

protected:
	template<typename a, typename b>
	friend class Tensor;

	bool ownership = true;
	number_type* scalar;

public:
	Scalar<number_type, TensorOperations>(number_type* value, bool owns) { scalar = value; ownership = owns;}
	Scalar<number_type, TensorOperations>(const Scalar& s);
	Scalar<number_type, TensorOperations>(Scalar&& s);
	explicit Scalar<number_type, TensorOperations>(number_type);
	Scalar<number_type, TensorOperations>() {
		TensorOperations::unified_initialize(scalar, 1);
	}
	Scalar<number_type, TensorOperations>& operator =(const Scalar<number_type, TensorOperations>& s);
	Scalar<number_type, TensorOperations>& operator =(number_type s);
	Scalar<number_type, TensorOperations>& operator =(Scalar<number_type, TensorOperations> && s);

	~Scalar<number_type, TensorOperations>() {
		if (ownership)
			if(scalar)
				TensorOperations::destruction(scalar);
	}
	//Access data
	//dereferences pointer --- does not work well with Cuda
	const number_type& operator ()() const {
		return this->scalar[0];
	}

	number_type& operator ()() {
		return this->scalar[0];
	}

	number_type get() const {
		number_type t;
		TensorOperations::port_copy_device_to_host(&t, scalar, 1);
		return t;
	}

	//Mathematics operators (By scalar)
	Scalar<number_type, TensorOperations> operator^(const Scalar<number_type, TensorOperations>& t) const;
	Scalar<number_type, TensorOperations> operator/(const Scalar<number_type, TensorOperations>& t) const;
	Scalar<number_type, TensorOperations> operator+(const Scalar<number_type, TensorOperations>& t) const;
	Scalar<number_type, TensorOperations> operator-(const Scalar<number_type, TensorOperations>& t) const;
	Scalar<number_type, TensorOperations> operator&(const Scalar<number_type, TensorOperations>& t) const;

	Scalar<number_type, TensorOperations>& operator^=(const Scalar<number_type, TensorOperations>& t);
	Scalar<number_type, TensorOperations>& operator/=(const Scalar<number_type, TensorOperations>& t);
	Scalar<number_type, TensorOperations>& operator+=(const Scalar<number_type, TensorOperations>& t);
	Scalar<number_type, TensorOperations>& operator-=(const Scalar<number_type, TensorOperations>& t);
	Scalar<number_type, TensorOperations>& operator&=(const Scalar<number_type, TensorOperations>& t);



	void print() const {
		std::cout << "[" << *scalar << "]" << std::endl;
	}
	;
	void printDimensions() const {
		std::cout << "[1]" << std::endl;
	}
	;

	number_type* data() {
		return scalar;
	}
	const number_type* data() const {
		return scalar;
	}
};
#endif /* SCALAR_H_ */
