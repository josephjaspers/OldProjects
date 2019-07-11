///*
// * BlackCat_Buffered_Mathematics.c
// *
// *  Created on: Oct 13, 2017
// *      Author: joseph
// */
//
//#ifndef BLACKCAT_BUFFERED_MATHEMATICS_C_
//#define BLACKCAT_BUFFERED_MATHEMATICS_C_
//
//template<typename T, class l_value, class r_value, typename oper>
//class Pointwise_Operation {
//
//	l_value* lv;
//	r_value* rv;
//
//	T operator [](unsigned i) {
//		return oper(lv[i], rv[i]);
//	}
//
//	void evaluate(T* assign_to, unsigned sz) {
//		for (unsigned i = 0; i < sz; ++i) {
//			assign_to[i] = oper(lv[i], rv[i]);
//		}
//	};
//
//	struct mul {
//		T operator()(T v1, T v2) {
//			return val1 * val2;
//		}
//	};
//	struct div {
//		T operator()(T v1, T v2) {
//			return val1 / val2;
//		}
//	};
//	struct add {
//		T operator()(T v1, T v2) {
//			return val1 + val2;
//		}
//	};
//	struct sub {
//		T operator()(T v1, T v2) {
//			return val1 - val2;
//		}
//	};
//
//};
//
//#endif /* BLACKCAT_BUFFERED_MATHEMATICS_C_ */
