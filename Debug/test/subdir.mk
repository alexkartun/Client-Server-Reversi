################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/gtest_main.cpp \
../test/test_board.cpp \
../test/test_game.cpp \
../test/test_player.cpp 

OBJS += \
./test/gtest_main.o \
./test/test_board.o \
./test/test_game.o \
./test/test_player.o 

CPP_DEPS += \
./test/gtest_main.d \
./test/test_board.d \
./test/test_game.d \
./test/test_player.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/kartuna/workspace/GitProject/gtest_src" -I"/home/kartuna/workspace/GitProject/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


