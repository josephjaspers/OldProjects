/*
 * Tensor_Base.h
 *
 *  Created on: Jan 6, 2018
 *      Author: joseph
 */

#ifndef TENSOR_BASE_H_
#define TENSOR_BASE_H_


#include "Implementation_Core/Tensor_IdentityClasses.h"
#include "Implementation_Core/Tensor_Operations.h"
#include "Implementation_Core/Tensor_Utility.h"
#include "Implementation_Core/Shape.h"
#include "../BC_MathLibraries/Mathematics_CPU.h"
#include "../BC_MathLibraries/Mathematics_GPU.cu"


namespace BC {

template<class, class, class> struct shell;
template<template<class, class> class tensor, class U, class ml, class V, class M> struct shell<tensor<U, ml>, V, M> { using type = tensor<V, M>; };

//Expression specialization
template<class T, class derived, class Mathlib, class voider = void>
class TensorBase :
				public Tensor_Math_Core<T, derived, Mathlib>,
				public Tensor_Utility  <T, derived, Mathlib, MTF::isPrimitive<T>::conditional>

{

protected:
	struct DISABLE;

	using math_parent  = Tensor_Math_Core<T, derived, Mathlib>;
//	using shape_parent = Shape;

	using functor_type 			= typename Tensor_Math_Core<T, derived, Mathlib>::functor_type;
	using subAccess_int 		= DISABLE;
	using force_evaluation_int 	= int;


	const Shape& shape_parent;
public:
	void printDetails() const { shape_parent.printDetails(); }
	int rank() const { return shape_parent.rank(); }
	int size() const { return shape_parent.size(); }
	int rows() const { return shape_parent.rows(); }
	int cols() const { return shape_parent.cols(); }
	int dimension(int i) const { return shape_parent.dimension(i); }
	void printDimensions() const {  shape_parent.printDimensions(); }
	void printLDDimensions() const {  shape_parent.printLDDimensions(); }

	int LD_rows() const { return shape_parent.LD_rows(); }
	int LD_cols() const { return shape_parent.LD_cols(); }

	const int* InnerShape() const { return shape_parent.InnerShape(); }
	const Shape& expression_packet() const { return shape_parent; }
	auto shape_copy_packet() const 	{ return shape_parent.shape_copy_packet(); }
	auto accessor_packet() const    { return shape_parent.accessor_packet(); }
	Shape transpose_packet() const   { return shape_parent.transpose_packet();}
	Shape dotproduct_packet(int eval_order, const Shape& sh) const { return shape_parent.dotproduct_packet(eval_order, sh); }
	const Shape& asShape() const { return shape_parent; }


	operator  const derived&() const { return static_cast<const derived&>(*this); }
	operator  derived&() { return static_cast<derived&>(*this); }

	functor_type array;

	template<class... params> TensorBase(const Shape& exp, const params&... p) : shape_parent(exp), array(p...) {}
    TensorBase(		 derived&& tensor) : shape_parent(tensor.expression_packet()), array(tensor.data()){}
	TensorBase(const derived& tensor) : shape_parent(tensor.expression_packet()), array(tensor.data()){}
};
template<class T, class derived, class Mathlib>
class TensorBase<T, derived, Mathlib, typename std::enable_if<MTF::non_pwise_functor<T>::conditional>::type> :
				public Tensor_Math_Core<T, derived, Mathlib>,
				public Tensor_Utility  <T, derived, Mathlib, MTF::non_pwise_functor<T>::conditional>,
				public Shape

{

protected:
	struct DISABLE;

	using math_parent  = Tensor_Math_Core<T, derived, Mathlib>;
	using shape_parent = Shape;

	using functor_type 			= typename Tensor_Math_Core<T, derived, Mathlib>::functor_type;
	using subAccess_int 		= DISABLE;
	using force_evaluation_int 	= int;

public:
	operator  const derived&() const { return static_cast<const derived&>(*this); }
	operator  derived&() { return static_cast<derived&>(*this); }

	functor_type array;

	template<class... params> TensorBase(Shape exp, const params&... p) : shape_parent(exp), array(p...) {}
	TensorBase(		 derived&& tensor) : shape_parent(tensor.expression_packet()), array(tensor.data()){}
	TensorBase(const derived& tensor) : shape_parent(tensor.expression_packet()), array(tensor.data()){}
};

//----------------------------------------SPECIALIZATION FOR ACTUAL TENSORS (non expressions)----------------------------------------//

template<class T, class derived, class Mathlib>
class TensorBase<T, derived, Mathlib, typename std::enable_if<MTF::isPrimitive<T>::conditional>::type> :
				public Tensor_Math_Core<T, derived, Mathlib>,
				public Tensor_Utility  <T, derived, Mathlib, MTF::isPrimitive<T>::conditional>,

