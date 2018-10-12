################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/ControladorPainel.cpp \
../Sources/ControladorPainel2.cpp \
../Sources/DecoderBCDAscii.cpp \
../Sources/DecoderBCDAscii2.cpp \
../Sources/DecoderBCDString.cpp \
../Sources/DecoderBCDString2.cpp \
../Sources/LCD.cpp \
../Sources/main.cpp \
../Sources/mkl_I2C.cpp \
../Sources/mkl_I2CPort.cpp \
../Sources/mkl_LCD.cpp 

OBJS += \
./Sources/ControladorPainel.o \
./Sources/ControladorPainel2.o \
./Sources/DecoderBCDAscii.o \
./Sources/DecoderBCDAscii2.o \
./Sources/DecoderBCDString.o \
./Sources/DecoderBCDString2.o \
./Sources/LCD.o \
./Sources/main.o \
./Sources/mkl_I2C.o \
./Sources/mkl_I2CPort.o \
./Sources/mkl_LCD.o 

CPP_DEPS += \
./Sources/ControladorPainel.d \
./Sources/ControladorPainel2.d \
./Sources/DecoderBCDAscii.d \
./Sources/DecoderBCDAscii2.d \
./Sources/DecoderBCDString.d \
./Sources/DecoderBCDString2.d \
./Sources/LCD.d \
./Sources/main.d \
./Sources/mkl_I2C.d \
./Sources/mkl_I2CPort.d \
./Sources/mkl_LCD.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


