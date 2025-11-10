#ifndef RLED_WS2812_H
#define RLED_WS2812_H

#include <stdint.h>
#include "../../rled.h"

// Configuration structure for WS2812 initialization
typedef struct
{
    SPI_Handle hspi;
    GPIO_Port  port;
    GPIO_Pin   pin;  // Data pin (SPI MOSI)
    uint16_t   num_leds;
    uint8_t*   spi_buffer;   // External buffer for SPI transmission
    uint16_t   buffer_size;  // Size of external buffer
} rled_ws2812_config_t;

// Device structure for WS2812 internal state
typedef struct
{
    SPI_Handle hspi;
    GPIO_Port  port;
    GPIO_Pin   pin;  // Data pin (SPI MOSI)
    uint16_t   num_leds;
    uint8_t*   spi_buffer;      // External buffer for SPI transmission
    uint16_t   buffer_size;     // Size of external buffer
    uint8_t    one_frame;       // SPI pattern for '1' bit
    uint8_t    zero_frame;      // SPI pattern for '0' bit
    uint32_t   reset_delay_us;  // Reset delay in microseconds
} rled_ws2812_device_t;

// Initialize WS2812 device
void rled_ws2812_init(rled_ws2812_device_t* device, const rled_ws2812_config_t* config);

// Turn on all LEDs with specified color
void rled_ws2812_set_all(rled_ws2812_device_t* device, uint8_t r, uint8_t g, uint8_t b);

// Turn off all LEDs
void rled_ws2812_clear(rled_ws2812_device_t* device);

// Set color for first LED (for backward compatibility)
void rled_ws2812_set_color(rled_ws2812_device_t* device, uint8_t r, uint8_t g, uint8_t b);

// Set color for specific LED (0-based index)
void rled_ws2812_set_led(rled_ws2812_device_t* device, uint16_t led_index, uint8_t r, uint8_t g, uint8_t b);

// Set multiple LEDs with array of colors
void rled_ws2812_set_strip(rled_ws2812_device_t* device, const uint8_t* colors, uint16_t num_leds);

#endif  // RLED_WS2812_H