				public Shape
{

protected:
	struct DISABLE;
	bool OWNERSHIP = Shape::array_ownership;

	using math_parent  = Tensor_Math_Core<T, derived, Mathlib>;
	using shape_parent = Shape;

	using functor_type 			= typename Tensor_Math_Core<T, derived, Mathlib>::functor_type;
	using subAccess_int 		= int;
	using force_evaluation_int 	= DISABLE;

	template<class U, class V>
	using derived_shell = typename shell<derived, U, V>::type;

public:

	using math_parent::operator=;

	operator  const derived&() const { return static_cast<const derived&>(*this); }
	operator  		derived&() 		 { return static_cast<		derived&>(*this); }

	functor_type array;

	TensorBase() : shape_parent(_shape(0)), OWNERSHIP(false) {
		 Mathlib::initialize(array, this->size());
	}

	template<class... params> TensorBase(Shape exp, const params&... p) : shape_parent(exp), array(p...), OWNERSHIP(false) {}
	template<class... params> TensorBase(Shape exp) : shape_parent(exp), OWNERSHIP(true) {
		Mathlib::initialize(array, this->size());
	}
	TensorBase(T* ary) : array(ary), OWNERSHIP(false) {}

	/////THIS OWNERSHIP SHOULD BE TRUE CAUSING CRASH ON NEURAL NETWORKS FOR SOME REASON ??? can't do auto var = derived&
	TensorBase(const derived& tensor) : shape_parent(tensor.shape_copy_packet()), OWNERSHIP(true) {
		Mathlib::initialize(array, this->size());
		Mathlib::copy(array, tensor.array, this->size());

	}
	template<class U, class D, class V>
	TensorBase(const TensorBase<U, D, Mathlib, V>& tensor) : shape_parent(tensor.expression_packet()), OWNERSHIP(true) {
		Mathlib::initialize(array, this->size());
		Mathlib::copy(array, tensor.array, this->size());
	}
	TensorBase(const derived&& tensor) : array(tensor.OWNERSHIP ? tensor.array : nullptr), Shape(tensor.expression_packet()), OWNERSHIP(true) {
		if (!tensor.OWNERSHIP) {
			Mathlib::initialize(array, this->size());
			Mathlib::copy(array, tensor.array, this->size());
		} else {
		tensor.changeOwnership(false);
		}
	}
	TensorBase(		derived&& tensor) : array(tensor.OWNERSHIP ? tensor.array : nullptr), Shape(tensor.expression_packet()), OWNERSHIP(true) {
		if (!tensor.OWNERSHIP) {
			Mathlib::initialize(array, this->size());
			Mathlib::copy(array, tensor.array, this->size());
		} else {
		tensor.changeOwnership(false);
		}
	}

	void changeOwnership(bool change = false) {
		ChangeShapeOwnership(change);
		this->OWNERSHIP = false;
	}

	derived& operator = (const derived& tensor) {
		this->assert_same_size(tensor);
		Mathlib::copy(this->data(), tensor.data(), this->size());
		return this->asBase();
	}
	derived& operator = (derived&& tensor) {
		this->assert_same_size(tensor);
		if (OWNERSHIP && tensor.OWNERSHIP) {
			std::swap(array, tensor.array);
			return this->asBase();
		} else {
		Mathlib::copy(this->data(), tensor.data(), this->size());
		return this->asBase();
		}
	}


	~TensorBase() {
		if (OWNERSHIP) {
			Mathlib::destroy(array);
		}
	}
};
}


#endif /* TENSOR_BASE_H_ */

