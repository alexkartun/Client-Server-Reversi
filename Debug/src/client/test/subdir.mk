################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/client/test/gtest_main.cpp \
../src/client/test/test_board.cpp \
../src/client/test/test_game.cpp \
../src/client/test/test_logic.cpp \
../src/client/test/test_user.cpp 

OBJS += \
./src/client/test/gtest_main.o \
./src/client/test/test_board.o \
./src/client/test/test_game.o \
./src/client/test/test_logic.o \
./src/client/test/test_user.o 

CPP_DEPS += \
./src/client/test/gtest_main.d \
./src/client/test/test_board.d \
./src/client/test/test_game.d \
./src/client/test/test_logic.d \
./src/client/test/test_user.d 


# Each subdirectory must supply rules for building sources it contributes
src/client/test/%.o: ../src/client/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/GitProject/src/client/include" -I"/home/kartuna/workspace/GitProject/src/client/gtest_src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


