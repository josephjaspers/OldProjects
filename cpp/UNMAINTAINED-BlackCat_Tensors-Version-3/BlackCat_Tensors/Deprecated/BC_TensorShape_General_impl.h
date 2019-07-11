/*
 * BC_Shape_General_impl.h
 *
 *  Created on: Dec 12, 2017
 *      Author: joseph
 */

#ifndef BC_TENSORSHAPE_GENERAL_IMPL_H_
#define BC_TENSORSHAPE_GENERAL_IMPL_H_

#include "../BC_Shape/Shape.h"

template<class, class>
struct Shape_Parser_impl;

template<int...>
struct rank;

/*
 * This method creates two types, inner and outer shape of appropriate dimensions by splitting the
 * integer list at any point it finds a 0.
 *
 * IE  1, 2, 3, 0, 1, 2, 8
 * Generates inner_shape<1,2,3> and outer_shape<1,2,8>
 *
 * if no 0's are in place the class utilizes DEFAULT_LD to generate the default LD_shape;
 * IE 1, 2, 3,
 * Generates inner_shape<1,2,3> and outer_shape<1, 2, 6>
 */

template<template<int...>class left, template<int...>class right, int... inner_dims, int... outer_dims, int focused_dim>
struct Shape_Parser_impl<left<inner_dims...>, right<focused_dim, outer_dims...>> {
	using inner_shape = typename Shape_Parser_impl<left<inner_dims..., focused_dim>, right<outer_dims...>>::inner_shape;
	using outer_shape = typename Shape_Parser_impl<left<inner_dims..., focused_dim>, right<outer_dims...>>::outer_shape;
};

template<template<int...>class left, template<int...>class right, int... inner_dims, int... outer_dims>
struct Shape_Parser_impl<left<inner_dims...>, right<0, outer_dims...>> {
	using inner_shape = Inner_Shape<inner_dims...>;
	using outer_shape = Outer_Shape<outer_dims...>;
};

template<template<int...>class left, template<int...>class right, int... inner_dims>
struct Shape_Parser_impl<left<inner_dims...>, right<>> {
	using inner_shape = Inner_Shape<inner_dims...>;
	using outer_shape = typename DEFAULT_LD<Inner_Shape<inner_dims...>>::type;
};

template<int... dimensions>
struct Shape_Parser {
	using inner_shape = typename Shape_Parser_impl<rank<>, rank<dimensions...>>::inner_shape;
	using outer_shape = typename Shape_Parser_impl<rank<>, rank<dimensions...>>::outer_shape;

	using type 	= Tensor_Shape<inner_shape, outer_shape>;
};



#endif /* BC_TENSORSHAPE_GENERAL_IMPL_H_ */
