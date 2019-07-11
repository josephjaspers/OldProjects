///*
// * BC_Tensor_Shape_impl.h
// *
// *  Created on: Dec 1, 2017
// *      Author: joseph
// */
//
//#ifndef STATIC_SHAPE_INNER_IMPL_H_
//#define STATIC_SHAPE_INNER_IMPL_H_
//
//#include <iostream>
//#include "../BlackCat_Internal_GlobalUnifier.h"
//
///*
// * What's happening?
// *
// * This code generates the core methods of Inner_Shape.
// * All of these methods (and return values) are calculated at COMPILE time
// *
// * The choice to enforce the dimensionality of Tensor at compile time enables many optimizations.
// * In my personal experience of working Neural Networks, it is seldom that one does not know the dimensionality of a Tensor (Vector or Matrix).
// * Ergo enforcing a specific dimensionality
// *
// */
//namespace BC {
//namespace BC_Shape_Identity_impl {
//
//
//	//---------------------------size handling-------------------------------//
//
//	template<int curr_dim, int ... dimensions> struct size_helper           { static constexpr int value = curr_dim * size_helper<dimensions...>::value; };
//	template<int curr_dim> 					   struct size_helper<curr_dim> { static constexpr int value = curr_dim; };
//
//	template<int ...dimensions> constexpr int size() { return size_helper<dimensions...>::value; }
//
//
//	//---------------------------dimension handling-------------------------------//
//	template<int index, int ... dims> struct dimension { static constexpr int value = 0; };
//
//	template<int index, int curr_dim, int ... dims>
//	struct dimension<index, curr_dim, dims...> {
//		static constexpr int value = index == 1 ? curr_dim : dimension<MTF::max<index - 1, 0>::value, dims...>::value;
//	};
//	template<int index, int curr_dim>
//	struct dimension<index, curr_dim> {
//		static constexpr int value = index == 1 ? curr_dim : 1;
//	};
//
//	//get row from dimensions
//	template<int r, int ... dimensions>
//	constexpr int row() {
//		return r;
//	}
//
//	//get col from dimensions
//	template<int ... dimensions>
//	constexpr int col() {
//		return dimension<2, dimensions...>::value;
//	}
//
//	//get depth (3rd dim) from dimensions
//	template<int ... dimensions>
//	constexpr int depth() {
//		return dimension<3, dimensions...>::value;
//	}
//
//	//get pages (4th dim) from dimensions
//	template<int ... dimensions>
//	constexpr int pages() {
//		return dimension<4, dimensions...>::value;
//	}
//
//	template<int ... dimensions>
//	constexpr int books() {
//		return dimension<5, dimensions...>::value;
//	}
//	template<int ... dimensions>
//	constexpr int libraries() {
//		return dimension<6, dimensions...>::value;
//	}
//
//
//	//---------------------------print impl-------------------------------//
//	template<class>
//	struct print;
//
//	template<int first, template<int...> class list, int... set>
//	struct print<list<first, set...>> {
//		print() {
//		std::cout << "[" << first << "]";
//		print<list<set...>>();
//		}
//	};
//	template<int first, template<int...> class list>
//	struct print<list<first>> {
//		print() {
//		std::cout << "[" << first << "]";
//		std::cout << std::endl;
//		}
//	};
//}
//}
//#endif /* STATIC_SHAPE_INNER_IMPL_H_ */
