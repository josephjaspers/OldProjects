/*
 * Vector.h
 *
 *  Created on: Dec 30, 2017
 *      Author: joseph
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "Scalar.h"
#include "TensorBase.h"


namespace BC {
template<class T, class Mathlib>
class Vector : public TensorBase<T, Vector<T, Mathlib>, Mathlib> {

	template<class,class> friend class Vector;
	using parent_class = TensorBase<T, Vector<T, Mathlib>, Mathlib>;
	using _int = typename parent_class::subAccess_int;

public:

	static constexpr int RANK() { return 1; }
	using parent_class::operator=;

	Vector() {}
	Vector(const Vector&& t) : parent_class(t) 		{}
	Vector(		 Vector&& t) : parent_class(t) 		{}
	Vector(const Vector&  t) : parent_class(t) 		{}
	Vector(int dim) 		 : parent_class(Shape({dim}))  {}

	template<class U> 		  Vector(const Vector<U, Mathlib>&  t) : parent_class(t) {}
	template<class U> 		  Vector(	   Vector<U, Mathlib>&& t) : parent_class(t) {}
	template<class... params> Vector(const params&... p) : parent_class(p...) {}

	Vector& operator =(const Vector&  t) { return parent_class::operator=(t); }
	Vector& operator =(const Vector&& t) { return parent_class::operator=(t); }
	Vector& operator =(	     Vector&& t) { return parent_class::operator=(t); }
	template<class U>
	Vector& operator = (const Vector<U, Mathlib>& t) { return parent_class::operator=(t); }

	Scalar<T, Mathlib> operator[] (_int i) {
		return (Scalar<T, Mathlib>(this->accessor_packet(), &this->array[i]));
	}
	const Scalar<T, Mathlib> operator[] (_int i) const {
		return Scalar<T, Mathlib>(this->accessor_packet(), &this->array[i]);
	}
	const Vector<unary_expression_transpose<typename MTF::determine_scalar<T>::type, typename parent_class::functor_type>, Mathlib> t() const {
		return Vector<unary_expression_transpose<typename MTF::determine_scalar<T>::type, typename parent_class::functor_type>, Mathlib>
		(this->transpose_packet(), this->data(), this->rows(), this->cols(), this->LD_rows());
	}
	const Vector<T, Mathlib> operator () (int index, std::vector<int> sub_shape) const {
		return Vector<T, Mathlib>(this->subAccessor_packet(sub_shape), &this->data()[index]);
	}
	Vector<T, Mathlib> operator () (int index, std::vector<int> sub_shape) {
		return Vector<T, Mathlib>(this->subAccessor_packet(sub_shape), &this->data()[index]);
	}

};

} //End Namespace BCw

#endif /* VECTOR_H_ */
