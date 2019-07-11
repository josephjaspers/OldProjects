################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include RunTimeTest/DEPFILES/UNSIGNDEF_DEFS/subdir.mk
-include RunTimeTest/DEPFILES/subdir.mk
-include RunTimeTest/BC_Vector_impl/subdir.mk
-include RunTimeTest/BC_Tensor_impl/subdir.mk
-include RunTimeTest/BC_Scalar_impl/subdir.mk
-include RunTimeTest/BC_LAR_impl/subdir.mk
-include RunTimeTest/BC_LAR_GPU_impl/FLOAT_DEFS/subdir.mk
-include RunTimeTest/BC_LAR_GPU_impl/subdir.mk
-include Release_tmp/DEPFILES/UNSIGNDEF_DEFS/subdir.mk
-include Release_tmp/DEPFILES/subdir.mk
-include Release_tmp/BC_Vector_impl/subdir.mk
-include Release_tmp/BC_Tensor_impl/subdir.mk
-include Release_tmp/BC_Scalar_impl/subdir.mk
-include Release_tmp/BC_LAR_impl/subdir.mk
-include Release_tmp/BC_LAR_GPU_impl/FLOAT_DEFS/subdir.mk
-include Release_tmp/BC_LAR_GPU_impl/subdir.mk
-include Deprecated_FileCode/subdir.mk
-include BC_Vector_impl/subdir.mk
-include BC_Tensor_impl/subdir.mk
-include BC_Scalar_impl/subdir.mk
-include BC_LAR_impl/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libBlackCat_Tensors.a

# Tool invocations
libBlackCat_Tensors.a: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Archiver'
	ar -r  "libBlackCat_Tensors.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(ARCHIVES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) libBlackCat_Tensors.a
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
