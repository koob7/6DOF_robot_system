################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../fonts/src/008_Open_Sans_Bold.cpp \
../fonts/src/009_Open_Sans_Bold.cpp \
../fonts/src/010_Open_Sans_Bold.cpp \
../fonts/src/011_Open_Sans_Bold.cpp \
../fonts/src/012_Open_Sans_Bold.cpp \
../fonts/src/014_Open_Sans_Bold.cpp \
../fonts/src/016_Open_Sans_Bold.cpp \
../fonts/src/018_Open_Sans_Bold.cpp \
../fonts/src/020_Open_Sans_Bold.cpp \
../fonts/src/022_Open_Sans_Bold.cpp \
../fonts/src/024_Open_Sans_Bold.cpp \
../fonts/src/026_Open_Sans_Bold.cpp \
../fonts/src/028_Open_Sans_Bold.cpp \
../fonts/src/036_Open_Sans_Bold.cpp \
../fonts/src/048_Open_Sans_Bold.cpp \
../fonts/src/072_Open_Sans_Bold.cpp \
../fonts/src/096_Open_Sans_Bold.cpp \
../fonts/src/112_Open_Sans_Bold.cpp \
../fonts/src/128_Open_Sans_Bold.cpp 

OBJS += \
./fonts/src/008_Open_Sans_Bold.o \
./fonts/src/009_Open_Sans_Bold.o \
./fonts/src/010_Open_Sans_Bold.o \
./fonts/src/011_Open_Sans_Bold.o \
./fonts/src/012_Open_Sans_Bold.o \
./fonts/src/014_Open_Sans_Bold.o \
./fonts/src/016_Open_Sans_Bold.o \
./fonts/src/018_Open_Sans_Bold.o \
./fonts/src/020_Open_Sans_Bold.o \
./fonts/src/022_Open_Sans_Bold.o \
./fonts/src/024_Open_Sans_Bold.o \
./fonts/src/026_Open_Sans_Bold.o \
./fonts/src/028_Open_Sans_Bold.o \
./fonts/src/036_Open_Sans_Bold.o \
./fonts/src/048_Open_Sans_Bold.o \
./fonts/src/072_Open_Sans_Bold.o \
./fonts/src/096_Open_Sans_Bold.o \
./fonts/src/112_Open_Sans_Bold.o \
./fonts/src/128_Open_Sans_Bold.o 

CPP_DEPS += \
./fonts/src/008_Open_Sans_Bold.d \
./fonts/src/009_Open_Sans_Bold.d \
./fonts/src/010_Open_Sans_Bold.d \
./fonts/src/011_Open_Sans_Bold.d \
./fonts/src/012_Open_Sans_Bold.d \
./fonts/src/014_Open_Sans_Bold.d \
./fonts/src/016_Open_Sans_Bold.d \
./fonts/src/018_Open_Sans_Bold.d \
./fonts/src/020_Open_Sans_Bold.d \
./fonts/src/022_Open_Sans_Bold.d \
./fonts/src/024_Open_Sans_Bold.d \
./fonts/src/026_Open_Sans_Bold.d \
./fonts/src/028_Open_Sans_Bold.d \
./fonts/src/036_Open_Sans_Bold.d \
./fonts/src/048_Open_Sans_Bold.d \
./fonts/src/072_Open_Sans_Bold.d \
./fonts/src/096_Open_Sans_Bold.d \
./fonts/src/112_Open_Sans_Bold.d \
./fonts/src/128_Open_Sans_Bold.d 


# Each subdirectory must supply rules for building sources it contributes
fonts/src/%.o fonts/src/%.su fonts/src/%.cyclo: ../fonts/src/%.cpp fonts/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/kobie/STM32CubeIDE/workspace_1.13.2/6DOF_robot_system/fonts/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-fonts-2f-src

