/*
 * BC_Tensor_Lv4_Math_Advanced.h
 *
 *  Created on: Dec 12, 2017
 *      Author: joseph
 */

#ifndef TENSOR_LV3_EXPR_UTILITY_H_
#define TENSOR_LV3_EXPR_UTILITY_H_

#include "Tensor_Lv2_Traits.h"
namespace BC {

template<
class T,									//The internal array type
class derived,									//The derived class
class math_lib,					    		    //Math_library
class inner_shape,
class outer_shape>
struct BC_Tensor_Utility_Expression : public Tensor_Type<T, derived, math_lib, Tensor_Shape<inner_shape, outer_shape>, false> {

	using parent_class = Tensor_Type<T, derived, math_lib, Tensor_Shape<inner_shape, outer_shape>, false>;
	using grandparent_class = parent_class;

	BC_Tensor_Utility_Expression() = delete;
	template<class ... params> BC_Tensor_Utility_Expression(const params& ... p) :
		Tensor_Type<T, derived, math_lib, Tensor_Shape<inner_shape, outer_shape>, false>(p...) {}



};
}

#endif /* TENSOR_LV3_EXPR_UTILITY_H_ */