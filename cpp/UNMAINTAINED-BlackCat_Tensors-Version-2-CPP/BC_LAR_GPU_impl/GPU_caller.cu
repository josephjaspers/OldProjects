#include "GPU.h"

void initialize_blockThreads(unsigned& numb_blocks, unsigned& numb_threads, const unsigned* ranks, unsigned order)
{

	numb_blocks = 8;
	numb_threads = 512;

	return;

//	if (order > 1)
//		if (ranks[0] < 1024)
//		{
//			numb_threads = ranks[order - 1];
//			numb_blocks = 1;
//		} else
//		{
//			numb_threads = 128;
//			numb_blocks = ceil(ranks[order - 1] / numb_threads);
//
//		}
}

void initialize_blockThreads(unsigned& numb_blocks, unsigned& numb_threads, unsigned sz)
{
	numb_blocks = 8;
	numb_threads = 512;

	return;

//	if (sz < 1024)
//	{
//		numb_threads = sz;
//		numb_blocks = 1;
//	} else
//	{
//		numb_threads = 128;
//		numb_blocks = ceil(sz / numb_threads);
//
//	}
}

__global__
void one_init(float* f) {
	*f = 1;
}

void GPU::dot(float* store, unsigned store_LD, const float* m1, unsigned m1_row, unsigned m1_col, unsigned m1_inc, const float* m2, unsigned m2_row, unsigned m2_col, unsigned m2_inc)
{


	float* scal_one;
	cudaMalloc((void**)&scal_one, sizeof(float));

	one_init<<<numb_blocks, numb_threads>>>(scal_one);
    cublasHandle_t h;
    cublasCreate(&h);
    cublasSetPointerMode(h, CUBLAS_POINTER_MODE_DEVICE);
	cublasSgemm(h,
			CUBLAS_OP_N,
			CUBLAS_OP_N,
            m1_row, //height
            m2_col, //width
            m1_col,//wdith
            scal_one, //alpha
            m1, //d matb
            m1_inc, //matb ld

            m2, //d mat a
            m2_inc, //mat a ld
            scal_one, //beta scal
            store, //dmat x
            store_LD); //ld

	cudaDeviceSynchronize();
	cudaFree(scal_one);
	cublasDestroy(h);
	cudaDeviceSynchronize();

}

void GPU::max(float* max, const float* m1, const unsigned* ranks, const unsigned* ld, unsigned order)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, ranks, order);

	GPU_MATHEMATICS::max<<<numb_blocks, numb_threads>>>(max, m1, ranks, ld, order);
	cudaDeviceSynchronize();
}
void GPU::min(float* min, const float* m1, const unsigned* ranks, const unsigned* ld, unsigned order)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, ranks, order);

	GPU_MATHEMATICS::min<<<numb_blocks, numb_threads>>>(min, m1, ranks, ld, order);
	cudaDeviceSynchronize();
}

void GPU::min_index(float* min_val, unsigned* min_indexes, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, ranks, order);

	GPU_MATHEMATICS::min_index<<<numb_blocks, numb_threads>>>(min_val, min_indexes, data, ranks, ld, order);
	cudaDeviceSynchronize();
}
void GPU::max_index(float* min_val, unsigned* min_indexes, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, ranks, order);

	GPU_MATHEMATICS::max_index<<<numb_blocks, numb_threads>>>(min_val, min_indexes, data, ranks, ld, order);
	cudaDeviceSynchronize();
}

void GPU::correlation(float* s, const float* filter, const float* signal, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);

	GPU_MATHEMATICS::correlation<<<numb_blocks, numb_threads>>>(s, filter, signal ,sz);
	cudaDeviceSynchronize();
}
void GPU::correlation(float* s, unsigned order, const unsigned* ranks, const float* filter, const unsigned* f_ld, const float* signal, const unsigned* s_ld)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, ranks, order);

	GPU_MATHEMATICS::correlation<<<numb_blocks, numb_threads>>>(s, order, ranks, filter, f_ld, signal, s_ld);
	cudaDeviceSynchronize();
}
//dimensional --movement correlation

