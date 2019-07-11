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
//#ifndef gpu_math_float_blackcat
//#define gpu_math_float_blackcat
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
//	   void initialize	(float*& d, unsigned sz);
//	   void destruction	(float* d);
//	   void unified_initialize(float*& d, unsigned sz) ;
//	   void unified_initialize(unsigned*& d, unsigned sz) ;
//       __global__  void copy		(unsigned* store, const unsigned* v, unsigned sz);
//
//	//Pure pointwise methods (no LD)
//       __global__  void copy		(float* store, const float* v, unsigned sz);
//       __global__  void fill		(float* m, float f, unsigned sz);
//       __global__  void randomize	(float* m, float lower_bound, float upper_bound, unsigned sz);
//       	   	   	   void print 		(const float* m, unsigned sz);
//
//    //Advanced -- no padding
//       __global__  void correlation(float* s, const float* filter, const float* signal, unsigned sz);
//
//    //Pointwise
//       __global__  void power		(float* s, const float* m1, const float* m2, unsigned sz);
//       __global__  void divide		(float* s, const float* m1, const float* m2, unsigned sz);
//       __global__  void add			(float* s, const float* m1, const float* m2, unsigned sz);
//       __global__  void subtract	(float* s, const float* m1, const float* m2, unsigned sz);
//       __global__  void multiply	(float* s, const float* m1, const float* m2, unsigned sz);
//    //Pointwise Scalar
//       __global__  void power		(float *s, const float *m, float v, unsigned sz);
//       __global__  void divide		(float *s, const float *m, float v, unsigned sz);
//       __global__  void add			(float *s, const float *m, float v, unsigned sz);
//       __global__  void subtract	(float *s, const float *m, float v, unsigned sz);
//       __global__  void multiply	(float *s, const float *m, float v, unsigned sz);
//
//    //---Primary Indexers
//       __global__  void max(const float* m, unsigned* ld, unsigned* ranks, unsigned order, float* max_val);
//       __global__  void min(const float* m, unsigned* ld, unsigned* ranks, unsigned order, float* max_val);
//
//       __global__  void max_index(float* min_val, unsigned* min_indexes, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order);
//       __global__  void min_index(float* min_val, unsigned* min_indexes, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order);
//
//   // Pointwise_ LD -scaleable variants - - - - - - - - -COLMAJOR- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//       __global__  void dot		(float* store, unsigned store_LD, const float* m1, unsigned m1_row, unsigned m1_col, unsigned m1_inc,
//    															const float* m2, unsigned m2_row, unsigned m2_col, unsigned m2_inc);
//    //Pointwise increments ------------- COL Major --- for degree > 2 Ten
//       __global__  void copy     (float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD);
//       __global__  void fill     (float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, float m1);
//       __global__  void transpose(float* s, unsigned s_ld, const float* m, unsigned r, unsigned c, unsigned m_ld);
//       __global__  void randomize(float* s, unsigned* s_ld, unsigned* ranks, unsigned order, float lb, float ub);
//       __global__  void print		(const float* ary, const unsigned* dims, const unsigned* lead_dims, unsigned index);
//
//    //Advanced operations
//       __global__  void axpy(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,
//    		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  const unsigned* m1_LD, float scalar);
//
//
//       __global__  void correlation(float* s, unsigned order, const unsigned* ranks,const float* filter, const unsigned* f_ld,
//    																		      const float* signal, const unsigned* s_ld);
//
//       __global__  void cross_correlation(float* s, unsigned cor_mv, const  unsigned* store_ld, const float* filter,const  unsigned * f_ld,const  unsigned* f_ranks, unsigned f_order,
//    																								const float* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order);
//
//
//       __global__  void axpy(float* store, const unsigned* store_ld, const float* signal, const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order, float scalar);
//
//       __global__  void neg_axpy(float* store, const unsigned* store_ld, const float* signal, const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order, float scalar);
//
//       __global__  void cc_filter_error(unsigned move_dimensions, float* store, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order,
//    		 const  float* error, const unsigned* error_ld, const unsigned* error_ranks, unsigned error_order,
//    		 const  float* signal,const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order);
//
//       __global__  void cc_signal_error(unsigned move_dimensions, float* store, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order,
//         		 const  float* error, const unsigned* error_ld, const unsigned* error_ranks, unsigned error_order,
//         		 const  float* signal,const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order);
//
//     //Pointwise
//       __global__  void power	(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float* m2,  const unsigned* m2_LD);
//       __global__  void multiply(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float* m2,  const unsigned* m2_LD);
//       __global__  void divide	(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float* m2,  const unsigned* m2_LD);
//       __global__  void add		(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float* m2,  const unsigned* m2_LD);
//       __global__  void subtract(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float* m2,  const unsigned* m2_LD);
//    //By Scalar
//       __global__  void power	(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float scal);
//       __global__  void multiply(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float scal);
//       __global__  void divide	(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float scal);
//       __global__  void add		(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float scal);
//       __global__  void subtract(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,  const unsigned* m1_LD, const float scal);
//
//       __global__  void max(float* max, const float* data, const unsigned *ranks, const unsigned* ld, unsigned order);
//       __global__  void min(float* min, const float* data, const unsigned *ranks, const unsigned* ld, unsigned order);
//};
//#endif /* LINEARALGEBRAROUTINES_HCUDA */
//
