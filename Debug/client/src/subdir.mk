################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../client/src/Board.cpp \
../client/src/Client.cpp \
../client/src/Console.cpp \
../client/src/Cpu.cpp \
../client/src/Game.cpp \
../client/src/Logic.cpp \
../client/src/Move.cpp \
../client/src/User.cpp \
../client/src/main.cpp 

OBJS += \
./client/src/Board.o \
./client/src/Client.o \
./client/src/Console.o \
./client/src/Cpu.o \
./client/src/Game.o \
./client/src/Logic.o \
./client/src/Move.o \
./client/src/User.o \
./client/src/main.o 

CPP_DEPS += \
./client/src/Board.d \
./client/src/Client.d \
./client/src/Console.d \
./client/src/Cpu.d \
./client/src/Game.d \
./client/src/Logic.d \
./client/src/Move.d \
./client/src/User.d \
./client/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
client/src/%.o: ../client/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/GitProject/client/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