void GPU::cross_correlation(float* s, unsigned cor_mv, const unsigned* store_ld, const float* filter, const unsigned * f_ld, const unsigned* f_ranks, unsigned f_order, const float* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, s_order);

	GPU_MATHEMATICS::cross_correlation<<<numb_blocks, numb_threads>>>(s, cor_mv, store_ld, filter, f_ld, f_ranks, f_order, signal, s_ld, s_ranks, s_order);
	cudaDeviceSynchronize();
}
void GPU::cross_correlation_filter_error(unsigned cor_mv, float* s, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order, const float* filter, const unsigned * f_ld, const unsigned* f_ranks, unsigned f_order, const float* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, s_order);

	GPU_MATHEMATICS::cc_filter_error<<<numb_blocks, numb_threads>>>(cor_mv, s, store_ld, store_ranks, store_order, filter, f_ld, f_ranks, f_order, signal, s_ld, s_ranks, s_order);
	cudaDeviceSynchronize();
}

void GPU::cross_correlation_signal_error(unsigned cor_mv, float* s, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order, const float* filter, const unsigned * f_ld, const unsigned* f_ranks, unsigned f_order, const float* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, s_order);

	GPU_MATHEMATICS::cc_signal_error<<<numb_blocks, numb_threads>>>(cor_mv, s, store_ld, store_ranks, store_order, filter, f_ld, f_ranks, f_order, signal, s_ld, s_ranks, s_order);
	cudaDeviceSynchronize();
}

//Memory Management [written for preparation for writing with CUDA]]
void GPU::initialize(float*& d, unsigned sz)
{
	GPU_MATHEMATICS::initialize(d, sz);
	cudaDeviceSynchronize();

}
void GPU::initialize(unsigned*& d, unsigned sz)
{
	GPU_MATHEMATICS::initialize(d, sz);
	cudaDeviceSynchronize();

}
void GPU::unified_initialize(float*& d, unsigned sz)
{
	GPU_MATHEMATICS::unified_initialize(d, sz);
	cudaDeviceSynchronize();
}
void GPU::destruction(float* d)
{
	GPU_MATHEMATICS::destruction(d);
	cudaDeviceSynchronize();
}

//unsgined
void GPU::unified_initialize(unsigned*& d, unsigned sz)
{
	GPU_MATHEMATICS::unified_initialize(d, sz);
	cudaDeviceSynchronize();
}
void GPU::destruction(unsigned* d)
{
	GPU_MATHEMATICS::destruction(d);
	cudaDeviceSynchronize();
}

void GPU::port_copy(float* s, const float* m, unsigned sz) {
	GPU_MATHEMATICS::port_copy(s, m, sz);
}

void GPU::port_copy_device_to_host(float* s, const float* m, unsigned sz) {
	GPU_MATHEMATICS::port_copy_device_to_host(s, m, sz);
}

void GPU::port_copy_device_to_host(unsigned* s, const unsigned* m, unsigned sz) {
	GPU_MATHEMATICS::port_copy_device_to_host(s, m, sz);
}
void GPU::copy(unsigned* s, const unsigned* m, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);

	GPU_MATHEMATICS::copy<<<numb_blocks, numb_threads>>>(s, m ,sz);
	cudaDeviceSynchronize();
}
//end
void GPU::copy(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::copy<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD);
	cudaDeviceSynchronize();
}

void GPU::copy(float* s, const float* m, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);

	GPU_MATHEMATICS::copy<<<numb_blocks, numb_threads>>>(s, m ,sz);
	cudaDeviceSynchronize();
}

void GPU::fill(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, float m1)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::fill<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1);
	cudaDeviceSynchronize();
}
void GPU::fill(float* s, float value, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);

	GPU_MATHEMATICS::fill<<<numb_blocks, numb_threads>>>(s, value, sz);
	cudaDeviceSynchronize();
}
void GPU::randomize(float* s, float lower_bound, float upper_bound, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);

	GPU_MATHEMATICS::randomize<<<numb_blocks, numb_threads>>>(s, lower_bound, upper_bound, sz);
	cudaDeviceSynchronize();
}

