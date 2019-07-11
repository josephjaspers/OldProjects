
/*
 * BC_Tensor_Base.h
 *
 *  Created on: Dec 11, 2017
 *      Author: joseph
 */

#ifndef BC_TENSOR_BASE_H_
#define BC_TENSOR_BASE_H_

#include "../BlackCat_Internal_GlobalUnifier.h"
namespace BC {

template <
class array_T,									//The internal array type
class derived,									//The derived class
class math_lib,					    		    //Math_library
class shape,									//The shape of the tensor
bool  isParent = MTF::AND<
					MTF::is_same<typename shape::inner_shape, DEFAULT_LD<typename shape::inner_shape>>::conditional,
					Tensor_FunctorType<array_T>::supports_utility_functions>::conditional
>
struct Tensor_Type : shape {

	using this_type       = Tensor_Type<array_T, derived, math_lib, shape, isParent>;
	using functor_type    = typename Tensor_FunctorType<array_T>::type;			//either T* if primitive else an array wrapper
	using scalar_type 	  = typename BC_ArrayType::Identity<array_T>::type;
	using identity_type   = typename BC_Shape_Identity::Identity<array_T, math_lib, typename shape::inner_shape>::type;
	using evaluation_type = derived&;
	static constexpr bool ASSIGNABLE = true;
	static constexpr bool MOVEABLE   = isParent;

	functor_type array; 														//This is the internal array

	Tensor_Type()  { math_lib::initialize(array, this->size());} 				//Assumes array is a pointer to a primitive type, initializes with the apropriate math_lib call
	template<class... params> Tensor_Type(const params&... p)  : array(p...) {}

	~Tensor_Type() { if (isParent) math_lib::destroy(array); }


		  evaluation_type eval() 	   { return static_cast<evaluation_type>(static_cast<derived&>(*this)); } //yes you need to double cast
	const evaluation_type eval() const { return static_cast<evaluation_type>(static_cast<derived&>(*this)); } //sorry its awkward

		  functor_type    data()	   { return array; }
	const functor_type	  data() const { return array; }

	constexpr bool isAssignable() const { return true; }
	constexpr bool isMoveable()   const { return isParent; }

	bool ensureAssignability() const { if (!isAssignable())  throw std::invalid_argument("non assignable"); return isAssignable();}
	bool ensureMoveability()   const { if (!isMoveable())    throw std::invalid_argument("non movable");   return isMoveable();}
};


/*
 *
 * This specialization is for Tensors that are not parents of their internal array. IE expressions and sub-tensors.
 *
 */

template <
class array_T,									//The internal array type
class derived,									//The derived class
class math_lib,					    		    //Math_library
class shape									   //The shape of the tensor
>
struct Tensor_Type<array_T, derived, math_lib, shape, false> : shape {

	using this_type       = Tensor_Type<array_T, derived, math_lib, shape, false>;
	using functor_type    = typename Tensor_FunctorType<array_T>::type;			//either T* if primitive else an array wrapper
	using scalar_type 	  = typename BC_ArrayType::Identity<array_T>::type;
	using identity_type   = typename BC_Shape_Identity::Identity<array_T, math_lib, typename shape::inner_shape>::type;
	using evaluation_type = typename BC_Evaluation_Identity::Identity<array_T, math_lib, typename shape::inner_shape>::type;
	static constexpr bool ASSIGNABLE = Tensor_FunctorType<array_T>::supports_utility_functions;
	static constexpr bool MOVABLE   = false;

	functor_type array; 														//This is the internal array

	template<class... params> Tensor_Type(const params&... p) : array(p...) {}				//Assumes array is a pointer to a primitive type, initializes with the appropriate math_lib call
	~Tensor_Type() = default;


		  evaluation_type eval() 	   { return static_cast<evaluation_type>(static_cast<derived&>(*this)); } //yes you need to double cast
	const evaluation_type eval() const { return static_cast<evaluation_type>(static_cast<derived&>(*this)); } //sorry its awkward

		  functor_type&  data()	   	  { return array; }
	const functor_type&	 data() const { return array; }


	constexpr bool isAssignable() const { return false; }
	constexpr bool isMoveable()   const { return false; }

	bool ensureAssignability() const { if (!isAssignable())  throw std::invalid_argument("non assignable"); return isMoveable();}
	bool ensureMoveability()   const { if (!isMoveable())    throw std::invalid_argument("non moveable");   return isAssignable();}
};

}

#endif /* BC_TENSOR_BASE_H_ */
