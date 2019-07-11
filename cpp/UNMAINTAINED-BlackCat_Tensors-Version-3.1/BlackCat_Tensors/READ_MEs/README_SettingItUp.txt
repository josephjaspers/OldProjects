BlackCat_Tensors-- Header only LinearAlgebra Library, designed for functional programming for Neural Networks
Author JosephJaspers : Current WestChester University - Student Researcher - 
Project: BlackCatTensors


--------------------------------------------Notice--------------------------------------------

If using any of this code you must include this read me. 

You must comment any changes made that differ from the original source in the source files clearly. 
You must include the date of the respository. 

This is an open source project. 
Please report any bugs or issues on JosephJaspers - github
Anytime you use this code please give apropriate credit.

(I'm just a student researcher IE I need all the credit I can get)





-------------------------------------LIBRARIES YOU MUST LINK AGAINST-------------------------

openmp 		  (if you like multithreading)
cublas 		  (if you like gpu dotproducts)
cblas && f77blas  (if you like dotproducts)  

-----------------------------------------Knobs for Optimization---------------------------------------

BC_CORE/BlackCat_Internal_Definitions 
		gives 2 constexpr ints:
			static constexpr int BC_CPU_SINGLE_THREAD_THRESHOLD = 999;
			static constexpr int CUDA_BASE_THREADS = 256;
		Adjust these to your preference 
			
			BC_CPU_SINGLE_THREAD_THRESHOLD  -- determines the minimum size to multi-thread pointwise operations (applies to all pointwise operations)
			CUDA_BASE_THREADS				-- determines the block/thread ratio base-thread quantity
			
			The two methods that determine threadblocks are defined in:
			BC_CORE/BC_MathLibraries/Mathematics_GPU.cu with the following implementation:
			
				static int blocks(int size) {
					return (size + CUDA_BASE_THREADS - 1) / CUDA_BASE_THREADS;
				}
				static int threads() {
					return CUDA_BASE_THREADS;
				}	
	



-----------------------------------------Setting it up----------------------------------------
//This is a header only library with .cu files. 
If using it in an executable remember to place your main method in a .cu file. 

To use, simply add the primary folder to your path and include "BlackCat_Tensors.h"
You may also choose to include "Functions/BlackCat_TensorFunctions.cu" which give access to NeuralNetwork functions
YOU MUST USE THE NVCC TO COMPILE THIS

IF YOU DO NOT HAVE THE NVCC (GO TO BOTTOM OF THIS)

##(My) CommandLine Options:
nvcc -fopenmp --std=c++17 -expt-relaxed-constexpr

##Include Paths (Obviously these depend on your system):
/usr/local/cuda-9.1/bin				##The cuda development kit
/usr/local/cuda/include				##The cuda development kit
/usr/local/include/atlas-base		##Replace with your BLAS library

##Linker:
nvcc -fopenmp 

##Linker Libraries
cblas
f77blas
cublas
gomp

##Library Include Paths (Obviously these depend on your system)
/usr/lib/atlas-base				##for BLAS
/usr/local/cuda/include			##for CUBLAS
/usr/local/cuda-9.1/bin			##for other CUDA

##Preproccessor Options for XCompiler ***This is required to use NVCC and OpenMP 
-fopenmp


**If you do not have an NVCC compiler (IE CUDA toolkit), add the following to the command line (this is not tested):
-X 
Expression_Binary_Dotproduct_impl.cu
Expression_Binary_Dotproduct.cu
Expression_Binary_Functors.cu
Expression_Binary_Pointwise_Scalar.cu
Expression_Binary_Pointwise.cu
Expression_Unary_MatrixTransposition.cu
Expression_Unary_Negation.cu
Expression_Unary_Pointwise.cu
SubTensor_Expression.cu
c-header

**This reinterperts the cuda-source files as header files. 


-----------------------------------------Setting it up (no NVCC)-----------------------------------------

go to BC_Core/Expressions/

change all of suffixes: 
	.cu to .h

you may need to refactor a few files that include these if your IDE does not do it for you.
Now the files should compile as purely C++14 (no GPU support) 

I will try to add a CPU only version to my github. 

(recommded: GCC) 



