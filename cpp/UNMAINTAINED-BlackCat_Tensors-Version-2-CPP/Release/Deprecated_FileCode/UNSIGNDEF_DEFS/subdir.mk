################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_DotProducts_CUDA.cu \
../Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_General_CUDA.cu \
../Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_PointwiseHighDegree_CUDA.cu \
../Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_advanced_CUDA.cu 

OBJS += \
./Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_DotProducts_CUDA.o \
./Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_General_CUDA.o \
./Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_PointwiseHighDegree_CUDA.o \
./Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_advanced_CUDA.o 

CU_DEPS += \
./Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_DotProducts_CUDA.d \
./Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_General_CUDA.d \
./Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_PointwiseHighDegree_CUDA.d \
./Deprecated_FileCode/UNSIGNDEF_DEFS/LAR_advanced_CUDA.d 


# Each subdirectory must supply rules for building sources it contributes
Deprecated_FileCode/UNSIGNDEF_DEFS/%.o: ../Deprecated_FileCode/UNSIGNDEF_DEFS/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -gencode arch=compute_52,code=sm_52  -odir "Deprecated_FileCode/UNSIGNDEF_DEFS" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 --compile --relocatable-device-code=true -gencode arch=compute_52,code=compute_52 -gencode arch=compute_52,code=sm_52  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


