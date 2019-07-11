//#include "BLACKCAT_GPU_MATHEMATICS.cuh"
//
//
//__global__
//void GPU_MATHEMATICS::dot(float* store, unsigned s_LD, const float* m1, unsigned m1_r, unsigned m1_c, unsigned m1_LD,
//																			 const float* m2, unsigned m2_r, unsigned m2_c, unsigned m2_LD)
//{
////    cublasHandle_t h;
////    cublasCreate(&h);
////    cublasSetPointerMode(h, CUBLAS_POINTER_MODE_DEVICE);
////	cublasSgemm(h, CUBLAS_OP_N, CUBLAS_OP_N,
////            m1_r, m2_c, m1_c,
////            1, m1, m1_LD,
////            m2, m2_LD, 1,
////            store, s_LD);
//}
//