void GPU::transpose(float* s, unsigned s_ld, const float* m, unsigned r, unsigned c, unsigned m_ld)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, r * c);

	GPU_MATHEMATICS::transpose<<<numb_blocks, numb_threads>>>(s, s_ld, m, r, c, m_ld);
	cudaDeviceSynchronize();
}

void GPU::power(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::power<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
	cudaDeviceSynchronize();
}
void GPU::multiply(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::multiply<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
	cudaDeviceSynchronize();
}
void GPU::divide(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::divide<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
	cudaDeviceSynchronize();
}
void GPU::add(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::add<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
	cudaDeviceSynchronize();
}
void GPU::subtract(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float* m2, const unsigned* m2_LD)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::subtract<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, m2, m2_LD);
	cudaDeviceSynchronize();
}
//By Scalar
void GPU::power(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::power<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, scal);
	cudaDeviceSynchronize();
}
void GPU::multiply(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::multiply<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, scal);
	cudaDeviceSynchronize();
}
void GPU::divide(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::divide<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, scal);
	cudaDeviceSynchronize();
}
void GPU::add(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::add<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, scal);
	cudaDeviceSynchronize();
}
void GPU::subtract(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD, const float scal)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, s_ranks, order);

	GPU_MATHEMATICS::subtract<<<numb_blocks, numb_threads>>>(s, s_ranks, order, s_LD, m1, m1_LD, scal);
	cudaDeviceSynchronize();
}
void GPU::print(const float* ary, const unsigned* dims, const unsigned* lead_dims, unsigned index)
{
	unsigned sz = 1;
	for (unsigned i = 0; i < index; ++i)
	{
		sz *= dims[i];
	}
	float* tmp = new float[sz];
	cudaMemcpy(tmp, ary, sizeof(float) * sz, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();
	GPU_MATHEMATICS::print(tmp, dims, lead_dims, index);

	delete[] tmp;
	std::cout << " fin print " << std::endl;
}

void GPU::power(float* s, const float* m1, const float* m2, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);

	GPU_MATHEMATICS::power<<<numb_blocks, numb_threads>>>(s, m1, m2 ,sz);
	cudaDeviceSynchronize();

}
void GPU::divide(float* s, const float* m1, const float* m2, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::divide<<<numb_blocks, numb_threads>>>(s, m1, m2 ,sz);
	cudaDeviceSynchronize();


}
void GPU::add(float* s, const float* m1, const float* m2, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::add<<<numb_blocks, numb_threads>>>(s, m1, m2 ,sz);
	cudaDeviceSynchronize();
}
void GPU::subtract(float* s, const float* m1, const float* m2, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::subtract<<<numb_blocks, numb_threads>>>(s, m1, m2 ,sz);
	cudaDeviceSynchronize();

}
void GPU::multiply(float* s, const float* m1, const float* m2, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::multiply<<<numb_blocks, numb_threads>>>(s, m1, m2 ,sz);
	cudaDeviceSynchronize();

}
//Pointwise Scalar
void GPU::power(float *s, const float *m, float v, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::power<<<numb_blocks, numb_threads>>>(s, m, v ,sz);
	cudaDeviceSynchronize();

}
void GPU::divide(float *s, const float *m, float v, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::divide<<<numb_blocks, numb_threads>>>(s, m, v ,sz);
	cudaDeviceSynchronize();

}
void GPU::add(float *s, const float *m, float v, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::add<<<numb_blocks, numb_threads>>>(s, m, v ,sz);
	cudaDeviceSynchronize();

}
void GPU::subtract(float *s, const float *m, float v, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::subtract<<<numb_blocks, numb_threads>>>(s, m, v ,sz);
	cudaDeviceSynchronize();

}
void GPU::multiply(float *s, const float *m, float v, unsigned sz)
{
	unsigned numb_blocks;
	unsigned numb_threads;
	initialize_blockThreads(numb_blocks, numb_threads, sz);
	GPU_MATHEMATICS::multiply<<<numb_blocks, numb_threads>>>(s, m, v ,sz);
	cudaDeviceSynchronize();
}

