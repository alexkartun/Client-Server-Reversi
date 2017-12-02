################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../client/test/gtest_main.cpp \
../client/test/test_board.cpp \
../client/test/test_game.cpp \
../client/test/test_logic.cpp 

OBJS += \
./client/test/gtest_main.o \
./client/test/test_board.o \
./client/test/test_game.o \
./client/test/test_logic.o 

CPP_DEPS += \
./client/test/gtest_main.d \
./client/test/test_board.d \
./client/test/test_game.d \
./client/test/test_logic.d 


# Each subdirectory must supply rules for building sources it contributes
client/test/%.o: ../client/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/GitProject/client/gtest_src" -I"/home/kartuna/workspace/GitProject/client/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


