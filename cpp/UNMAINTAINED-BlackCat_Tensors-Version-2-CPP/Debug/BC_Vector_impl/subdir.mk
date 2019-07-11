################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BC_Vector_impl/Vector_AssignmentOperators.cpp \
../BC_Vector_impl/Vector_BoundryChecking.cpp \
../BC_Vector_impl/Vector_Constructors.cpp 

OBJS += \
./BC_Vector_impl/Vector_AssignmentOperators.o \
./BC_Vector_impl/Vector_BoundryChecking.o \
./BC_Vector_impl/Vector_Constructors.o 

CPP_DEPS += \
./BC_Vector_impl/Vector_AssignmentOperators.d \
./BC_Vector_impl/Vector_BoundryChecking.d \
./BC_Vector_impl/Vector_Constructors.d 


# Each subdirectory must supply rules for building sources it contributes
BC_Vector_impl/%.o: ../BC_Vector_impl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -fopenmp -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


