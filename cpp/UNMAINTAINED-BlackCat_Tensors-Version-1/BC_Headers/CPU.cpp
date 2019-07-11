#include "CPU.h"


/*
 * These are the only non-header functions
 * they are defined here so they can be linked with BLAS (otherwise the compiler skips including blas until
 * after it reads the header files)
 */

void CPU_MATHEMATICS::matmulBLAS(double* c, const double* a, int m, int n, const double* b, int k) {

	cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, k, n, 1, a, m, b, n, 1, c, m);
}
void CPU_MATHEMATICS::matmulBLAS(float* c, const float* a, int m, int n, const float* b, int k) {

	cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, k, n, 1, a, m, b, n, 1, c, m);
}
