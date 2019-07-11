#include "Tensor_King.h"
#include "Tensor_Buffers.h"
#ifndef Tq_h
#define Tq_h

#include <vector>
template<class T, class Math_lib, class Accessor>
class Tensor_Queen : public Tensor_King<T, Math_lib, Accessor> {
protected:

	using Tensor_King<T, Math_lib, Accessor>::tensor;
	typedef std::vector<int> shape;
	int degree;
	int* rank = nullptr;
	int sz;

	const bool shape_ownership;

public:

	//-------------------------------------------------------------Constructors -------------------------------------------------------------//

	//humble destructor
	~Tensor_Queen<T, Math_lib, Accessor>() {
		if (shape_ownership) {
			delete[] rank;
		}
	}

	//Basic Vector
	Tensor_Queen(int m) :
			Tensor_King<T, Math_lib, Accessor>(m), shape_ownership(true) {

		this->sz = m;
		//Math_lib::unified_initialize(shape, 1);
		rank = new int[1];
		rank[0] = sz;
		degree = 1;
	}

	//Basic Matrix
	Tensor_Queen(int m, int n) :
			Tensor_King<T, Math_lib, Accessor>(m * n), shape_ownership(true) {

		this->sz = m * n;
		//Math_lib::unified_initialize(shape, 2);
		rank = new int[2];
		rank[0] = m;
		rank[1] = n;
		degree = 2;
	}

	//index Tensor -- >> essentially a recursive super_class constructor --always called for generating an index tensor
	//this does not apply to vectors generating scalars
	template<typename A>
	Tensor_Queen(const Tensor_Queen<T, Math_lib, A>& super, int index) :
			Tensor_King<T, Math_lib, Accessor>(&super.accessor()[index]), shape_ownership(false) {

		this->sz = super.rank[super.degree - 2];
		//Math_lib::unified_initialize(shape, 1p);
		rank = super.rank;
		degree = super.degree - 1;

		this->accessor().disable_ownership();
	}

	//sub-tensor constructor -- is always called for the generation of a sub-tensor
	template<typename A, typename ... params>
	Tensor_Queen(const Tensor_Queen<T, Math_lib, A>& super, int index, shape sub_shape, params&... fields) :
			Tensor_King<T, Math_lib, Accessor>(&super.accessor()[index], fields...), shape_ownership(true) {

		sz = 1;
		for (unsigned i = 0; i < sub_shape.size(); ++i) {
			sz *= sub_shape[i];
		}

		//Math_lib::unified_initialize(shape, sub_shape.size());
		rank = new int[sub_shape.size()];
		Math_lib::copy(rank, sub_shape, sub_shape.size());
		degree = sub_shape.size();

		this->accessor().disable_ownership();
	}

	//-------------------------------------------------------------General Methods--------------------------------------------------------------------//
	void fill(T value);
	void zero();
	void print();
	void print(int precision);

	void randomize(T lb, T ub) {
		Math_lib::randomize(tensor, lb, ub, sz);
	}

	int size() const;
	int order() const;
	int order(int index) const;

	//-------------------------------------------------------------Assignment Operators-------------------------------------------------------------//

	Tensor_Queen<T, Math_lib, Accessor>& operator =(const Tensor_Queen<T, Math_lib, Accessor>& ary);

	template<class U, class A> Tensor_Queen<T, Math_lib, Accessor>& operator =(const Tensor_King<U, Math_lib, A>& ary);
	template<class U, class A> Tensor_Queen<T, Math_lib, Accessor>& operator =(const Tensor_Queen<U, Math_lib, A>& ary);

	template<class U> Tensor_Queen<T, Math_lib, Accessor>& operator =(const Id_Scalar<U, Math_lib>& ary);
	template<class U> Tensor_Queen<T, Math_lib, Accessor>& operator =(const U& data);
	Tensor_Queen<T, Math_lib, Accessor>& operator =(T scalar);

	//-------------------------------------------------------------Point-wise operators-------------------------------------------------------------//

};

template<class T, class Math_lib, class Accessor>
int Tensor_Queen<T, Math_lib, Accessor>::size() const {
	return sz;
}

template<class T, class Math_lib, class Accessor>
int Tensor_Queen<T, Math_lib, Accessor>::order() const {
	return degree;
}

template<class T, class Math_lib, class Accessor>
int Tensor_Queen<T, Math_lib, Accessor>::order(int index) const {
	return rank[index];
}

template<class T, class Math_lib, class Accessor>
void Tensor_Queen<T, Math_lib, Accessor>::fill(T value) {
	Math_lib::fill(tensor, value, sz);
}

template<class T, class Math_lib, class Accessor>
void Tensor_Queen<T, Math_lib, Accessor>::zero() {
	Math_lib::zero(tensor, this->size());
}

template<class T, class Math_lib, class Accessor>
void Tensor_Queen<T, Math_lib, Accessor>::print() {
	Math_lib::print(tensor, rank, degree, 5);
}
template<class T, class Math_lib, class Accessor>
void Tensor_Queen<T, Math_lib, Accessor>::print(int precision) {
	Math_lib::print(tensor, rank, degree, precision);
}

template<class T, class Math_lib, class Accessor>
template<class U, class A>
Tensor_Queen<T, Math_lib, Accessor>& Tensor_Queen<T, Math_lib, Accessor>::operator =(const Tensor_King<U, Math_lib, A>& ary) {
	this->assert_same_size(ary);
	Math_lib::copy(tensor, ary.accessor(), this->size());
	return *this;
}

template<class T, class Math_lib, class Accessor>
Tensor_Queen<T, Math_lib, Accessor>& Tensor_Queen<T, Math_lib, Accessor>::operator =(const Tensor_Queen<T, Math_lib, Accessor>& ary) {
	this->assert_same_size(ary);
	Math_lib::copy(tensor, ary.accessor(), this->size());
	return *this;
}

template<class T, class Math_lib, class Accessor>
template<typename U, class A>
Tensor_Queen<T, Math_lib, Accessor>& Tensor_Queen<T, Math_lib, Accessor>::operator =(const Tensor_Queen<U, Math_lib, A>& ary) {
	this->assert_same_size(ary);
	Math_lib::copy(tensor, ary.accessor(), this->size());
	return *this;
}

template<class T, class Math_lib, class Accessor>
template<class U>
Tensor_Queen<T, Math_lib, Accessor>& Tensor_Queen<T, Math_lib, Accessor>::operator =(const Id_Scalar<U, Math_lib>& ary) {
	this->assert_same_size(ary);
	Math_lib::copy(tensor, ary.accessor(), this->size());
	return *this;
}

template<class T, class Math_lib, class Accessor>
Tensor_Queen<T, Math_lib, Accessor>& Tensor_Queen<T, Math_lib, Accessor>::operator =(T scalar) {

	this->fill(scalar);
	return *this;
}

template<class T, class Math_lib, class Accessor>
template<class ary>
Tensor_Queen<T, Math_lib, Accessor>& Tensor_Queen<T, Math_lib, Accessor>::operator =(const ary& data) {
	this->assert_same_size(data);
	Math_lib::copy(tensor, data, this->size());
	return *this;
}

#endif
