///*
// * TensorMath.h
// *
// *  Created on: Sep 13, 2017
// *      Author: joseph
// */
//
//#ifndef TENSORMATH_H_
//#define TENSORMATH_H_
//
//#include "LinearAlgebraRoutines.h"
//#include "LinearAlgebraRoutinesGPU.cuh"
//namespace BLACKCAT_LARDesignator {
//
//
//#define GPU_Tensor
//
////Controls if utilizing GPU operations or CPU operations
//#ifndef GPU_Tensor
//template<typename number_type, class math = Tensor_Operations<number_type>>
//#else
//		template<typename number_type, class math = Tensor_OperationsGPU<number_type>>
//#endif
//class TensorMath {
//public:
//
//	   // Pointwise_ LD -scaleable variants - - - - - - - - -COLMAJOR- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	void dot(number_type* store, unsigned store_LD, const number_type* m1, unsigned m1_row, unsigned m1_col, unsigned m1_inc,
//	    											const number_type* m2, unsigned m2_row, unsigned m2_col, unsigned m2_inc) const {
//		math::dot(store, store_LD, m1, m1_row, m1_col, m1_inc, m2, m2_row, m2_col, m2_inc);
//	}
//
//
//	void correlation	(number_type* s, const number_type* filter, const number_type* signal, unsigned sz) const {
//		math::correlation(s, filter, signal ,sz);
//	}
//	void correlation	(number_type* s, unsigned order, const unsigned* ranks,const number_type* filter, const unsigned* f_ld, const number_type* signal, const unsigned* s_ld) const {
//		math::correlation(s, order, ranks, filter, f_ld, signal, s_ld);
//	}
//		 //dimensional --movement correlation
//	void cross_correlation(number_type* s, unsigned cor_mv, unsigned order, const  unsigned* store_ld, const number_type* filter,const  unsigned * f_ld,const  unsigned* f_ranks,
//		    																							const number_type* signal, const unsigned * s_ld, const unsigned* s_ranks) const {
//		math::cross_correlation(s, cor_mv, order, store_ld, filter, f_ld, f_ranks, signal, s_ld, s_ranks);
//	}
//		 //Memory Management [written for preparation for writing with CUDA]]
//	void initialize	(number_type*& d, unsigned sz) const {
//		math::initialize(d, sz);
//	}
//	void destruction	(number_type* d) { math::destruction(d); };
//
//		//Pointwise increments ------------- COL Major --- for degree > 2 Ten
////    void copy     (number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1, const unsigned* m1_LD) const {
////    	math::copy(s, s_ranks, s_LD, m1, m1_LD);
////    }
//
//	void copy     	(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1, const unsigned* m1_LD) const {
//		math::copy(s, s_ranks, order, s_LD, m1, m1_LD);
//	}
//	void fill     	(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, number_type m1) const {
//		math::fill(s, s_ranks, order, s_LD, m1);
//	}
//	void randomize     	(number_type* s, number_type lower_bound, number_type upper_bound, unsigned sz) const {
//#ifndef GPU_Tensor
//		math::randomize(s, lower_bound, upper_bound, sz);
//#endif
//	}
//	void transpose	(number_type* s, unsigned s_ld, const number_type* m, unsigned r, unsigned c, unsigned m_ld) const {
//		math::transpose(s, s_ld, m, r, c, m_ld);
//	}
//
//	void power		(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type* m2,  const unsigned* m2_LD) const {
//		math::power(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
//	}
//	void multiply	(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type* m2,  const unsigned* m2_LD) const {
//		math::multiply(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
//	}
//	void divide	(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type* m2,  const unsigned* m2_LD) const {
//		math::divide(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
//	}
//	void add		(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type* m2,  const unsigned* m2_LD) const {
//		math::add(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
//	}
//	void subtract	(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type* m2,  const unsigned* m2_LD) const {
//		math::subtract(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
//	}
//		    //By Scalar
//	void power		(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type scal) const {
//		math::power(s, s_ranks, order, s_LD, m1, m1_LD, scal);
//	}
//	void multiply	(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type scal) const {
//		math::multiply(s, s_ranks, order, s_LD, m1, m1_LD, scal);
//	}
//	void divide	(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type scal) const {
//		math::divide(s, s_ranks, order, s_LD, m1, m1_LD, scal);
//	}
//	void add		(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type scal) const {
//		math::add(s, s_ranks, order, s_LD, m1, m1_LD, scal);
//	}
//	void subtract	(number_type* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const number_type* m1,  const unsigned* m1_LD, const number_type scal) const {
//		math::subtract(s, s_ranks, order, s_LD, m1, m1_LD, scal);
//	}
//    void print		(const number_type* ary, const unsigned* dims, const unsigned* lead_dims, unsigned index) const {
//    	math::print(ary, dims, lead_dims, index);
//    }
//
//};
//};
//
//
//
//#endif /* TENSORMATH_H_ */
