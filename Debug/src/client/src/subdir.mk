################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/client/src/Board.cpp \
../src/client/src/Client.cpp \
../src/client/src/Console.cpp \
../src/client/src/Cpu.cpp \
../src/client/src/Game.cpp \
../src/client/src/Logic.cpp \
../src/client/src/Move.cpp \
../src/client/src/User.cpp \
../src/client/src/main.cpp 

OBJS += \
./src/client/src/Board.o \
./src/client/src/Client.o \
./src/client/src/Console.o \
./src/client/src/Cpu.o \
./src/client/src/Game.o \
./src/client/src/Logic.o \
./src/client/src/Move.o \
./src/client/src/User.o \
./src/client/src/main.o 

CPP_DEPS += \
./src/client/src/Board.d \
./src/client/src/Client.d \
./src/client/src/Console.d \
./src/client/src/Cpu.d \
./src/client/src/Game.d \
./src/client/src/Logic.d \
./src/client/src/Move.d \
./src/client/src/User.d \
./src/client/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/client/src/%.o: ../src/client/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/GitProject/src/client/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


