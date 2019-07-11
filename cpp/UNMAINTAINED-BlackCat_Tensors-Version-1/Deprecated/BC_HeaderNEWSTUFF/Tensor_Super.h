/*
 * Tensor_Super.h
 *
 *  Created on: Nov 4, 2017
 *      Author: joseph
 */

#ifndef TENSOR_SUPER_H_
#define TENSOR_SUPER_H_

template<
	typename T,
	class Math_lib,

	template<
		class type,
		class Math_lib_same,
		class destructor>
	class Accessor,
	class Destructor>
class Tensor_King {
public:
	Accessor tensor;

	int size() const = 0;
	int rank() const = 0;
	int rank(int id) const = 0;
	int rows() const = 0;
	int cols() const = 0;
	int depth() const = 0;

};

template<typename T, class Math_lib, class Accessor, class Destructor>
class Tensor_King : public Tensor_King<T, Math_lib, Accessor<T, Math_lib, typename Destructor>, Destructor> {
public:

	int order;
	int* shape;			//unified memory
	Accessor tensor;	//Accessor tensor

};

#endif /* TENSOR_SUPER_H_ */
