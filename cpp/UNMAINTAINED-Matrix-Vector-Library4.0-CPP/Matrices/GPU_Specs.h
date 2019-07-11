#pragma once
#ifndef gpu_specs_h
#define gpu_specs_h

#include "cuda.h"
#include "device_launch_parameters.h"
#include "cuda_runtime.h"

//Stores the basic thread/block restrictions of the user'sz GPU
//Default Values are set to the higher capability models of CUDA
namespace GPU_specs {

	static unsigned MAX_BLOCK_dimx = 1024; //512
	static unsigned MAX_BLOCK_dimy = 1024; //512
	static unsigned MAX_BLOCK_dimz = 64; //64
	static unsigned MAX_THREADS = 1024; //512

	static unsigned DESIRED_THREADS = 256;
	static unsigned DESIRED_BLOCKS = 256;

	static void setCapability_Lower() {
		MAX_BLOCK_dimx = 512;
		MAX_BLOCK_dimy = 512;
		MAX_BLOCK_dimz = 64;
		MAX_THREADS = 512;
	}
	static void setCapability_Greater() {
		MAX_BLOCK_dimx = 1024;
		MAX_BLOCK_dimy = 1024;
		MAX_BLOCK_dimz = 64;
		MAX_THREADS = 1024;
	}
	static void setDefault_DesiredBlocks(int n_blocks) {
		DESIRED_BLOCKS = n_blocks;
	}
	static void setDefault_DesiredThreads(int n_threads) {
		DESIRED_THREADS = n_threads;
	}
}
#endif