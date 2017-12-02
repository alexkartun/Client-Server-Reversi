################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../client/Client.cpp \
../client/main.cpp 

OBJS += \
./client/Client.o \
./client/main.o 

CPP_DEPS += \
./client/Client.d \
./client/main.d 


# Each subdirectory must supply rules for building sources it contributes
client/%.o: ../client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


