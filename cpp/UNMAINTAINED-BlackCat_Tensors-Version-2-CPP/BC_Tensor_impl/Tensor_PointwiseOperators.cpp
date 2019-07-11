#include "Tensor.h"
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator^(const Tensor<number_type, TensorOperations> & t) const {
    this->assert_same_dimensions(t);
    Tensor<number_type, TensorOperations> store(*this, false);

    subTensor || t.subTensor ?
    		TensorOperations::power(store.tensor, ranks, order, store.ld, tensor, ld, t.tensor, t.ld)
    :
    		TensorOperations::power(store.tensor, tensor, t.tensor, sz);

    return store;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator/(const Tensor<number_type, TensorOperations> & t) const {
	this->assert_same_dimensions(t);
    Tensor<number_type, TensorOperations> store(*this, false);

    subTensor || t.subTensor ?
    		TensorOperations::divide(store.tensor, ranks, order, store.ld, tensor, ld, t.tensor, t.ld)
    :
    		TensorOperations::divide(store.tensor, tensor, t.tensor, sz);

    return store;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator+(const Tensor<number_type, TensorOperations> & t) const {
	this->assert_same_dimensions(t);
    Tensor<number_type, TensorOperations> store(*this, false);

    subTensor || t.subTensor ?
    		TensorOperations::add(store.tensor, ranks, order, store.ld, tensor, ld, t.tensor, t.ld)
    :
    		TensorOperations::add(store.tensor, tensor, t.tensor, sz);

    return store;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator-(const Tensor<number_type, TensorOperations> & t) const {
	this->assert_same_dimensions(t);
    Tensor<number_type, TensorOperations> store(*this, false);

    subTensor || t.subTensor ?
    		TensorOperations::subtract(store.tensor, ranks, order, store.ld, tensor, ld, t.tensor, t.ld)
    :
    		TensorOperations::subtract(store.tensor, tensor, t.tensor, sz);

    return store;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator%(const Tensor<number_type, TensorOperations>& t) const {
	this->assert_same_dimensions(t);
    Tensor<number_type, TensorOperations> store(*this, false);

    subTensor || t.subTensor ?
        		TensorOperations::multiply(store.tensor, ranks, order, store.ld, tensor, ld, t.tensor, t.ld)
        :
        		TensorOperations::multiply(store.tensor, tensor, t.tensor, sz);

    return store;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator^=(const Tensor<number_type, TensorOperations> & t) {
	this->assert_same_dimensions(t);

	  subTensor || t.subTensor ?
	        		TensorOperations::power(tensor, ranks, order, ld, tensor, ld, t.tensor, t.ld)
	        :
	        		TensorOperations::power(tensor, tensor, t.tensor, sz);


	return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator/=(const Tensor<number_type, TensorOperations> & t) {
	this->assert_same_dimensions(t);

	  subTensor || t.subTensor ?
	        		TensorOperations::divide(tensor, ranks, order, ld, tensor, ld, t.tensor, t.ld)
	        :
	        		TensorOperations::divide(tensor, tensor, t.tensor, sz);


	return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator+=(const Tensor<number_type, TensorOperations> & t) {
	this->assert_same_dimensions(t);

	  subTensor || t.subTensor ?
	        		TensorOperations::add(tensor, ranks, order, ld, tensor, ld, t.tensor, t.ld)
	        :
	        		TensorOperations::add(tensor, tensor, t.tensor, sz);


	return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator-=(const Tensor<number_type, TensorOperations> & t) {
	this->assert_same_dimensions(t);

	  subTensor || t.subTensor ?
	        		TensorOperations::subtract(tensor, ranks, order, ld, tensor, ld, t.tensor, t.ld)
	        :
	        		TensorOperations::subtract(tensor, tensor, t.tensor, sz);


	return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator%=(const Tensor<number_type, TensorOperations>& t) {
	this->assert_same_dimensions(t);

	  subTensor || t.subTensor ?
	        		TensorOperations::multiply(tensor, ranks, order, ld, tensor, ld, t.tensor, t.ld)
	        :
	        		TensorOperations::multiply(tensor, tensor, t.tensor, sz);



	return *this;
}
//------------------------------------------------------------scalar methods------------------------------------------------------------//


template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator^=(const Scalar<number_type, TensorOperations>& scal) {
	subTensor ?
			TensorOperations::power(tensor, ranks, order, ld, tensor, ld, scal())
	:
			TensorOperations::power(tensor, tensor, scal(), sz);


    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator/=(const Scalar<number_type, TensorOperations>& scal) {
	subTensor ?
			TensorOperations::divide(tensor, ranks, order, ld, tensor, ld, scal())
	:
			TensorOperations::divide(tensor, tensor, scal(), sz);


    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator+=(const Scalar<number_type, TensorOperations>& scal) {
	subTensor ?
			TensorOperations::add(tensor, ranks, order, ld, tensor, ld, scal())
	:
			TensorOperations::add(tensor, tensor, scal(), sz);


    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator-=(const  Scalar<number_type, TensorOperations>&  scal) {
	subTensor ?
				TensorOperations::subtract(tensor, ranks, order, ld, tensor, ld, scal())
		:
				TensorOperations::subtract(tensor, tensor, scal(), sz);


    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator%=(const  Scalar<number_type, TensorOperations>&  scal) {

	subTensor ?
				TensorOperations::multiply(tensor, ranks, order, ld, tensor, ld, scal())
		:
				TensorOperations::multiply(tensor, tensor, scal(), sz);


    return *this;
}
//--------------------------------scalar non assignment --------------------------------------------------------//

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator-(const Scalar<number_type, TensorOperations>& scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::subtract(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
    :
    		TensorOperations::subtract(s.tensor, tensor, scal(), sz);

    return s;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator%(const Scalar<number_type, TensorOperations>& scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);

    subTensor ?
    		TensorOperations::multiply(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
    :
    		TensorOperations::multiply(s.tensor, tensor, scal(), sz);

    return s;
}

template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator^(const  Scalar<number_type, TensorOperations>&  scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::power(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
    :
    		TensorOperations::power(s.tensor, tensor, scal(), sz);

    return s;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator/(const  Scalar<number_type, TensorOperations>&  scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::divide(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
    :
    		TensorOperations::divide(s.tensor, tensor, scal(), sz);


    return s;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator+(const  Scalar<number_type, TensorOperations>&  scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::add(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
    :
    		TensorOperations::add(s.tensor, tensor, scal(), sz);


    return s;
}

//--------------------------------------------------------------base number-type ------------------------------------------------------------/


template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator^=(number_type scal) {

    subTensor ?
    		TensorOperations::power(tensor, ranks, order, ld, tensor, ld, scal)
    :
    		TensorOperations::power(tensor, tensor, scal, sz);




    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator/=(number_type scal) {
	subTensor ?
	    		TensorOperations::divide(tensor, ranks, order, ld, tensor, ld, scal)
	    :
	    		TensorOperations::divide(tensor, tensor, scal, sz);


    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator+=(number_type scal) {
	subTensor ?
	    		TensorOperations::add(tensor, ranks, order, ld, tensor, ld, scal)
	    :
	    		TensorOperations::add(tensor, tensor, scal, sz);


    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator-=(number_type scal) {
	subTensor ?
	    		TensorOperations::subtract(tensor, ranks, order, ld, tensor, ld, scal)
	    :
	    		TensorOperations::subtract(tensor, tensor, scal, sz);


    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator%=(number_type scal) {

	subTensor ?
	    		TensorOperations::multiply(tensor, ranks, order, ld, tensor, ld, scal)
	    :
	    		TensorOperations::multiply(tensor, tensor, scal, sz);


    return *this;
}
//--------------------------------scalar non assignment --------------------------------------------------------//

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator=(number_type scal) {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::fill(tensor, ranks, order, ld, scal)
    :
    		TensorOperations::fill(tensor, scal, sz);

    return *this;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator-(number_type scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::subtract(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal)
    :
    		TensorOperations::subtract(s.tensor, tensor, scal, sz);

    return s;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator%(number_type scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::multiply(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal)
    :
    		TensorOperations::multiply(s.tensor, tensor, scal, sz);
    return s;
}

template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator^(number_type scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::power(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal)
    :
    		TensorOperations::power(s.tensor, tensor, scal, sz);
    return s;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator/(number_type scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::divide(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal)
    :
    		TensorOperations::divide(s.tensor, tensor, scal, sz);
    return s;
}

template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator+(number_type scal) const {
    Tensor<number_type, TensorOperations> s(*this, false);
    subTensor ?
    		TensorOperations::add(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal)
    :
    		TensorOperations::add(s.tensor, tensor, scal, sz);
    return s;
}
