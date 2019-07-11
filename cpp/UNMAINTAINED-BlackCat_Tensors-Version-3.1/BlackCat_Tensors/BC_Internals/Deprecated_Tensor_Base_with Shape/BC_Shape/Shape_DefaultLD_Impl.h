/*
 * BC_Shape_Primary.h
 *
 *  Created on: Dec 8, 2017
 *      Author: joseph
 */

#ifndef STATIC_SHAPE_OUTER_IMPL_H_
#define STATIC_SHAPE_OUTER_IMPL_H_


/*
 * What's happening?
 *
 *
 * This code generates default leading_dimensions in respect to some given dimensionality of a tensor.
 *
 * IE if given an Inner_Shape<4,3,2>
 * DEFAULT_LD generates the type Outer_Shape<4, 12, 24>
 *
 */
namespace BC {
template<int ... dimensions>
struct Inner_Shape;

template<int ... dimensions>
struct Outer_Shape;

template<class from, class to>
class reverse_helper;

template<class>
class reverse;

template<class, class>
struct extract;

template<class>
struct LD_Generator_Helper;

template<class>
struct DEFAULT_LD_impl;

template<template<int...> class from,
		 template<int...> class to,
		 int... ele1,
		 int	  front,
		 int... ele2>
struct reverse_helper<from<front, ele1...>, to<ele2...>>{
	using type = typename reverse_helper<from<ele1...>, to<front, ele2...>>::type;
};

template<template<int...> class from,
		 template<int...> class to,
		 int... ele2>
struct reverse_helper<from<>, to<ele2...>>{
	using type = to<ele2...>;
};

template<template<int...>class list, int... set>
struct reverse<list<set...>> {
	using type = typename reverse_helper<list<set...>, list<>>::type;
};


template<template<int...> class l1, template<int...>class l2, int... e1, int... e2>
struct extract<l1<e1...>, l2<e2...>> {
	using type = l1<e1...,e2...>;
};

template<class>
struct DEFAULT_LD_impl;

template<template<int...> class list, int... set, int front>
struct DEFAULT_LD_impl<list<front, set...>> {
	static constexpr int value = front * DEFAULT_LD_impl<list<set...>>::value;
	using type = typename extract<typename DEFAULT_LD_impl<list<set...>>::type, Outer_Shape<value>>::type;
};

template<template<int...> class list, int front>
struct DEFAULT_LD_impl<list<front>> {
	static constexpr int value = front;
	using type = Outer_Shape<front>;
};

template<class>
struct DEFAULT_LD;

template<template<int...> class list, int... set>
struct DEFAULT_LD<list<set...>> {
	using type = typename DEFAULT_LD_impl<typename reverse<list<set...>>::type>::type;
};

//template<int>struct Dynamic_Outer_Shape;
//template<int>struct Dynamic_Inner_Shape;
//
//template<int dim>
//struct DEFAULT_LD<Dynamic_Inner_Shape<dim>> {
//	using type = Dynamic_Outer_Shape<dim>;
//};

}

#endif /* STATIC_SHAPE_OUTER_IMPL_H_ */
