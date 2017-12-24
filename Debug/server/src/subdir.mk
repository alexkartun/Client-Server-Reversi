################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../server/src/Server.cpp \
../server/src/main.cpp 

OBJS += \
./server/src/Server.o \
./server/src/main.o 

CPP_DEPS += \
./server/src/Server.d \
./server/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
server/src/%.o: ../server/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/GitProject/server/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


