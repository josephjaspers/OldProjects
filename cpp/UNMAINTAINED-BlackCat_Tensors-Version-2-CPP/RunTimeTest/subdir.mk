################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../test.cu \
../text.cu 

OBJS += \
./test.o \
./text.o 

CU_DEPS += \
./test.d \
./text.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 -gencode arch=compute_50,code=sm_50 -gencode arch=compute_52,code=sm_52  -odir "." -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 --compile --relocatable-device-code=true -gencode arch=compute_52,code=compute_52 -gencode arch=compute_50,code=sm_50  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


