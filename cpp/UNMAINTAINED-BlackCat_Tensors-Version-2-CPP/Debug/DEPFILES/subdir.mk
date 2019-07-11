################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DEPFILES/DEPSCALAR.cpp \
../DEPFILES/LAR_Indexing.cpp \
../DEPFILES/LAR_Pointwise_Specialized.cpp 

OBJS += \
./DEPFILES/DEPSCALAR.o \
./DEPFILES/LAR_Indexing.o \
./DEPFILES/LAR_Pointwise_Specialized.o 

CPP_DEPS += \
./DEPFILES/DEPSCALAR.d \
./DEPFILES/LAR_Indexing.d \
./DEPFILES/LAR_Pointwise_Specialized.d 


# Each subdirectory must supply rules for building sources it contributes
DEPFILES/%.o: ../DEPFILES/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -G -g -O0 -std=c++11 -gencode arch=compute_52,code=sm_52  -odir "DEPFILES" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -G -g -O0 -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


