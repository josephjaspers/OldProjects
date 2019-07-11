///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///*
// * File:   LinearAlgebraRoutines.h
// * Author: joseph
// *
// * Created on July 23, 2017, 9:11 PM
// */
//
//#ifndef gpu_math_uint_blackcat
//#define gpu_math_uint_blackcat
//#include <iostream>
//#include <math.h>
//#include <cuda.h>
//#include <cuda_runtime.h>
//#include <cublas_v2.h>
//#include <stdio.h>
//
//
//
//
//namespace GPU_MATHEMATICS {
//
//	//Memory Management [written for preparation for writing with CUDA]]
//	   void initialize	(unsigned*& d, unsigned sz);
//	   void destruction	(unsigned* d);
//	   void unified_initialize(unsigned*& d, unsigned sz) ;
//
//	//Pure pointwise methods (no LD)
//       __global__  void copy		(unsigned* store, const unsigned* v, unsigned sz);
//       __global__  void fill		(unsigned* m, unsigned f, unsigned sz);
//       __global__  void randomize	(unsigned* m, unsigned lower_bound, unsigned upper_bound, unsigned sz);
//       	   	   	   void print 		(const unsigned* m, unsigned sz);
//
//    //Advanced -- no padding
//       __global__  void correlation(unsigned* s, const unsigned* filter, const unsigned* signal, unsigned sz);
//
//    //Pointwise
//       __global__  void power		(unsigned* s, const unsigned* m1, const unsigned* m2, unsigned sz);
//       __global__  void divide		(unsigned* s, const unsigned* m1, const unsigned* m2, unsigned sz);
//       __global__  void add			(unsigned* s, const unsigned* m1, const unsigned* m2, unsigned sz);
//       __global__  void subtract	(unsigned* s, const unsigned* m1, const unsigned* m2, unsigned sz);
//       __global__  void multiply	(unsigned* s, const unsigned* m1, const unsigned* m2, unsigned sz);
//    //Pointwise Scalar
//       __global__  void power		(unsigned *s, const unsigned *m, unsigned v, unsigned sz);
//       __global__  void divide		(unsigned *s, const unsigned *m, unsigned v, unsigned sz);
//       __global__  void add			(unsigned *s, const unsigned *m, unsigned v, unsigned sz);
//       __global__  void subtract	(unsigned *s, const unsigned *m, unsigned v, unsigned sz);
//       __global__  void multiply	(unsigned *s, const unsigned *m, unsigned v, unsigned sz);
//
//    //---Primary Indexers
//       __global__  void max(const unsigned* m, unsigned* ld, unsigned* ranks, unsigned order, unsigned* max_val);
//       __global__  void min(const unsigned* m, unsigned* ld, unsigned* ranks, unsigned order, unsigned* max_val);
//
//       __global__  void max_index(unsigned* min_val, unsigned* min_indexes, const unsigned* data, const unsigned* ranks, const unsigned* ld, unsigned order);
//       __global__  void min_index(unsigned* min_val, unsigned* min_indexes, const unsigned* data, const unsigned* ranks, const unsigned* ld, unsigned order);
//
//   // Pointwise_ LD -scaleable variants - - - - - - - - -COLMAJOR- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//       __global__  void dot		(unsigned* store, unsigned store_LD, const unsigned* m1, unsigned m1_row, unsigned m1_col, unsigned m1_inc,
//    															const unsigned* m2, unsigned m2_row, unsigned m2_col, unsigned m2_inc);
//    //Pointwise increments ------------- COL Major --- for degree > 2 Ten
//       __global__  void copy     (unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1, const unsigned* m1_LD);
//       __global__  void fill     (unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, unsigned m1);
//       __global__  void transpose(unsigned* s, unsigned s_ld, const unsigned* m, unsigned r, unsigned c, unsigned m_ld);
//       __global__  void randomize(unsigned* s, unsigned* s_ld, unsigned* ranks, unsigned order, unsigned lb, unsigned ub);
//       __global__  void print		(const unsigned* ary, const unsigned* dims, const unsigned* lead_dims, unsigned index);
//
//    //Advanced operations
//       __global__  void axpy(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,
//    		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  const unsigned* m1_LD, unsigned scalar);
//
//
//       __global__  void correlation(unsigned* s, unsigned order, const unsigned* ranks,const unsigned* filter, const unsigned* f_ld,
//    																		      const unsigned* signal, const unsigned* s_ld);
//
//       __global__  void cross_correlation(unsigned* s, unsigned cor_mv, const  unsigned* store_ld, const unsigned* filter,const  unsigned * f_ld,const  unsigned* f_ranks, unsigned f_order,
//    																								const unsigned* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order);
//
//
//       __global__  void axpy(unsigned* store, const unsigned* store_ld, const unsigned* signal, const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order, unsigned scalar);
//
//       __global__  void neg_axpy(unsigned* store, const unsigned* store_ld, const unsigned* signal, const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order, unsigned scalar);
//
//       __global__  void cc_filter_error(unsigned move_dimensions, unsigned* store, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order,
//    		 const  unsigned* error, const unsigned* error_ld, const unsigned* error_ranks, unsigned error_order,
//    		 const  unsigned* signal,const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order);
//
//       __global__  void cc_signal_error(unsigned move_dimensions, unsigned* store, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order,
//         		 const  unsigned* error, const unsigned* error_ld, const unsigned* error_ranks, unsigned error_order,
//         		 const  unsigned* signal,const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order);
//
//     //Pointwise
//       __global__  void power	(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned* m2,  const unsigned* m2_LD);
//       __global__  void multiply(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned* m2,  const unsigned* m2_LD);
//       __global__  void divide	(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned* m2,  const unsigned* m2_LD);
//       __global__  void add		(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned* m2,  const unsigned* m2_LD);
//       __global__  void subtract(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned* m2,  const unsigned* m2_LD);
//    //By Scalar
//       __global__  void power	(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned scal);
//       __global__  void multiply(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned scal);
//       __global__  void divide	(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned scal);
//       __global__  void add		(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned scal);
//       __global__  void subtract(unsigned* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const unsigned* m1,  const unsigned* m1_LD, const unsigned scal);
//
//       __global__  void max(unsigned* max, const unsigned* data, const unsigned *ranks, const unsigned* ld, unsigned order);
//       __global__  void min(unsigned* min, const unsigned* data, const unsigned *ranks, const unsigned* ld, unsigned order);
//};
//#endif /* LINEARALGEBRAROUTINES_HCUDA */
//
