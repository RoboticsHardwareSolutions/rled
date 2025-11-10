cmake_minimum_required(VERSION 3.24)
project(rled
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION "LED driver library for STM32")

set(RLED_SOURCES
    rled.c
    hw/gpio/rled_gpio.c
    hw/pwm/rled_pwm.c
    hw/rgb/rled_rgb.c
    hw/ws2812/rled_ws2812.c
    wrappers/gpio/gpio.c
    wrappers/tim/tim.c
    wrappers/spi/spi.c
)

set(RLED_HEADERS
    rled.h
    hw/gpio/rled_gpio.h
    hw/pwm/rled_pwm.h
    hw/rgb/rled_rgb.h
    hw/ws2812/rled_ws2812.h
    wrappers/gpio/gpio.h
    wrappers/tim/tim.h
    wrappers/spi/spi.h
)

add_library(${PROJECT_NAME} STATIC ${RLED_SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ./
    wrappers/
)

