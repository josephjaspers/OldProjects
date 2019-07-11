/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LAR_Pounsignedwise.h
 * Author: joseph
 *
 * Creat
 * */
#include "BLACKCAT_CPU_MATHEMATICS.h"
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"


template<typename number_type>
void CPU_MATHEMATICS<number_type>::power(number_type * s, const number_type * m1, const number_type * m2, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = pow(m1[i], m2[i]);
    }
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::divide(number_type * s, const number_type * m1, const number_type * m2, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = m1[i] / m2[i];
    }
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::add(number_type * s, const number_type * m1, const number_type * m2, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = m1[i] + m2[i];
    }
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::subtract(number_type * s, const number_type * m1, const number_type * m2, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = m1[i] - m2[i];
    }
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::multiply(number_type * s, const number_type * m1, const number_type * m2, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = m1[i] * m2[i];
	}
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::power(number_type * s, const number_type * mat, number_type v, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = pow(mat[i], v);
	}
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::divide(number_type * s, const number_type * m, number_type v, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = m[i] / v;
	}
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::add(number_type * s, const number_type * m, number_type v, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = m[i] + v;
	}
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::subtract(number_type * s, const number_type * m, number_type v, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = m[i] - v;
	}
#pragma omp barrier

}

template<typename number_type>
void CPU_MATHEMATICS<number_type>::multiply(number_type * s, const number_type * m, number_type v, unsigned sz) {
#pragma omp parallel for

    for (unsigned i = 0; i < sz; ++i) {
        s[i] = m[i] * v;
	}
#pragma omp barrier

}
