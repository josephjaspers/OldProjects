################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../DEPFILES/UNSIGNDEF_DEFS/LAR_DotProducts_CUDA.cu \
../DEPFILES/UNSIGNDEF_DEFS/LAR_General_CUDA.cu \
../DEPFILES/UNSIGNDEF_DEFS/LAR_PointwiseHighDegree_CUDA.cu \
../DEPFILES/UNSIGNDEF_DEFS/LAR_advanced_CUDA.cu 

OBJS += \
./DEPFILES/UNSIGNDEF_DEFS/LAR_DotProducts_CUDA.o \
./DEPFILES/UNSIGNDEF_DEFS/LAR_General_CUDA.o \
./DEPFILES/UNSIGNDEF_DEFS/LAR_PointwiseHighDegree_CUDA.o \
./DEPFILES/UNSIGNDEF_DEFS/LAR_advanced_CUDA.o 

CU_DEPS += \
./DEPFILES/UNSIGNDEF_DEFS/LAR_DotProducts_CUDA.d \
./DEPFILES/UNSIGNDEF_DEFS/LAR_General_CUDA.d \
./DEPFILES/UNSIGNDEF_DEFS/LAR_PointwiseHighDegree_CUDA.d \
./DEPFILES/UNSIGNDEF_DEFS/LAR_advanced_CUDA.d 


# Each subdirectory must supply rules for building sources it contributes
DEPFILES/UNSIGNDEF_DEFS/%.o: ../DEPFILES/UNSIGNDEF_DEFS/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 -gencode arch=compute_37,code=sm_37 -gencode arch=compute_50,code=sm_50 -gencode arch=compute_52,code=sm_52 -gencode arch=compute_53,code=sm_53 -gencode arch=compute_60,code=sm_60  -odir "DEPFILES/UNSIGNDEF_DEFS" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 --compile --relocatable-device-code=true -gencode arch=compute_50,code=compute_50 -gencode arch=compute_52,code=compute_52 -gencode arch=compute_53,code=compute_53 -gencode arch=compute_60,code=compute_60 -gencode arch=compute_37,code=sm_37 -gencode arch=compute_50,code=sm_50 -gencode arch=compute_52,code=sm_52 -gencode arch=compute_53,code=sm_53 -gencode arch=compute_60,code=sm_60  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


