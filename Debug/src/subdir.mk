################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Board.cpp \
../src/Console.cpp \
../src/Cpu.cpp \
../src/Game.cpp \
../src/Logic.cpp \
../src/User.cpp \
../src/main.cpp 

OBJS += \
./src/Board.o \
./src/Console.o \
./src/Cpu.o \
./src/Game.o \
./src/Logic.o \
./src/User.o \
./src/main.o 

CPP_DEPS += \
./src/Board.d \
./src/Console.d \
./src/Cpu.d \
./src/Game.d \
./src/Logic.d \
./src/User.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/GitProject/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


