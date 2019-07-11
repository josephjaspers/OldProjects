#ifndef Tq_h
#define Tq_h

#include "Tensor_King.h"
#include "BC_Accessor_Buffer.h"
#include "BC_Accessor_continuous.h"
#include "BC_Accessor_transpose.h"
#include "CPU.h"
#include <initializer_list>

template<
class T,
class Math_lib = CPU_MATHEMATICS,
class std_access = continuous<T, Math_lib>>

class Tensor_Queen : public Tensor_King<T, Math_lib, std_access> {
public:

	using Tensor_King<T, Math_lib, std_access>::tensor;

	//-------------------------------------------------------------Constructors -------------------------------------------------------------//

	//-------------------------------------------------------------General Methods--------------------------------------------------------------------//

	void fill(T value);
	void zero();
	void randomize(T lb, T ub);

	void print() const;
	void print(int precision) const;

	Tensor_Queen<T, Math_lib, std_access>(std::initializer_list<int> dims) :
			Tensor_King<T, Math_lib, std_access>(true, true, dims) {
	}

	//some type of subtensor constructor -- ergo will never own tensor, possibly own ranks,
	template<typename ... params>
	Tensor_Queen<T, Math_lib, std_access>(bool rank_ownership, params ... p) :
			Tensor_King<T, Math_lib, std_access>(false, rank_ownership, p...) {
	}

	//-------------------------------------------------------------Math Operators-------------------------------------------------------------//
	template<class U, class A>
	Tensor_Queen<T, Math_lib, continuous<T, Math_lib>> operator *(const Tensor_Queen<U, Math_lib, A>& te) {
		if (this->order() > 2 || te.order() > 2) {
			throw std::invalid_argument("dot product undefined for tensors with order > 2");
		}
		if (this->dimension(1) != te.dimension(0)) {
			throw std::invalid_argument("this->cols() != param.rows() -- invalid dot product dimensions");
		}

		Tensor_Queen<T, Math_lib, continuous<T, Math_lib>> mul({this->dimension(0), te.dimension(1)});
		mul.zero();
		Math_lib::matmul(mul.accessor(), this->accessor(), this->dimension(0), this->dimension(1), te.accessor(), te.dimension(1));
		return mul;
	}

	template<class A>
	Tensor_Queen<T, Math_lib, continuous<T, Math_lib>> operator *(const Tensor_Queen<T, Math_lib, A>& te) {
		if (this->order() > 2 || te.order() > 2) {
			throw std::invalid_argument("dot product undefined for tensors with order > 2");
		}
		if (this->dimension(1) != te.dimension(0)) {
			throw std::invalid_argument("this->cols() != param.rows() -- invalid dot product dimensions");
		}

		Tensor_Queen<T, Math_lib, continuous<T, Math_lib>> mul({this->dimension(0), te.dimension(1)});
		mul.zero();
		Math_lib::matmulBLAS(const_cast<T*>(mul.accessor().getData()), this->accessor().getData(), this->dimension(0), this->dimension(1), te.accessor().getData(), te.dimension(1));
		return mul;
	}

	Tensor_Queen<T, Math_lib, transpose_accessor<T, Math_lib>> t() {
		return Tensor_Queen<T, Math_lib, transpose_accessor<T, Math_lib>>(false, this->accessor());
	}

	template<class U, class A>
	Tensor_Queen<T, Math_lib, buffer<T, Math_lib, std_access, A, Operation::add<T>>> operator + (const Tensor_Queen<U, Math_lib, A>& te)
	{
		return Tensor_Queen<T, Math_lib, buffer<T, Math_lib, std_access, A, Operation::add<T>>>(false, tensor, te.tensor);
	}

	template<class U, class A>
	Tensor_Queen<T, Math_lib, buffer<T, Math_lib, std_access, A, Operation::sub<T>>> operator - (const Tensor_Queen<U, Math_lib, A>& te)
	{
		return Tensor_Queen<T, Math_lib, buffer<T, Math_lib, std_access, A, Operation::sub<T>>>(false, tensor, te.tensor);
	}
	template<class U, class A>
	Tensor_Queen<T, Math_lib, buffer<T, Math_lib, std_access, A, Operation::div<T>>> operator / (const Tensor_Queen<U, Math_lib, A>& te)
	{
		return Tensor_Queen<T, Math_lib, buffer<T, Math_lib, std_access, A, Operation::div<T>>>(false, tensor, te.tensor);
	}
	template<class U, class A>
	Tensor_Queen<T, Math_lib, buffer<T, Math_lib, std_access, A, Operation::mul<T>>> operator % (const Tensor_Queen<U, Math_lib, A>& te)
	{
		return Tensor_Queen<T, Math_lib, buffer<T, Math_lib, std_access, A, Operation::mul<T>>>(false, tensor, te.tensor);
	}

	//-------------------------------------------------------------Assignment Operators-------------------------------------------------------------//

	Tensor_Queen<T, Math_lib, std_access>& operator =(const Tensor_Queen<T, Math_lib, std_access>& ary);
	template<class U, class A> Tensor_Queen<T, Math_lib, std_access>& operator =(const Tensor_Queen<U, Math_lib, A>& ary);

	//-------------------------------------------------------------Point-wise operators-------------------------------------------------------------//

};

template<class T, class Math_lib, class std_access>
void Tensor_Queen<T, Math_lib, std_access>::fill(T value) {
	Math_lib::fill(tensor, value, this->size());
}

template<class T, class Math_lib, class std_access>
void Tensor_Queen<T, Math_lib, std_access>::zero() {
	Math_lib::zero(tensor, this->size());
}
template<class T, class Math_lib, class std_access>
void Tensor_Queen<T, Math_lib, std_access>::randomize(T lb, T ub) {
	Math_lib::randomize(tensor, lb, ub, this->size());
}
template<class T, class Math_lib, class std_access>
void Tensor_Queen<T, Math_lib, std_access>::print() const {
	tensor.hasShape() ? Math_lib::print(tensor, tensor.getShape(), this->order(), 5) : Math_lib::print(tensor, this->size(), 5);
}
template<class T, class Math_lib, class std_access>
void Tensor_Queen<T, Math_lib, std_access>::print(int precision) const {
	tensor.hasShape() ? Math_lib::print(tensor, tensor.getShape(), this->order(), precision) : Math_lib::print(tensor, this->size(), precision);
}

template<class T, class Math_lib, class std_access>
Tensor_Queen<T, Math_lib, std_access>& Tensor_Queen<T, Math_lib, std_access>::operator =(const Tensor_Queen<T, Math_lib, std_access>& ary) {
	this->assert_same_size(ary);
	Math_lib::copy(tensor.accessor().getData(), ary.accessor(), this->size());
	return *this;
}

template<class T, class Math_lib, class std_access>
template<typename U, class A>
Tensor_Queen<T, Math_lib, std_access>& Tensor_Queen<T, Math_lib, std_access>::operator =(const Tensor_Queen<U, Math_lib, A>& ary) {
	this->assert_same_size(ary);
	Math_lib::copy(this->tensor.data, ary.accessor(), this->size());
	return *this;
}

#endif
