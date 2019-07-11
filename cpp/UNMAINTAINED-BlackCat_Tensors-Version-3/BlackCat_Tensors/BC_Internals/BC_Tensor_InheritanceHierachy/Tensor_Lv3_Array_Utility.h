/*
 * BC_Tensor_Lv4_Array_Utility.h
 *
 *  Created on: Dec 13, 2017
 *      Author: joseph
 */

/*
 * Print helper (will be removed eventually)
 */



#ifndef BC_TENSOR_LV3_ARRAY_UTILITY_H_
#define BC_TENSOR_LV3_ARRAY_UTILITY_H_
#include "Tensor_Lv2_Traits.h"

namespace BC {

template<class T,									//The internal array type
	class derived,									//The derived class
	class math_lib,					    		    //Math_library
	class inner_shape,
	class outer_shape
>
struct BC_Tensor_Utility_Array
		: public Tensor_Type<T, derived, math_lib, Tensor_Shape<inner_shape, outer_shape>, MTF::is_same<outer_shape, typename DEFAULT_LD<inner_shape>::type>::conditional>
{

	using this_type =     BC_Tensor_Utility_Array<T, derived, math_lib, inner_shape, outer_shape>;
	using parent_class =  Tensor_Type<T, derived, math_lib, Tensor_Shape<inner_shape, outer_shape>, MTF::is_same<outer_shape, typename DEFAULT_LD<inner_shape>::type>::conditional>;
	using grandparent_class = parent_class;

	BC_Tensor_Utility_Array() = default;
	template<class ... params> BC_Tensor_Utility_Array(const params& ... p) : parent_class(p...) {}

	void randomize(T lb, T ub) { math_lib::randomize(this->data(), lb, ub, this->size()); }
	void fill(T value) 		   { math_lib::fill(this->data(), value, this->size()); }
	void zero() 	  		   { math_lib::zero(this->data(), this->size()); }

	void print() const {
		auto ranks = this->getShape();
		math_lib::print(this->array, ranks, this->order(), 5);
	}
};
}
#endif /* BC_TENSOR_LV3_ARRAY_UTILITY_H_ */