clean-fonts-2f-src:
	-$(RM) ./fonts/src/008_Open_Sans_Bold.cyclo ./fonts/src/008_Open_Sans_Bold.d ./fonts/src/008_Open_Sans_Bold.o ./fonts/src/008_Open_Sans_Bold.su ./fonts/src/009_Open_Sans_Bold.cyclo ./fonts/src/009_Open_Sans_Bold.d ./fonts/src/009_Open_Sans_Bold.o ./fonts/src/009_Open_Sans_Bold.su ./fonts/src/010_Open_Sans_Bold.cyclo ./fonts/src/010_Open_Sans_Bold.d ./fonts/src/010_Open_Sans_Bold.o ./fonts/src/010_Open_Sans_Bold.su ./fonts/src/011_Open_Sans_Bold.cyclo ./fonts/src/011_Open_Sans_Bold.d ./fonts/src/011_Open_Sans_Bold.o ./fonts/src/011_Open_Sans_Bold.su ./fonts/src/012_Open_Sans_Bold.cyclo ./fonts/src/012_Open_Sans_Bold.d ./fonts/src/012_Open_Sans_Bold.o ./fonts/src/012_Open_Sans_Bold.su ./fonts/src/014_Open_Sans_Bold.cyclo ./fonts/src/014_Open_Sans_Bold.d ./fonts/src/014_Open_Sans_Bold.o ./fonts/src/014_Open_Sans_Bold.su ./fonts/src/016_Open_Sans_Bold.cyclo ./fonts/src/016_Open_Sans_Bold.d ./fonts/src/016_Open_Sans_Bold.o ./fonts/src/016_Open_Sans_Bold.su ./fonts/src/018_Open_Sans_Bold.cyclo ./fonts/src/018_Open_Sans_Bold.d ./fonts/src/018_Open_Sans_Bold.o ./fonts/src/018_Open_Sans_Bold.su ./fonts/src/020_Open_Sans_Bold.cyclo ./fonts/src/020_Open_Sans_Bold.d ./fonts/src/020_Open_Sans_Bold.o ./fonts/src/020_Open_Sans_Bold.su ./fonts/src/022_Open_Sans_Bold.cyclo ./fonts/src/022_Open_Sans_Bold.d ./fonts/src/022_Open_Sans_Bold.o ./fonts/src/022_Open_Sans_Bold.su ./fonts/src/024_Open_Sans_Bold.cyclo ./fonts/src/024_Open_Sans_Bold.d ./fonts/src/024_Open_Sans_Bold.o ./fonts/src/024_Open_Sans_Bold.su ./fonts/src/026_Open_Sans_Bold.cyclo ./fonts/src/026_Open_Sans_Bold.d ./fonts/src/026_Open_Sans_Bold.o ./fonts/src/026_Open_Sans_Bold.su ./fonts/src/028_Open_Sans_Bold.cyclo ./fonts/src/028_Open_Sans_Bold.d ./fonts/src/028_Open_Sans_Bold.o ./fonts/src/028_Open_Sans_Bold.su ./fonts/src/036_Open_Sans_Bold.cyclo ./fonts/src/036_Open_Sans_Bold.d ./fonts/src/036_Open_Sans_Bold.o ./fonts/src/036_Open_Sans_Bold.su ./fonts/src/048_Open_Sans_Bold.cyclo ./fonts/src/048_Open_Sans_Bold.d ./fonts/src/048_Open_Sans_Bold.o ./fonts/src/048_Open_Sans_Bold.su ./fonts/src/072_Open_Sans_Bold.cyclo ./fonts/src/072_Open_Sans_Bold.d ./fonts/src/072_Open_Sans_Bold.o ./fonts/src/072_Open_Sans_Bold.su ./fonts/src/096_Open_Sans_Bold.cyclo ./fonts/src/096_Open_Sans_Bold.d ./fonts/src/096_Open_Sans_Bold.o ./fonts/src/096_Open_Sans_Bold.su ./fonts/src/112_Open_Sans_Bold.cyclo ./fonts/src/112_Open_Sans_Bold.d ./fonts/src/112_Open_Sans_Bold.o ./fonts/src/112_Open_Sans_Bold.su ./fonts/src/128_Open_Sans_Bold.cyclo ./fonts/src/128_Open_Sans_Bold.d ./fonts/src/128_Open_Sans_Bold.o ./fonts/src/128_Open_Sans_Bold.su

.PHONY: clean-fonts-2f-src

