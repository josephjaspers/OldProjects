################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/GPU_caller.cu \
../GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_DotProducts_CUDA.cu \
../GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_General_CUDA.cu \
../GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_POINTWISE_CUDA.cu \
../GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_PointwiseHighDegree_CUDA.cu \
../GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_advanced_CUDA.cu 

OBJS += \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/GPU_caller.o \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_DotProducts_CUDA.o \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_General_CUDA.o \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_POINTWISE_CUDA.o \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_PointwiseHighDegree_CUDA.o \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_advanced_CUDA.o 

CU_DEPS += \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/GPU_caller.d \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_DotProducts_CUDA.d \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_General_CUDA.d \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_POINTWISE_CUDA.d \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_PointwiseHighDegree_CUDA.d \
./GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/LAR_advanced_CUDA.d 


# Each subdirectory must supply rules for building sources it contributes
GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/%.o: ../GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 -gencode arch=compute_52,code=sm_52  -odir "GPU_LIB_ImplementationDelayedNotSupportedCurrently/BC_LAR_GPU_impl" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 --compile --relocatable-device-code=true -gencode arch=compute_52,code=compute_52 -gencode arch=compute_52,code=sm_52  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


