# RLED Driver

This is a modular LED driver library for STM32 microcontrollers, providing a unified API for different types of LEDs.

## Architecture

The driver is structured in layers:

- **Application Level** (`rled.h`, `rled.c`): Unified API for controlling LEDs regardless of hardware type.
- **Hardware Abstraction** (`hw/`): Specific implementations for different LED types (GPIO, PWM, RGB, WS2812).
- **HAL Wrappers** (`wrappers/`): Thin wrappers around ST HAL APIs for GPIO, TIM, and SPI, providing opaque interfaces.

## Supported LED Types

1. **GPIO LED** (`RLED_TYPE_GPIO`): Simple on/off control via GPIO pin.
2. **PWM LED** (`RLED_TYPE_PWM`): Brightness control via PWM.
3. **RGB LED** (`RLED_TYPE_RGB`): Color control via PWM on three channels.
4. **WS2812 LED** (`RLED_TYPE_WS2812`): Addressable RGB LED via SPI (implementation pending).

## Usage

```c
#include "rled.h"

// Example for GPIO LED
rled_t led = {
    .type = RLED_TYPE_GPIO,
    .config.gpio = {
        .port = GPIOA,
        .pin = GPIO_PIN_5
    }
};

rled_init(&led);
rled_on(&led);
rled_off(&led);
```

## Building

Use CMake to build the library. It requires STM32 HAL libraries.

## Example

Find an usage example in [here](WS2812_EXAMPLE.md)
