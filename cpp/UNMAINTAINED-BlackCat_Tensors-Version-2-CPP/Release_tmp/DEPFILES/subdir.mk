################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DEPFILES/LAR_Indexing.cpp \
../DEPFILES/LAR_Pointwise_Specialized.cpp 

OBJS += \
./DEPFILES/LAR_Indexing.o \
./DEPFILES/LAR_Pointwise_Specialized.o 

CPP_DEPS += \
./DEPFILES/LAR_Indexing.d \
./DEPFILES/LAR_Pointwise_Specialized.d 


# Each subdirectory must supply rules for building sources it contributes
DEPFILES/%.o: ../DEPFILES/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 -gencode arch=compute_37,code=sm_37 -gencode arch=compute_50,code=sm_50 -gencode arch=compute_52,code=sm_52 -gencode arch=compute_53,code=sm_53 -gencode arch=compute_60,code=sm_60  -odir "DEPFILES" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers/BC_HEADERS_GPU_TYPES -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


