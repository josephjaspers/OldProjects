/*
 * matmul_custom.h
 *
 *  Created on: Nov 11, 2017
 *      Author: joseph
 */

#ifndef MATMUL_CUSTOM_H_
#define MATMUL_CUSTOM_H_

template<class A, class B, class C>
static void matmul(C c, A a, int m, int n, B b, int k) {
	zero(c, m * k); //fill with zeros first

	//col major
	/*
	 * This implementation shoudl be fast as it accesses every array in sequential (continuous)
	 * order. This should therefor be nearly cache optimal. Other optimizations could be included
	 * such as unrolling the for loop. -- however this should make this implementation easy to
	 * use with open mp
	 *
	 */
#pragma omp parallel for

	for (int z = 0; z < k; ++z) {
		for (int x = 0; x < n; ++x) {
			for (int y = 0; y < m; ++y) {
				c[z * m + y] += a[x * m + y] * b[z * n + x];

//std::cout << "c[" << z * m + y <<"] = a[" << x * m + y << "] * b[" << z * n + x << "]" << std::endl;
			}
		}
	}
#pragma omp barrier

}

template<class A, class B, class C>
static void matmul(C c, A a, int m, int n, B b, int k, bool aT, bool bT) {
	zero(c, m * k); //fill with zeros first

	//col major
	/*
	 * This implementation shoudl be fast as it accesses every array in sequential (continuous)
	 * order. This should therefor be nearly cache optimal. Other optimizations could be included
	 * such as unrolling the for loop. -- however this should make this implementation easy to
	 * use with open mp
	 *
	 */
	if (!aT ^ !bT) {
#pragma omp parallel for

		for (int z = 0; z < k; ++z) {
			for (int x = 0; x < n; ++x) {
				for (int y = 0; y < m; ++y) {
					c[z * m + y] += a[x * m + y] * b[z * n + x];

//std::cout << "c[" << z * m + y <<"] = a[" << x * m + y << "] * b[" << z * n + x << "]" << std::endl;
				}
			}
		}
#pragma omp barrier
	}

	else if (bT) {
#pragma omp parallel for

		for (int z = 0; z < k; ++z) {
			for (int x = 0; x < n; ++x) {
				for (int y = 0; y < m; ++y) {
					c[z * m + y] += a[x * m + y] * b[z + n * x];

					//std::cout << "c[" << z * m + y <<"] = a[" << x * m + y << "] * b[" << z * n + x << "]" << std::endl;
				}
			}
		}
#pragma omp barrier
	}

	else if (aT) {

#pragma omp parallel for
		for (int z = 0; z < k; ++z) {
			for (int x = 0; x < n; ++x) {
				for (int y = 0; y < m; ++y) {
					c[z * m + y] += a[x + m * y] * b[z * n + x];

					//std::cout << "c[" << z * m + y <<"] = a[" << x * m + y << "] * b[" << z * n + x << "]" << std::endl;
				}
			}
		}
#pragma omp barrier
	}

	else if (aT ^ bT) {

#pragma omp parallel for

		for (int z = 0; z < k; ++z) {
			for (int x = 0; x < n; ++x) {
				for (int y = 0; y < m; ++y) {
					c[z * m + y] += a[x * m + y] * b[z + n * x];

					//std::cout << "c[" << z * m + y <<"] = a[" << x * m + y << "] * b[" << z * n + x << "]" << std::endl;
				}
			}
		}
#pragma omp barrier
	}
}

template<class T, class T2>
static void transpose(T to, T2 from, int rowsFrom, int colFrom) {
#pragma omp parallel for

	for (int x = 0; x < rowsFrom; ++x) {
		for (int y = 0; y < colFrom; ++y) {
			to[x + y * colFrom] = from[x * rowsFrom + y];
		}
	}
#pragma omp barrier

}

#endif /* MATMUL_CUSTOM_H_ */
