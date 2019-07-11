/*
 * BC_Tensor_Super_Ace.h
 *
 *  Created on: Nov 18, 2017
 *      Author: joseph
 */

#ifndef STATIC_SHAPE_H_
#define STATIC_SHAPE_H_

#include "../BlackCat_Internal_GlobalUnifier.h"
#include "Static_Shape_Inner_Impl.h"
#include "Static_Shape_Outer_Impl.h"
#include <type_traits>
#include <vector>
/*
 *
 * Compile time management of methods related to dimensionality
 */
namespace BC {

	template<int>class Dynamic_Inner_Shape;
	template<int>class Dynamic_Outer_Shape;

template<class Inner_Shape, class Outer_Shape = typename DEFAULT_LD<Inner_Shape>::type>
struct Tensor_Shape :
		MTF::IF_ELSE<Inner_Shape::isDynamic, Dynamic_Inner_Shape<Inner_Shape::RANK   >, Inner_Shape>::type,
		MTF::IF_ELSE<Outer_Shape::isDynamic, Dynamic_Outer_Shape<Outer_Shape::LD_RANK>, Outer_Shape>::type {

	static constexpr bool isContinuous = MTF::is_same<Outer_Shape, typename DEFAULT_LD<Inner_Shape>::type>::conditional;
	static constexpr int  RANK = Inner_Shape::RANK;
	static constexpr int  SIZE = Inner_Shape::size();

	using outer_shape = Outer_Shape;
	using inner_shape = Inner_Shape;
};


		namespace printHelper {

			template<class >
			struct f;

			template<int ... set, template<int...> class list, int front>
			struct f<list<front, set...>> {
				static void fill(int* ary) {
					ary[0] = front;
					f<list<set...>>::fill(&ary[1]);
				}
			};
			template<template<int...> class list, int front>
			struct f<list<front>> {
				static void fill(int* ary) {
					ary[0] = front;
				}
			};
		}


template<int ... dimensions>
struct Inner_Shape {

	static constexpr int RANK = sizeof...(dimensions);
	static constexpr bool isDynamic = MTF::sum<dimensions...>::value == 0;

	void printDimensions() const { BC_Shape_Identity_impl::print<Inner_Shape<dimensions...>>(); }

	const auto getShape() const {
		std::vector<int> sh(RANK);
		printHelper::f<Inner_Shape<dimensions...>>::fill(&sh[0]);
		  return sh;
	}
	constexpr int order() const { return sizeof...(dimensions); }
	constexpr int size()  const { return BC_Shape_Identity_impl::size<dimensions...>(); }
	constexpr int rows()  const { return BC_Shape_Identity_impl::row<dimensions...>();   }
	constexpr int cols()  const { return BC_Shape_Identity_impl::col<dimensions...>();   }
	constexpr int depth() const { return BC_Shape_Identity_impl::depth<dimensions...>(); }
	constexpr int pages() const { return BC_Shape_Identity_impl::pages<dimensions...>(); }
	constexpr int books() const { return BC_Shape_Identity_impl::books<dimensions...>(); }
	constexpr int libraries() const { return BC_Shape_Identity_impl::libraries<dimensions...>(); }

	template<int dim_index> constexpr int dimension() const { return BC_Shape_Identity_impl::dimension<dim_index, dimensions...>(); }
};

template<int... dimensions>
struct Outer_Shape {

	static constexpr int LD_RANK = sizeof...(dimensions);
	static constexpr bool isDynamic = MTF::sum<dimensions...>::value == 0;

	void printLeadingDimensions() const { BC_Shape_Identity_impl::print<Outer_Shape<dimensions...>>(); }

	constexpr int LD_size()  const { return BC_Shape_Identity_impl::size<dimensions...>(); }
	constexpr int LD_rows()  const { return BC_Shape_Identity_impl::row<dimensions...>(); }
	constexpr int LD_cols()  const { return BC_Shape_Identity_impl::col<dimensions...>(); }
	constexpr int LD_depth() const { return BC_Shape_Identity_impl::depth<dimensions...>(); }
	constexpr int LD_pages() const { return BC_Shape_Identity_impl::pages<dimensions...>(); }
	constexpr int LD_books() const { return BC_Shape_Identity_impl::books<dimensions...>(); }
	constexpr int LD_libraries() const { return BC_Shape_Identity_impl::libraries<dimensions...>(); }

	template<int dim_index> constexpr int LD_dimension() const { return BC_Shape_Identity_impl::dimension<dim_index, dimensions...>(); }
};


template<int  dimensions>
struct Dynamic_Inner_Shape{
	static constexpr bool isDynamic = true;
	static constexpr int  RANK = dimensions;
	int ranks[dimensions];
	int sz = 1;

	const auto& getShape() const {
		 return ranks;
	}
	constexpr int order() const { return dimensions; }

	void initInner(std::initializer_list<int> dims) {
		for (int i = 0; i < dimensions; ++i) {
			ranks[i] = dims.begin()[i];
			sz *= ranks[i];
		}
	};

	void printDimensions() const {
		using namespace Printer;
		for (int i = 0; i < dimensions; ++i) {
			print - "[", ranks[i], "]";
		}
		print - nl;
	}

	 int size()  const { return sz; }
	 int rows()  const { return ranks[0];   }
	 int cols()  const { return dimensions > 0 ? ranks[1] : 1;   }
	 int depth() const { return dimensions > 1 ? ranks[2] : 1; }
	 int pages() const { return dimensions > 2 ? ranks[3] : 1; }
	 int books() const { return dimensions > 3 ? ranks[4] : 1; }
	 int libraries() const { return dimensions > 4 ? ranks[5] : 1; }

	int dimension(int i) { return dimensions > i ? ranks[i] : 1; }


};

template<int dimensions>
struct Dynamic_Outer_Shape {
	static constexpr bool isDynamic = true;
	static constexpr int  LD_RANK = dimensions;

	int LD_ranks[dimensions];

	void initOuter(std::initializer_list<int> dims) {
		LD_ranks[0] = dims.begin()[0];
		for (int i = 1; i < dimensions; ++i) {
			LD_ranks[i] = dims.begin()[i] * LD_ranks[i - 1];
		}
	};
	void initOuter(int* outer) {
		LD_ranks = outer;
	}

	void printLeadingDimensions() const {
		using namespace Printer;
		for (int i = 0; i < dimensions; ++i) {
			print - "[", LD_ranks[i], "]";
		}
		print - nl;
	}


	 int LD_rows()  const { return LD_ranks[0];   }
	 int LD_cols()  const { return dimensions > 0 ? LD_ranks[1] : 1;   }
	 int LD_depth() const { return dimensions > 1 ? LD_ranks[2] : 1; }
	 int LD_pages() const { return dimensions > 2 ? LD_ranks[3] : 1; }
	 int LD_books() const { return dimensions > 3 ? LD_ranks[4] : 1; }
	 int LD_libraries() const { return dimensions > 4 ? LD_ranks[5] : 1; }

	int LD_dimension(int i) { return dimensions > i ? LD_ranks[i] : 1; }

};

}
#endif /* STATIC_SHAPE_H_ */
