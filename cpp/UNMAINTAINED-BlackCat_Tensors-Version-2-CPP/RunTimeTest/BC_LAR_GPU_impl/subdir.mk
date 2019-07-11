################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../BC_LAR_GPU_impl/GPU_caller.cu 

OBJS += \
./BC_LAR_GPU_impl/GPU_caller.o 

CU_DEPS += \
./BC_LAR_GPU_impl/GPU_caller.d 


# Each subdirectory must supply rules for building sources it contributes
BC_LAR_GPU_impl/%.o: ../BC_LAR_GPU_impl/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 -gencode arch=compute_50,code=sm_50 -gencode arch=compute_52,code=sm_52  -odir "BC_LAR_GPU_impl" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 --compile --relocatable-device-code=true -gencode arch=compute_52,code=compute_52 -gencode arch=compute_50,code=sm_50  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


