#include "Scalar.h"
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"
template<typename number_type, typename TensorOperations>


Scalar<number_type, TensorOperations>::Scalar(const Scalar<number_type, TensorOperations>& s) {
	TensorOperations::initialize(scalar, 1);
	TensorOperations::fill(scalar, s.scalar[0], 1);
}

template<typename number_type, typename TensorOperations>
Scalar<number_type, TensorOperations>::Scalar(Scalar<number_type, TensorOperations> && s) {
	if (s.ownership && ownership)
	scalar = s.scalar;
	else {
		TensorOperations::fill(scalar, s.scalar[0], 1);
	}
}

template<typename number_type, typename TensorOperations>
Scalar<number_type, TensorOperations>::Scalar(number_type value) {
	TensorOperations::initialize(scalar, 1);
	TensorOperations::fill(scalar, value, 1);
}

template<typename number_type, typename TensorOperations>
Scalar<number_type, TensorOperations>& Scalar<number_type, TensorOperations>::operator =(const Scalar<number_type, TensorOperations>& s) {
	TensorOperations::fill(scalar, s.scalar[0], 1);
	return *this;
}

template<typename number_type, typename TensorOperations>
Scalar<number_type, TensorOperations>& Scalar<number_type, TensorOperations>::operator =(Scalar<number_type, TensorOperations> && s) {

	if (s.ownership && ownership) {
		TensorOperations::destruction(this->scalar);
		this->scalar = s.scalar;
	} else {
		TensorOperations::fill(scalar, s.scalar[0], 1);
	}
	return *this;
}

template<typename number_type, typename TensorOperations>
Scalar<number_type, TensorOperations>& Scalar<number_type, TensorOperations>::operator =(number_type s) {
	TensorOperations::fill(scalar, s, 1);
	return *this;
}
