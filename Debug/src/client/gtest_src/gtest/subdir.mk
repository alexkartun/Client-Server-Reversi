################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/client/gtest_src/gtest/gtest-all.cc 

CC_DEPS += \
./src/client/gtest_src/gtest/gtest-all.d 

OBJS += \
./src/client/gtest_src/gtest/gtest-all.o 


# Each subdirectory must supply rules for building sources it contributes
src/client/gtest_src/gtest/%.o: ../src/client/gtest_src/gtest/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/GitProject/src/client/gtest_src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


