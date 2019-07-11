/*
 * BC_MetaTemplate_EssentialMethods.h
 *
 *  Created on: Dec 11, 2017
 *      Author: joseph
 */

#ifndef ADHOC_H_
#define ADHOC_H_

#include "Simple.h"
#include <type_traits>

namespace BC {
template<class,class> struct unary_expression_transpose;
template<class,class,class,class> struct binary_expression_dotproduct;
	namespace MTF {


		template<class, int, int, class...> class Matrix;
		template<class, int, class...> class Vector;

		template<class...>
		struct _list;

		//EXPRESSION_TYPE----------------------------------------------------------------------------------------------
		template<class, class>  struct expression_substitution;

		template<class sub, template<class, class> class derived, class scalar_type, class ml>
		struct expression_substitution<sub, derived<scalar_type, ml>>{
				using type = derived<sub, ml>;
		};
		//SCALAR_TYPE----------------------------------------------------------------------------------------------
		template<class T>
		struct determine_scalar {
				using type = T;
		};
		template<template<class...> class tensor, class T, class... set>
		struct determine_scalar<tensor<T, set...>> {
				using type = typename determine_scalar<T>::type;
		};
		//FUNCTOR_TYPE----------------------------------------------------------------------------------------------
		template<class T, class voider = void>
		struct determine_functor {
				using type = T;
		};
		template<class T>
		struct determine_functor<T, typename std::enable_if<MTF::isPrimitive<T>::conditional, void>::type> {
				using type = T*;
		};
		//EVALUTION_TYPE----------------------------------------------------------------------------------------------
		template<class tensor>
		struct determine_evaluation;

		template<bool, class T> struct if_AddRef { using type = T; };
		template<	   class T> struct if_AddRef<true, T> { using type = T&; };
		template<class T> struct ref { using type = T&; };

		template<template<class, class> class tensor, class T, class ML>
		struct determine_evaluation<tensor<T, ML>> {

			using type = typename MTF::IF_ELSE<isPrimitive<T>::conditional,
									typename ref<tensor<T, ML>>::type,
									tensor<typename determine_scalar<T>::type, ML>>::type;
		};

		//NONLINEAR EXPRESSION -------------------------------------------------------------


		template<class T>  struct non_pwise_functor {static constexpr bool conditional = false; };
		template<class T, class a, class b, class c>
		struct non_pwise_functor<binary_expression_dotproduct<T, a, b, c>> {static constexpr bool conditional = true; };


		template<class T, class a>
		struct non_pwise_functor<unary_expression_transpose<T, a>> {static constexpr bool conditional = true; };


	}
}
#endif /* ADHOC_H_ */
