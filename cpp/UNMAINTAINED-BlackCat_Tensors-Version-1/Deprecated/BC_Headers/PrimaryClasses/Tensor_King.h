/*
 * Tensor_King.h
 *
 *  Created on: Nov 5, 2017
 *      Author: joseph
 */

#ifndef TENSOR_KING_H_
#define TENSOR_KING_H_

#include "Tensor_Buffers.h"


/*
 *
 * Defines basic pointwise operations for all subclasses
 * Pointwise operations accept a Tensor_Ace type so it can interact with Buffers
 *
 */
template<class T, class Math_lib, class Accessor>
class Tensor_King : public Tensor_King<T, Math_lib, Accessor> {

public:

	template<typename ... params>
	Tensor_King(params... fields) : Tensor_King<T, Math_lib, Accessor>(fields...) {
		/*empty*/
	}

	virtual int size() const = 0;
	virtual int order() const = 0;
	virtual int order(int index) const = 0;

	virtual ~Tensor_King() = default;

	template<class U, class access> Buffer<T, Math_lib, Accessor, access, Operation::add<T>> operator +(const Tensor_King<U, Math_lib, access>& vec) const;
	template<class U, class access> Buffer<T, Math_lib, Accessor, access, Operation::sub<T>> operator -(const Tensor_King<U, Math_lib, access>& vec) const;
	template<class U, class access> Buffer<T, Math_lib, Accessor, access, Operation::div<T>> operator /(const Tensor_King<U, Math_lib, access>& vec) const;
	template<class U, class access> Buffer<T, Math_lib, Accessor, access, Operation::mul<T>> operator %(const Tensor_King<U, Math_lib, access>& vec) const;

	//assumes unknown type is a stack_scalar
	Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::add<T>> operator +(T scalar) const;
	Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::sub<T>> operator -(T scalar) const;
	Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::div<T>> operator /(T scalar) const;
	Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::mul<T>> operator %(T scalar) const;
};


template<class T, class Math_lib, class Accessor>
template<class U, class access>
Buffer<T, Math_lib, Accessor, access, Operation::add<T>> Tensor_King<T, Math_lib, Accessor>::operator +(const Tensor_King<U, Math_lib, access>& vec) const {
	return Buffer<T, Math_lib, Accessor, access, Operation::add<T>>(this->accessor(), vec.accessor(), size());
}
template<class T, class Math_lib, class Accessor>
template<class U, class access>
Buffer<T, Math_lib, Accessor, access, Operation::sub<T>> Tensor_King<T, Math_lib, Accessor>::operator -(const Tensor_King<U, Math_lib, access>& vec) const {
	return Buffer<T, Math_lib, Accessor, access, Operation::sub<T>>(this->accessor(), vec.accessor(), size());
}
template<class T, class Math_lib, class Accessor>
template<class U, class access>
Buffer<T, Math_lib, Accessor, access, Operation::div<T>> Tensor_King<T, Math_lib, Accessor>::operator /(const Tensor_King<U, Math_lib, access>& vec) const {
	return Buffer<T, Math_lib, Accessor, access, Operation::div<T>>(this->accessor(), vec.accessor(), size());
}
template<class T, class Math_lib, class Accessor>
template<class U, class access>
Buffer<T, Math_lib, Accessor, access, Operation::mul<T>> Tensor_King<T, Math_lib, Accessor>::operator %(const Tensor_King<U, Math_lib, access>& vec) const {
	return Buffer<T, Math_lib, Accessor, access, Operation::mul<T>>(this->accessor(), vec.accessor(), size());
}

template<class T, class Math_lib, class Accessor>
Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::add<T>> Tensor_King<T, Math_lib, Accessor>::operator +(T scalar) const {
	return Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::add<T>>(this->accessor(), singleton_stack<T, Math_lib>(scalar), size());
}

template<class T, class Math_lib, class Accessor>
Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::sub<T>> Tensor_King<T, Math_lib, Accessor>::operator -(T scalar) const {
	return Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::sub<T>>(this->accessor(), singleton_stack<T, Math_lib>(scalar), size());
}

template<class T, class Math_lib, class Accessor>
Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::div<T>> Tensor_King<T, Math_lib, Accessor>::operator /(T scalar) const {
	return Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::div<T>>(this->accessor(), singleton_stack<T, Math_lib>(scalar), size());
}

template<class T, class Math_lib, class Accessor>
Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::mul<T>> Tensor_King<T, Math_lib, Accessor>::operator %(T scalar) const {
	return Buffer<T, Math_lib, Accessor, singleton_stack<T, Math_lib>, Operation::mul<T>>(this->accessor(), singleton_stack<T, Math_lib>(scalar), size());
}

#endif /* TENSOR_KING_H_ */
