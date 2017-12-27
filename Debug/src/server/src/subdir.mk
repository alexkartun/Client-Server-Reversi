################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/server/src/CommandsManager.cpp \
../src/server/src/Server.cpp \
../src/server/src/main.cpp 

OBJS += \
./src/server/src/CommandsManager.o \
./src/server/src/Server.o \
./src/server/src/main.o 

CPP_DEPS += \
./src/server/src/CommandsManager.d \
./src/server/src/Server.d \
./src/server/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/server/src/%.o: ../src/server/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/Git/src/server/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


