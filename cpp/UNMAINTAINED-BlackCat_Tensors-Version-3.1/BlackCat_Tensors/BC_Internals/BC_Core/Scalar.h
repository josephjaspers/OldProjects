/*
 * Scalar.h
 *
 *  Created on: Jan 6, 2018
 *      Author: joseph
 */

#ifndef SCALAR_H_
#define SCALAR_H_
#include "TensorBase.h"

namespace BC {

template<class T, class Mathlib>
class Scalar : public TensorBase<T, Scalar<T, Mathlib>, Mathlib> {

	using parent_class = TensorBase<T, Scalar<T, Mathlib>, Mathlib>;
	template<class, class> friend class Vector;

public:
	static constexpr int RANK() { return 0; }

	using parent_class::operator=;

	Scalar() {}
	Scalar(const Scalar&& t) : parent_class(t) 		{}
	Scalar(		 Scalar&& t) : parent_class(t) 		{}
	Scalar(const Scalar&  t) : parent_class(t) 		{}
	template<class... params> Scalar(Shape sh, const params&... p) : parent_class(sh, p...) {}

	Scalar& operator =(const Scalar&  t) { return parent_class::operator=(t); }
	Scalar& operator =(const Scalar&& t) { return parent_class::operator=(t); }
	Scalar& operator =(	     Scalar&& t) { return parent_class::operator=(t); }
	template<class U>
	Scalar& operator =(const Scalar<U, Mathlib>& t) { return parent_class::operator=(t); }
	Scalar& operator =(T scalar) { Mathlib::DeviceToHost(this->data(), &scalar, 1); return *this; }

	using _shape = std::vector<int>;
	Scalar(T* param) : parent_class(Shape(_shape(0), _shape(0), 0, 1, false), param) {}
	Scalar(T value) : parent_class(Shape(_shape(0), _shape(0), 0, 1, true)) {
		Mathlib::HostToDevice(this->array, &value, 1);
	}
};


}



#endif /* SCALAR_H_ */
