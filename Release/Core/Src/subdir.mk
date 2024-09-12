################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bitmap_arrays.c \
../Core/Src/fatfs_sd.c \
../Core/Src/font8x8.c \
../Core/Src/gpio.c \
../Core/Src/spi.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7xx.c \
../Core/Src/tim.c 

CPP_SRCS += \
../Core/Src/display_ssd1963.cpp \
../Core/Src/draw_display.cpp \
../Core/Src/finish_state_machine.cpp \
../Core/Src/main.cpp \
../Core/Src/menu_parts.cpp \
../Core/Src/navigate_robot.cpp \
../Core/Src/objects.cpp \
../Core/Src/sd_card_service.cpp \
../Core/Src/servo.cpp \
../Core/Src/xpt2046.cpp 

C_DEPS += \
./Core/Src/bitmap_arrays.d \
./Core/Src/fatfs_sd.d \
./Core/Src/font8x8.d \
./Core/Src/gpio.d \
./Core/Src/spi.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7xx.d \
./Core/Src/tim.d 

OBJS += \
./Core/Src/bitmap_arrays.o \
./Core/Src/display_ssd1963.o \
./Core/Src/draw_display.o \
./Core/Src/fatfs_sd.o \
./Core/Src/finish_state_machine.o \
./Core/Src/font8x8.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/menu_parts.o \
./Core/Src/navigate_robot.o \
./Core/Src/objects.o \
./Core/Src/sd_card_service.o \
./Core/Src/servo.o \
./Core/Src/spi.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7xx.o \
./Core/Src/tim.o \
./Core/Src/xpt2046.o 

CPP_DEPS += \
./Core/Src/display_ssd1963.d \
./Core/Src/draw_display.d \
./Core/Src/finish_state_machine.d \
./Core/Src/main.d \
./Core/Src/menu_parts.d \
./Core/Src/navigate_robot.d \
./Core/Src/objects.d \
./Core/Src/sd_card_service.d \
./Core/Src/servo.d \
./Core/Src/xpt2046.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/bitmap_arrays.cyclo ./Core/Src/bitmap_arrays.d ./Core/Src/bitmap_arrays.o ./Core/Src/bitmap_arrays.su ./Core/Src/display_ssd1963.cyclo ./Core/Src/display_ssd1963.d ./Core/Src/display_ssd1963.o ./Core/Src/display_ssd1963.su ./Core/Src/draw_display.cyclo ./Core/Src/draw_display.d ./Core/Src/draw_display.o ./Core/Src/draw_display.su ./Core/Src/fatfs_sd.cyclo ./Core/Src/fatfs_sd.d ./Core/Src/fatfs_sd.o ./Core/Src/fatfs_sd.su ./Core/Src/finish_state_machine.cyclo ./Core/Src/finish_state_machine.d ./Core/Src/finish_state_machine.o ./Core/Src/finish_state_machine.su ./Core/Src/font8x8.cyclo ./Core/Src/font8x8.d ./Core/Src/font8x8.o ./Core/Src/font8x8.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/menu_parts.cyclo ./Core/Src/menu_parts.d ./Core/Src/menu_parts.o ./Core/Src/menu_parts.su ./Core/Src/navigate_robot.cyclo ./Core/Src/navigate_robot.d ./Core/Src/navigate_robot.o ./Core/Src/navigate_robot.su ./Core/Src/objects.cyclo ./Core/Src/objects.d ./Core/Src/objects.o ./Core/Src/objects.su ./Core/Src/sd_card_service.cyclo ./Core/Src/sd_card_service.d ./Core/Src/sd_card_service.o ./Core/Src/sd_card_service.su ./Core/Src/servo.cyclo ./Core/Src/servo.d ./Core/Src/servo.o ./Core/Src/servo.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7xx.cyclo ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/xpt2046.cyclo ./Core/Src/xpt2046.d ./Core/Src/xpt2046.o ./Core/Src/xpt2046.su

.PHONY: clean-Core-2f-Src

