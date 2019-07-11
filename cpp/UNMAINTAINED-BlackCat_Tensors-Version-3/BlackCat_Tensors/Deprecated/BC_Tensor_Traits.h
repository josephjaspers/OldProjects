/*
 * BC_Tensor_Base.h
 *
 *  Created on: Dec 6, 2017
 *      Author: joseph
 */

#ifndef BC_TENSOR_TRAITS_H_
#define BC_TENSOR_TRAITS_H_

namespace BC {

#include "../BC_Internal_Include.h"
#include "../BC_Tensor_Shape.h"
#include "BC_Shape_Inner_Impl.h"
#include "BC_Typeclass_FunctionType.h"
#include "BC_Typeclass_FunctionType.h"
#include "BC_Typeclass_Identity.h"

/*
 * class Shape is the BC::Shape<int...> class
 * leading_dimensions is the BC::LD_Shape<int...> class
 */

template<class Array_Type>
class Traits {
	using functor_type 		= typename Tensor_FunctorType<Array_Type>::type;
	using identity_type 	= typename BC_Shape_Identity::Identity<Array_Type, ml, dimensions...>::type;
	using evaluation_type 	= typename BC_Evaluation_Identity::Identity<Array_Type, ml, dimensions...>::type;
	using array_type 		= typename BC_ArrayType::Identity<Array_Type>::type;
};

}
#endif /* BC_TENSOR_TRAITS_H_ */


/*
 * functor_type  --- is the type  type expressions will store as their lv/rv values. For the most standard Tensors,
 * this will be of some type T* (IE a double/float array).
 *
 * Identity_type ---Identity type  IE Vector, Matrix, Cube, Tensor
 *
 * Evaluation_type --- the type if the object is needed now, if the functor type is a pointer to an array,
 * the type evaluation_type is a reference to itself, otherwise it is evaluated and returns the identity type
 *
 * Array_type    --- the adjusted functor type to T, IE functor_type = double* array_Type = double.
 * 						OR Binary_Expression<double, lv, rv, oper> array_type = double
 *
 */
