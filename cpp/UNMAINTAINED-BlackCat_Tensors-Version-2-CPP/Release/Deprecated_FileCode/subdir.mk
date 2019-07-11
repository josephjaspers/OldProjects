################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Deprecated_FileCode/DEPSCALAR.cpp \
../Deprecated_FileCode/LAR_Indexing.cpp \
../Deprecated_FileCode/LAR_Pointwise_Specialized.cpp 

OBJS += \
./Deprecated_FileCode/DEPSCALAR.o \
./Deprecated_FileCode/LAR_Indexing.o \
./Deprecated_FileCode/LAR_Pointwise_Specialized.o 

CPP_DEPS += \
./Deprecated_FileCode/DEPSCALAR.d \
./Deprecated_FileCode/LAR_Indexing.d \
./Deprecated_FileCode/LAR_Pointwise_Specialized.d 


# Each subdirectory must supply rules for building sources it contributes
Deprecated_FileCode/%.o: ../Deprecated_FileCode/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -fopenmp -I/home/joseph/cuda-workspace/BlackCat_Tensors/BC_Headers -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


