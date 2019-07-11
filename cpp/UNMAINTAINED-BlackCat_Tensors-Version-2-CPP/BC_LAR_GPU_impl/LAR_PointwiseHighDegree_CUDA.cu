#include "BLACKCAT_GPU_MATHEMATICS.cuh"



    __global__ void GPU_MATHEMATICS::copy(float* s, const unsigned* ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD) {

	unsigned store_index = 0;
	unsigned m1_index = 0;



	if (order  == 1) {
		copy<<<10,128>>>(s, m1, ranks[order-1]);

	} else {

		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			copy<<<10,128>>>(&s[store_index], ranks, order-1, s_LD, &m1[m1_index], m1_LD);
			store_index += s_LD[order-1];
			m1_index += m1_LD[order-1];
		}
	}
}

    __global__ void GPU_MATHEMATICS::fill(float* s, const unsigned* s_ranks,  unsigned order, const unsigned *s_LD, float m1) {
	if (order == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1;
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			fill<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, m1);
		}
	}
}


//----

    __global__ void GPU_MATHEMATICS::power(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD,
    																															 const float* m2, const unsigned* m2_LD) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			//s[i] = pow(m1[i], m2[i]);
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			power<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, &m2[m2_LD[order - 1] * i], m2_LD);
		}
	}
}


    __global__ void GPU_MATHEMATICS::multiply(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD,
    																															 const float* m2, const unsigned* m2_LD) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1[i] * m2[i];
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			multiply<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, &m2[m2_LD[order - 1] * i], m2_LD);
		}
	}
}


    __global__ void GPU_MATHEMATICS::divide(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD,
    																															 const float* m2, const unsigned* m2_LD) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1[i] / m2[i];
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			divide<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, &m2[m2_LD[order - 1] * i], m2_LD);
		}
	}
}


    __global__ void GPU_MATHEMATICS::add(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD,
    																															 const float* m2, const unsigned* m2_LD) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1[i] + m2[i];
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			add<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, &m2[m2_LD[order - 1] * i], m2_LD);
		}
	}
}



    __global__ void GPU_MATHEMATICS::subtract(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1, const unsigned* m1_LD,
    																															 const float* m2, const unsigned* m2_LD) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1[i] - m2[i];
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			subtract<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, &m2[m2_LD[order - 1] * i], m2_LD);
		}
	}
}

//-----------------------------------------------Scalar Methods ----------------------------------------------------//

__global__ void GPU_MATHEMATICS::power	(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD,
																			const float* m1,  const unsigned* m1_LD, const float scal) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
		//	s[i] = pow(m1[i], scal);
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			power<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, scal);
		}
	}
}

__global__ void GPU_MATHEMATICS::multiply(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD,
																			const float* m1,  const unsigned* m1_LD, const float scal) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1[i] * scal;
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			multiply<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, scal);
		}
	}
}

__global__ void GPU_MATHEMATICS::divide(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,
																			const unsigned* m1_LD, const float scal) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1[i] / scal;
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			divide<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, scal);
		}
	}
}

__global__ void GPU_MATHEMATICS::add(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,
																			const unsigned* m1_LD, const float scal) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1[i] + scal;
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			add<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, scal);
		}
	}
}

__global__ void GPU_MATHEMATICS::subtract(float* s, const unsigned* s_ranks, unsigned order, const unsigned *s_LD, const float* m1,
																			const unsigned* m1_LD, const float scal) {
	if (order  == 1) {
		for (unsigned i = 0; i < s_ranks[0]; ++i) {
			s[i] = m1[i] - scal;
		}
	} else {
		for (unsigned i = 0; i < s_ranks[order - 1]; ++i) {
			subtract<<<10,128>>>(&s[s_LD[order - 1] * i], s_ranks, order - 1, s_LD, &m1[m1_LD[order - 1] * i], m1_LD, scal);
		}
	}
}

