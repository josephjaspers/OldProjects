/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LAR_General.h
 * Author: joseph
 *
 * Created on July 23, 2017, 3:24 PM
 */

#include "BLACKCAT_GPU_MATHEMATICS.cuh"


 void GPU_MATHEMATICS::initialize(float*& d, unsigned sz) {
	 cudaMalloc((void**)&d, sizeof(float) * sz);
 }
 void GPU_MATHEMATICS::initialize(unsigned*& d, unsigned sz) {
	 cudaMalloc((void**)&d, sizeof(unsigned) * sz);
 }
 void GPU_MATHEMATICS::unified_initialize(unsigned*& d, unsigned sz) {
	cudaMallocManaged((void**)&d, sizeof(unsigned) * sz);
}
 void GPU_MATHEMATICS::unified_initialize(float*& d, unsigned sz) {
	cudaMallocManaged((void**)&d, sizeof(float) * sz);
 }

 void GPU_MATHEMATICS::destruction(float * d) {
    cudaFree(d);
    d = nullptr;
}
 void GPU_MATHEMATICS::destruction(unsigned * d) {
    cudaFree(d);
    d = nullptr;
}

  void GPU_MATHEMATICS::port_copy(float * store, const float * v, unsigned sz) {
     cudaMemcpy(store, v, sizeof(float) * sz, cudaMemcpyHostToDevice);
 }
  void GPU_MATHEMATICS::port_copy_device_to_host(float * store, const float * v, unsigned sz) {
     cudaMemcpy(store, v, sizeof(float) * sz, cudaMemcpyDeviceToHost);
 }
  void GPU_MATHEMATICS::port_copy_device_to_host(unsigned * store, const unsigned * v, unsigned sz) {
     cudaMemcpy(store, v, sizeof(unsigned) * sz, cudaMemcpyDeviceToHost);
 }

__global__ void GPU_MATHEMATICS::copy(float * store, const float * v, unsigned sz) {
    for (int i = 0; i < sz; ++i) {
        store[i] = v[i];
    }
}
__global__ void GPU_MATHEMATICS::copy(unsigned * store, const unsigned * v, unsigned sz) {
    for (int i = 0; i < sz; ++i) {
        store[i] = v[i];
    }
}


__global__ void GPU_MATHEMATICS::fill(float * m, float f, unsigned sz) {
    for (int i = 0; i < sz; ++i) {
        m[i] = f;
    }
}


__global__ void GPU_MATHEMATICS::transpose(float * s, unsigned s_ld, const float * m, unsigned rows, unsigned cols, unsigned m_ld) {

	for (unsigned r = 0; r < rows; ++r) {
		for (unsigned c= 0; c< cols; ++c) {
			s[r * s_ld + c] = m[c * m_ld + r];
		}
	}
}


__global__ void GPU_MATHEMATICS::max(float* max_val, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order) {

	if (order == 1) {
		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			if (*max_val < data[i]) {
				*max_val = data[i];
			}
		}
	} else {

		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			max<<<128,128>>>(max_val, &data[i * ld[order-1]], ranks, ld, order-1);
		}
	}
}


__global__ void GPU_MATHEMATICS::min(float* min_val, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order) {

	if (order == 1) {
		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			if (*min_val < data[i]) {
				*min_val = data[i];
			}
		}
	} else {

		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			min<<<128,128>>>(min_val, &data[i * ld[order-1]], ranks, ld, order-1);
		}
	}
}


__global__ void GPU_MATHEMATICS::max_index(float* max_val, unsigned* max_indexes, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order) {

	if (order == 1) {
		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			if (*max_val < data[i]) {
				*max_val = data[i];
				*max_indexes = i;
			}
		}
	} else {

		float curr_max;
		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			curr_max = *max_val;
			max_index<<<128,128>>>(max_val, max_indexes, &data[i * ld[order-1]], ranks, ld, order-1);

			//if modified -- update
			if (curr_max != *max_val) {
				max_indexes[order-1] = i;
			}
		}
	}
}



__global__ void GPU_MATHEMATICS::min_index(float* min_val, unsigned* min_indexes, const float* data, const unsigned* ranks, const unsigned* ld, unsigned order) {

	if (order == 1) {
		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			if (*min_val < data[i]) {
				*min_val = data[i];
				*min_indexes = i;
			}
		}
	} else {

		float curr_max;
		for (unsigned i = 0; i < ranks[order-1]; ++i) {
			curr_max = *min_val;
			min_index<<<128,128>>>(min_val, min_indexes, &data[i * ld[order-1]], ranks, ld, order-1);

			//if modified -- update
			if (curr_max != *min_val) {
				min_indexes[order-1] = i;
			}
		}
	}
}




__global__ void GPU_MATHEMATICS::randomize(float * m, float lower_bound, float upper_bound, unsigned sz) {
    for (int i = 0; i < sz; ++i) {
      if (i > 5) {
    	  m[i] = i;
      } else {
    	  m[i] = -i;
      }
    }
}


__global__ void GPU_MATHEMATICS::randomize(float * m, unsigned* ld, unsigned* ranks, unsigned order, float lower_bound, float upper_bound) {
    --order;
    if (order == 0) {
    	randomize<<<128,128>>>(m, lower_bound, upper_bound , ranks[order]);
    } else {
    	for (unsigned i = 0; i < ranks[order]; ++i) {
    		randomize<<<128,128>>>(&m[ld[order] * i], ld, ranks, order, lower_bound, upper_bound);
    	}
    }
}

void GPU_MATHEMATICS::print(const float* ary, unsigned sz) {
	for (unsigned i = 0; i < sz; ++i) {
		std::cout << ary[i] << " " << std::endl;
	}
}


 void GPU_MATHEMATICS::print(const float* ary, const unsigned* dims, const unsigned* lead_dims, unsigned index) {


	if (index < 3) {
		for (unsigned r = 0; r < dims[0]; ++r) {

			if (r != 0)
			std::cout << std::endl;

			for (unsigned c = 0; c< dims[1]; ++c) {
				auto str =std::to_string(ary[r + c * lead_dims[index - 1]]);
				str = str.substr(0, str.length() < 3 ? str.length() : 3);
				std::cout << str << " ";
			}
		}
		std::cout << "]" << std::endl << std::endl;

	} else {
		std::cout << "[";
		for (unsigned i = 0; i < dims[index - 1]; ++i) {
			print(&ary[i * lead_dims[index - 1]], dims, lead_dims, index - 1);
		}
	}
}
