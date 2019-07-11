/*
 * GPU.cuh
 *
 *  Created on: Sep 28, 2017
 *      Author: joseph
 */

#ifndef GPU_CUH_
#define GPU_CUH_
#include "BLACKCAT_GPU_MATHEMATICS.cuh"

class GPU {
public:
	// Pointwise_ LD -scaleable variants - - - - - - - - -COLMAJOR- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	static void dot(float* store, unsigned store_LD, const float* m1, unsigned m1_row, unsigned m1_col, unsigned m1_inc, const float* m2, unsigned m2_row, unsigned m2_col, unsigned m2_inc);
	static void zeros(float* x, unsigned sz) {
		cudaMemset(x, 0, sz*sizeof(float));
	}
	static void max(float* max, const float* m1, const unsigned* ranks, const unsigned* ld, unsigned order);
	static void min(float* min, const float* m1, const unsigned* ranks, const unsigned* ld, unsigned order);

	static void min_index(float* min_val, unsigned* min_indexes, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order);
	static void max_index(float* min_val, unsigned* min_indexes, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order);

	static void correlation(float* s, const float* filter, const float* signal, unsigned sz);
	static void correlation(float* s, unsigned order, const unsigned* ranks, const float* filter, const unsigned* f_ld, const float* signal, const unsigned* s_ld);
	//dimensional --movement correlation

	static void cross_correlation(float* s, unsigned cor_mv, const unsigned* store_ld, const float* filter, const unsigned * f_ld, const unsigned* f_ranks, unsigned f_order, const float* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order);
	static void cross_correlation_filter_error(unsigned cor_mv, float* s, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order, const float* filter, const unsigned * f_ld, const unsigned* f_ranks, unsigned f_order, const float* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order);

	static void cross_correlation_signal_error(unsigned cor_mv, float* s, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order, const float* filter, const unsigned * f_ld, const unsigned* f_ranks, unsigned f_order, const float* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order);
//---z-------------------------------------------

//Advanced -- no padding

	//Pointwise
	static void power(float* s, const float* m1, const float* m2, unsigned sz);
	static void divide(float* s, const float* m1, const float* m2, unsigned sz);
	static void add(float* s, const float* m1, const float* m2, unsigned sz);
	static void subtract(float* s, const float* m1, const float* m2, unsigned sz);
	static void multiply(float* s, const float* m1, const float* m2, unsigned sz);
	//Pointwise Scalar
	static void power(float *s, const float *m, float v, unsigned sz);
	static void divide(float *s, const float *m, float v, unsigned sz);
	static void add(float *s, const float *m, float v, unsigned sz);
	static void subtract(float *s, const float *m, float v, unsigned sz);
	static void multiply(float *s, const float *m, float v, unsigned sz);
	//----------------------------------------------

	//Memory Management [written for preparation for writing with CUDA]]
	static void initialize(float*& d, unsigned sz);
	static void initialize(unsigned*& d, unsigned sz);

	static void unified_initialize(float*& d, unsigned sz);
	static void destruction(float* d);

	static void unified_initialize(unsigned*& d, unsigned sz);
	static void destruction(unsigned* d);
	static void copy(unsigned* s, const unsigned* m, unsigned sz);
	static void port_copy(float* device, const float* host, unsigned sz);
	static void port_copy_device_to_host(float* device, const float* host, unsigned sz);
	static void port_copy_device_to_host(unsigned* device, const unsigned* host, unsigned sz);

	static void copy(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD);

	static void copy(float* s, const float* m, unsigned sz);
	static void fill(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, float m1);
	static void fill(float* s, float value, unsigned sz);
	static void randomize(float* s, float lower_bound, float upper_bound, unsigned sz);
	static void transpose(float* s, unsigned s_ld, const float* m, unsigned r, unsigned c, unsigned m_ld);

	static void power(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD);
	static void multiply(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD);
	static void divide(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD);
	static void add(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD);
	static void subtract(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD);
	//By Scalar
	static void power(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal);
	static void multiply(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal);
	static void divide(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal);
	static void add(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal);
	static void subtract(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal);
	static void print(const float* ary, const unsigned* dims, const unsigned* lead_dims, unsigned index);
};

#endif /* GPU_CUH_ */
