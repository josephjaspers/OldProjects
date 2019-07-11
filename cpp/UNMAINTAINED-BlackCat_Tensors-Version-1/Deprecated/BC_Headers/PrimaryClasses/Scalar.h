/*
 * Scalar.h
 *
 *  Created on: Oct 27, 2017
 *      Author: joseph
 */

#ifndef BlackCat_SCALAR_H_
#define BlackCat_SCALAR_H_
#include <iostream>
#include "Tensor_King.h"


/*
 * Scalar is class that is only accessible through indexing a Vector with [].
 * The internal data references that same as the given index of the original Vector
 */
template <class T, class Math_lib>
class Id_Scalar : public Tensor_King<T, Math_lib, singleton<T,Math_lib>>{

protected:

	template<class T2, class Ml, template<class, class> class A>
	friend class Vector;

	Id_Scalar<T, Math_lib>(T* value) : Tensor_King<T, Math_lib, singleton<T, Math_lib>>(value) {
		this->accessor().disable_ownership();
	}

public:


	~Id_Scalar<T, Math_lib>() = default;

	//modify this print method later
	void print() const { Math_lib::print(this->accessor(), 1, 5); }

	int size() const { return 1; }
	int order() const { return 0; }
	int order(int index) const { return 1; }
};

/*
 * Same as above but only from a value given from the stack. Although the mathlib defaults to CPU --
 * the class is trivially copy-able and therefor can integrate with other math_libs
 *
 * The purpose of this class is to be able to do operations such as (1 - a)
 * Where 1 is cast to a Scalar, and therefor you do not need to generate a Tensor and fill with 1s to generate a Tensor of
 * size a with values equal to 1 - a.
 */
template<class T = double, class Math_lib = CPU_MATHEMATICS>
class Scalar : public Tensor_King<T, Math_lib, singleton_stack<T, Math_lib>> {
	public:

	Scalar<T,Math_lib>(T value) : Tensor_King<T, Math_lib, singleton_stack<T, Math_lib>>(value) {}

	~Scalar<T,Math_lib>() = default;
	void print() {
		std::cout << (this->accessor().scalar) << std::endl;
	}
	int size() const { return 1; }
	int order() const { return 0; }
	int order(int index) const { return 1; }
	void print() const { Math_lib::print(this->accessor(), 1, 5); }

};
#endif
