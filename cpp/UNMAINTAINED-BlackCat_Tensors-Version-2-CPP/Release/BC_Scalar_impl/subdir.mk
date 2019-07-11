################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BC_Scalar_impl/Scalar_Constructors.cpp \
../BC_Scalar_impl/Scalar_Operators.cpp 

OBJS += \
./BC_Scalar_impl/Scalar_Constructors.o \
./BC_Scalar_impl/Scalar_Operators.o 

CPP_DEPS += \
./BC_Scalar_impl/Scalar_Constructors.d \
./BC_Scalar_impl/Scalar_Operators.d 


# Each subdirectory must supply rules for building sources it contributes
BC_Scalar_impl/%.o: ../BC_Scalar_impl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -fopenmp -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


