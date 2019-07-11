/*
 * BC_Expression_Binary_Functors.h
 *
 *  Created on: Dec 1, 2017
 *      Author: joseph
 */
#ifdef  __CUDACC__
#ifndef EXPRESSION_BINARY_FUNCTORS_H_
#define EXPRESSION_BINARY_FUNCTORS_H_
#include "../BlackCat_Internal_Definitions.h" //__BC_gcpu__

#include <iostream>
namespace BC {
		struct assign {

		template<class lv, class rv> __BC_gcpu__
		inline __attribute__((always_inline)) auto& operator ()(lv& l, rv r) const {
			return (l = r);
		}
	};

	struct combine {

		template<class lv, class rv> __BC_gcpu__
		inline __attribute__((always_inline)) auto operator ()(lv l, rv r) const {
			return l;
		}
	};


	struct add {

		template<class lv, class rv> __BC_gcpu__
		inline __attribute__((always_inline)) auto operator ()(lv l, rv r) const {
			return l + r;
		}
	};

	struct mul {
		template<class lv, class rv> __BC_gcpu__
		inline __attribute__((always_inline)) auto operator ()(lv l, rv r) const {
			return l * r;
		}
	};

	struct sub {
		template<class lv, class rv> __BC_gcpu__
		inline __attribute__((always_inline)) auto operator ()(lv l, rv r) const {
			return l - r;
		}
	};

	struct div {
		template<class lv, class rv> __BC_gcpu__
		inline __attribute__((always_inline)) auto operator ()(lv l, rv r) const {
			return l / r;
		}
	};
}


#endif /* EXPRESSION_BINARY_FUNCTORS_H_ */
#endif
