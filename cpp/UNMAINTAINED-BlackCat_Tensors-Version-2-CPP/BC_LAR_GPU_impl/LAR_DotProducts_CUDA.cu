//#include "BLACKCAT_GPU_MATHEMATICS.cuh"
//
//__global__
//void GPU_MATHEMATICS::dot(float* store, unsigned s_LD, const float* m1, unsigned m1_r, unsigned m1_c, unsigned m1_LD,
//																			 const float* m2, unsigned m2_r, unsigned m2_c, unsigned m2_LD)
//{
////	float* scal_one;
////	cudaMalloc(&scal_one, sizeof(float));
////
////    cublasHandle_t h;
////    cublasCreate(&h);
////    cublasSetPointerMode(h, CUBLAS_POINTER_MODE_DEVICE);
////	cublasSgemm(h,
////			CUBLAS_OP_N,
////			CUBLAS_OP_N,
////            m1_r, //height
////            m2_c, //width
////            m1_c,//wdith
////            scal_one, //alpha
////            m1, //d matb
////            m1_LD, //matb ld
////
////            m2, //d mat a
////            m2_LD, //mat a ld
////            scal_one, //beta scal
////            store, //dmat x
////            s_LD); //ld
////
////	cudaFree(scal_one);
//}
//
