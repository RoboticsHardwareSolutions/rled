#ifndef RLED_WS2812_H
#define RLED_WS2812_H

#include <stdint.h>
#include "../../rled.h"

// Configuration structure for WS2812 (unified config + state)
typedef struct rled_ws2812_config
{
    SPI_Handle hspi;
    GPIO_Port  port;
    GPIO_Pin   pin;            // Data pin (SPI MOSI)
    uint16_t   num_leds;
    uint8_t*   spi_buffer;     // External buffer for SPI transmission
    uint16_t   buffer_size;    // Size of external buffer
    uint8_t    one_frame;      // SPI pattern for '1' bit (WS2812_ONE_FRAME)
    uint8_t    zero_frame;     // SPI pattern for '0' bit (WS2812_ZERO_FRAME)
    uint32_t   reset_delay_us; // Reset delay in microseconds (WS2812_RESET_DELAY_US)
} rled_ws2812_config_t;

// Initialize WS2812 configuration
// Returns 0 on success, negative on error
int rled_ws2812_init(const rled_ws2812_config_t* config);

// Turn on all LEDs with specified color
int rled_ws2812_set_all(const rled_ws2812_config_t* config, uint8_t r, uint8_t g, uint8_t b);

// Turn off all LEDs
int rled_ws2812_clear(const rled_ws2812_config_t* config);

// Set color for first LED (for backward compatibility)
int rled_ws2812_set_color(const rled_ws2812_config_t* config, uint8_t r, uint8_t g, uint8_t b);

// Set color for specific LED (0-based index)
int rled_ws2812_set_led(const rled_ws2812_config_t* config, uint16_t led_index, uint8_t r, uint8_t g, uint8_t b);

// Set multiple LEDs with array of colors
int rled_ws2812_set_strip(const rled_ws2812_config_t* config, const uint8_t* colors, uint16_t num_leds);

#endif  // RLED_WS2812_H