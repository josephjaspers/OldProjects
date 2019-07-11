#include "Scalar.h"
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"
#include <math.h>

	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations> Scalar<number_type, ScalarOperations>::operator^(const Scalar<number_type, ScalarOperations>& t) const {
		Scalar<number_type, ScalarOperations> val(0);
		ScalarOperations::power(val.scalar, this->scalar, t.scalar, 1);
		return val;
	}
	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations> Scalar<number_type, ScalarOperations>::operator/(const Scalar<number_type, ScalarOperations>& t) const {
		Scalar<number_type, ScalarOperations> val(0);
		ScalarOperations::divide(val.scalar, this->scalar, t.scalar, 1);
		return val;	}
	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations> Scalar<number_type, ScalarOperations>::operator+(const Scalar<number_type, ScalarOperations>& t) const {
		Scalar<number_type, ScalarOperations> val(0);
		ScalarOperations::add(val.scalar, this->scalar, t.scalar, 1);
		return val;	}
	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations> Scalar<number_type, ScalarOperations>::operator-(const Scalar<number_type, ScalarOperations>& t) const {
		Scalar<number_type, ScalarOperations> val(0);
		ScalarOperations::subtract(val.scalar, this->scalar, t.scalar, 1);
		return val;	}
	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations> Scalar<number_type, ScalarOperations>::operator&(const Scalar<number_type, ScalarOperations>& t) const {
		Scalar<number_type, ScalarOperations> val(0);
		ScalarOperations::multiply(val.scalar, this->scalar, t.scalar, 1);
		return val;	}

	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations>& Scalar<number_type, ScalarOperations>::operator^=(const Scalar<number_type, ScalarOperations>& t) {
		ScalarOperations::power(scalar, scalar, t.scalar, 1);
		 return *this;
	}
	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations>& Scalar<number_type, ScalarOperations>::operator/=(const Scalar<number_type, ScalarOperations>& t) {
		ScalarOperations::divide(scalar, scalar, t.scalar, 1);
		 return *this;
	}
	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations>& Scalar<number_type, ScalarOperations>::operator+=(const Scalar<number_type, ScalarOperations>& t) {
		ScalarOperations::add(scalar, scalar, t.scalar, 1);
		 return *this;
	}
	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations>& Scalar<number_type, ScalarOperations>::operator-=(const Scalar<number_type, ScalarOperations>& t) {
		ScalarOperations::subtract(scalar, scalar, t.scalar, 1);
		 return *this;
	}
	template<typename number_type, typename ScalarOperations> Scalar<number_type, ScalarOperations>& Scalar<number_type, ScalarOperations>::operator&=(const Scalar<number_type, ScalarOperations>& t) {
		ScalarOperations::multiply(scalar, scalar, t.scalar, 1);
		 return *this;
	}
