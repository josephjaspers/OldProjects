################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BC_Headers/CPU.cpp 

OBJS += \
./BC_Headers/CPU.o 

CPP_DEPS += \
./BC_Headers/CPU.d 


# Each subdirectory must supply rules for building sources it contributes
BC_Headers/%.o: ../BC_Headers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -w -fopenmp -I/home/joseph/BlackCatTensor_NsightWorkSpace/BlackCat_Tensors/BC_Headers -I/home/joseph/BlackCatTensor_NsightWorkSpace/BlackCat_Tensors/BC_Headers/Tensor_SuperClasses -I/home/joseph/BlackCatTensor_NsightWorkSpace/BlackCat_Tensors/BC_Headers/Tensor_PrimaryClasses -I/home/joseph/BlackCatTensor_NsightWorkSpace/BlackCat_Tensors/BC_Headers/Iterators -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


