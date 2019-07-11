################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BC_LAR_impl/LAR_DotProducts.cpp \
../BC_LAR_impl/LAR_General.cpp \
../BC_LAR_impl/LAR_Pointwise.cpp \
../BC_LAR_impl/LAR_PointwiseHighDegree.cpp \
../BC_LAR_impl/LAR_advanced.cpp 

OBJS += \
./BC_LAR_impl/LAR_DotProducts.o \
./BC_LAR_impl/LAR_General.o \
./BC_LAR_impl/LAR_Pointwise.o \
./BC_LAR_impl/LAR_PointwiseHighDegree.o \
./BC_LAR_impl/LAR_advanced.o 

CPP_DEPS += \
./BC_LAR_impl/LAR_DotProducts.d \
./BC_LAR_impl/LAR_General.d \
./BC_LAR_impl/LAR_Pointwise.d \
./BC_LAR_impl/LAR_PointwiseHighDegree.d \
./BC_LAR_impl/LAR_advanced.d 


# Each subdirectory must supply rules for building sources it contributes
BC_LAR_impl/%.o: ../BC_LAR_impl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -fopenmp -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


