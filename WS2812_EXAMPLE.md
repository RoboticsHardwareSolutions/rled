# WS2812 LED Driver Usage Example

This example demonstrates how to use the new WS2812 SPI implementation in the RLED driver.

## Basic Setup

```c
#include "rled.h"
#include "hw/ws2812/rled_ws2812.h"

// Example configuration for a WS2812 LED strip
rled_ws2812_config_t ws2812_config = {
    .hspi = &hspi1,           // SPI handle from STM32 HAL
    .port = GPIOA,            // GPIO port for data pin
    .pin = GPIO_PIN_7,        // MOSI pin (SPI data pin)
    .num_leds = 8             // Number of LEDs in strip
};

// LED handle for unified API
rled_t led = {
    .type = RLED_TYPE_WS2812,
    .config.ws2812 = ws2812_config
};

int main(void) {
    // Initialize the LED
    rled_init(&led);
    
    // Use unified API
    rled_on(&led);              // Turns on all LEDs white
    rled_off(&led);             // Turns off all LEDs
    rled_set_color(&led, 255, 0, 0);  // Set all LEDs to red
    
    return 0;
}
```

## Advanced Usage

For more control over individual LEDs, use the device-specific functions:

```c
#include "hw/ws2812/rled_ws2812.h"

int main(void) {
    // Device instance (global or static)
    static rled_ws2812_device_t ws2812_device;
    
    // Initialize with configuration
    rled_ws2812_init(&ws2812_device, &ws2812_config);
    
    // Set all LEDs to the same color
    rled_ws2812_set_all(&ws2812_device, 0, 255, 0);  // All green
    
    // Set individual LED colors
    rled_ws2812_set_led(&ws2812_device, 0, 255, 0, 0);    // LED 0: Red
    rled_ws2812_set_led(&ws2812_device, 1, 0, 255, 0);    // LED 1: Green
    rled_ws2812_set_led(&ws2812_device, 2, 0, 0, 255);    // LED 2: Blue
    
    // Set multiple LEDs with array
    uint8_t color_data[] = {
        255, 0, 0,    // LED 0: Red
        0, 255, 0,    // LED 1: Green
        0, 0, 255,    // LED 2: Blue
        255, 255, 0,  // LED 3: Yellow
        255, 0, 255,  // LED 4: Magenta
        0, 255, 255,  // LED 5: Cyan
        255, 255, 255 // LED 6: White
    };
    rled_ws2812_set_strip(&ws2812_device, color_data, 7);
    
    // Clear all LEDs
    rled_ws2812_clear(&ws2812_device);
    
    return 0;
}
```

## Color Patterns Example

```c
void rainbow_pattern(rled_ws2812_device_t* device, uint16_t num_leds) {
    for (int i = 0; i < num_leds; i++) {
        uint8_t r = (i * 255) / num_leds;
        uint8_t g = ((i * 2 * 255) / num_leds) % 255;
        uint8_t b = ((i * 3 * 255) / num_leds) % 255;
        
        rled_ws2812_set_led(device, i, r, g, b);
    }
}

void breathing_effect(rled_ws2812_device_t* device, uint16_t num_leds) {
    for (int brightness = 0; brightness <= 255; brightness += 5) {
        rled_ws2812_set_all(device, brightness, 0, 0);  // Red breathing
        HAL_Delay(50);  // Small delay for visible effect
    }
    for (int brightness = 255; brightness >= 0; brightness -= 5) {
        rled_ws2812_set_all(device, brightness, 0, 0);
        HAL_Delay(50);
    }
}
```

## SPI Configuration Notes

1. **SPI Frequency**: The WS2812 protocol requires specific timing. The current implementation uses:
   - `ONE_FRAME = 0xFF` for '1' bits
   - `ZERO_FRAME = 0xC0` for '0' bits
   - These values may need adjustment based on your SPI clock frequency

2. **Data Pin**: Uses SPI MOSI pin for data transmission

3. **Color Order**: WS2812 uses GRB (Green-Red-Blue) order internally

## Timing Requirements

- **Reset Delay**: 80μs minimum between frames (implemented)
- **SPI Clock**: Should be configured appropriately for bit encoding timing
- **Memory**: Buffer allocation is handled automatically based on LED count

## Error Handling

- All functions include null pointer checks
- Buffer allocation failure is handled gracefully
- Invalid LED indices are ignored

## Customization

To adjust timing constants, modify these defines in `rled_ws2812.c`:

```c
#define WS2812_ONE_FRAME  0xFF  // Pattern for '1' bit
#define WS2812_ZERO_FRAME 0xC0  // Pattern for '0' bit  
#define WS2812_RESET_DELAY_US 80  // Reset delay in microseconds
```

The exact values depend on your SPI clock speed and LED strip requirements. Consult the WS2812 datasheet for precise timing specifications.