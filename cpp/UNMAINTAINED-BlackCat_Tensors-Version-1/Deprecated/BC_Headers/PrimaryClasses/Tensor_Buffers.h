/*
 * OperationBuffer_PointwiseMeat.h
 *
 *  Created on: Oct 27, 2017
 *      Author: joseph
 */

#ifndef OPERATIONBUFFER_POINTWISEMEAT_H_
#define OPERATIONBUFFER_POINTWISEMEAT_H_

#include "Tensor_Ace.h"
#include "Accessors.h"

class Operation {

	//--------------------------Operations for buffers, they work best with continuous Tensors, though non-continuous functors work as well -------------------//
	template<typename T>
	struct mul {
		template<typename lv, typename rv>
		T operator ()(const lv left, const rv right, int index) const {
			return left[index] * right[index];
		}
	};
	template<typename T>
	struct div {
		template<typename lv, typename rv>
		T operator ()(const lv left, const rv right, int index) const {
			return left[index] / right[index];
		}
	};
	template<typename T>
	struct add {
		template<typename lv, typename rv>
		T operator()(const lv left, const rv right, int index) const {
			return left[index] + right[index];

		}
	};
	template<typename T>
	struct sub {
		template<typename lv, typename rv>
		inline T operator ()(const lv left, const rv right, int index) const {
			return left[index] - right[index];
		}
	};
};

template<typename T, typename Math_lib, typename lv, typename rv, typename oper>
struct Buffer : Tensor_King<T, Math_lib, buffer_accessor<T, lv, rv, oper>> {

	int sz;



	Buffer<T, Math_lib, lv, rv, oper>(const lv left, const rv right, int size) :
			Tensor_King<T, Math_lib, buffer_accessor<T, lv, rv, oper>>(left, right) {
		this->sz = size;
	}

	virtual ~Buffer<T, Math_lib, lv, rv, oper>() = default;

	int size() const;
	int order() const;
	int order(int id) const;
	//---------------------------------------------------------------------Buffer by Tensor Operations ---------------------------------------------------/
	template<class U, class access> Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::add<T>> operator +(const Tensor_King<U, Math_lib, access>& add);
	template<class U, class access> Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::sub<T>> operator -(const Tensor_King<U, Math_lib, access>& sub);
	template<class U, class access> Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::mul<T>> operator %(const Tensor_King<U, Math_lib, access>& mul);
	template<class U, class access> Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::div<T>> operator /(const Tensor_King<U, Math_lib, access>& div);

	template<class U> Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<U, Math_lib>, Operation::add<T>> operator +(U scalar) const;
	template<class U> Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<U, Math_lib>, Operation::sub<T>> operator -(U scalar) const;
	template<class U> Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<U, Math_lib>, Operation::div<T>> operator /(U scalar) const;
	template<class U> Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<U, Math_lib>, Operation::mul<T>> operator %(U scalar) const;

};

template<class T, class Math_lib, class lv, class rv, class oper>
int Buffer<T, Math_lib, lv, rv, oper>::size() const {
	return sz;
}

template<class T, class Math_lib, class lv, class rv, class oper>
int Buffer<T, Math_lib, lv, rv, oper>::order() const {
	return 1;
}

template<class T, class Math_lib, class lv, class rv, class oper>
int Buffer<T, Math_lib, lv, rv, oper>::order(int id) const {
	return 1;
}

template<class T, class Math_lib, class lv, class rv, class oper>
template<class U, class access>
Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::add<T>> Buffer<T, Math_lib, lv, rv, oper>::operator +(const Tensor_King<U, Math_lib, access>& add) {
	this->assert_same_size(add);
	return Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::add<T>>(this->accessor(), add.accessor(), sz);
}

template<class T, class Math_lib, class lv, class rv, class oper>
template<class U, class access>
Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::sub<T>> Buffer<T, Math_lib, lv, rv, oper>::operator -(const Tensor_King<U, Math_lib, access>& sub) {
	this->assert_same_size(sub);
	return Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::sub<T>>(this->accessor(), sub.accessor(), sz);
}

template<class T, class Math_lib, class lv, class rv, class oper>
template<class U, class access>
Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::mul<T>> Buffer<T, Math_lib, lv, rv, oper>::operator %(const Tensor_King<U, Math_lib, access>& mul) {
	this->assert_same_size(mul);
	return Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::mul<T>>(this->accessor(), mul.accessor(), sz);
}

template<class T, class Math_lib, class lv, class rv, class oper>
template<class U, class access>
Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::div<T>> Buffer<T, Math_lib, lv, rv, oper>::operator /(const Tensor_King<U, Math_lib, access>& div) {
	this->assert_same_size(div);
	return Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, access, Operation::div<T>>(this->accessor(), div.accessor(), sz);
}

template<class T, class Math_lib, class lv, class rv, class oper>
template<class U>
Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<U, Math_lib>, Operation::add<T>> Buffer<T, Math_lib, lv, rv, oper>::operator +(U scalar) const {
	return Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<T, Math_lib>, Operation::add<T>>(this->accessor(), singleton_stack<U, Math_lib>(scalar), sz);
}

template<class T, class Math_lib, class lv, class rv, class oper>
template<class U>
Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<U, Math_lib>, Operation::sub<T>> Buffer<T, Math_lib, lv, rv, oper>::operator -(U scalar) const {
	return Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<T, Math_lib>, Operation::sub<T>>(this->accessor(), singleton_stack<U, Math_lib>(scalar), sz);
}

template<class T, class Math_lib, class lv, class rv, class oper>
template<class U>
Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<U, Math_lib>, Operation::div<T>> Buffer<T, Math_lib, lv, rv, oper>::operator /(U scalar) const {
	return Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<T, Math_lib>, Operation::div<T>>(this->accessor(), singleton_stack<U, Math_lib>(scalar), sz);
}

template<class T, class Math_lib, class lv, class rv, class oper>
template<class U>
Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<U, Math_lib>, Operation::mul<T>> Buffer<T, Math_lib, lv, rv, oper>::operator %(U scalar) const {
	return Buffer<T, Math_lib, buffer_accessor<T, lv, rv, oper>, singleton_stack<T, Math_lib>, Operation::mul<T>>(this->accessor(), singleton_stack<U, Math_lib>(scalar), sz);
}

#endif /* OPERATIONBUFFER_POINTWISEMEAT_H_ */
