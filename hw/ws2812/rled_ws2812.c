#include "rled_ws2812.h"
#include "../../wrappers/spi/spi.h"
#include <string.h>

// WS2812 timing constants (for 4 MHz SPI)
#define WS2812_ONE_FRAME 0xE0      // 01110000 - for '1' bit
#define WS2812_ZERO_FRAME 0xC0     // 00110000 - for '0' bit (adjust based on timing)
#define WS2812_RESET_DELAY_US 300  // Minimum reset delay in microseconds
#define BITS_PER_COLOR 8
#define COLORS_PER_PIXEL 3  // G, R, B order for WS2812

// Internal buffer size calculation
#define CALC_BUFFER_SIZE(num_leds) ((num_leds) * COLORS_PER_PIXEL * BITS_PER_COLOR)

// Encode a single color byte (8 bits) into SPI buffer
static void ws2812_encode_byte(uint8_t color, uint8_t** buffer)
{
    for (int i = 7; i >= 0; i--)
    {
        uint8_t bit_value = (color >> i) & 0x01;
        if (bit_value)
        {
            *(*buffer)++ = WS2812_ONE_FRAME;
        }
        else
        {
            *(*buffer)++ = WS2812_ZERO_FRAME;
        }
    }
}

// Encode a single RGB pixel in GRB order
static void ws2812_encode_pixel(uint8_t g, uint8_t r, uint8_t b, uint8_t** buffer)
{
    ws2812_encode_byte(g, buffer);  // Green first
    ws2812_encode_byte(r, buffer);  // Red second
    ws2812_encode_byte(b, buffer);  // Blue third
}

// Reset delay function (simple delay)
static void ws2812_reset_delay(const rled_ws2812_config_t* config)
{
    // Simple delay implementation - replace with proper delay function
    // for (volatile int i = 0; i < config->reset_delay_us * 10; i++)
    // ;
    spi_delay(config->hspi);
}

// Helper function to transmit buffer data
static int ws2812_transmit_buffer(const rled_ws2812_config_t* config)
{
    if (!config || !config->hspi || !config->spi_buffer)
    {
        return -1;
    }
    spi_transmit(config->hspi, config->spi_buffer, config->buffer_size, 1000);
    ws2812_reset_delay(config);
    return 0;
}

int rled_ws2812_init(const rled_ws2812_config_t* config)
{
    if (!config)
    {
        return -1;
    }

    if (!config->spi_buffer)
    {
        // Handle null buffer error
        return -3;
    }

    // Validate buffer size
    uint16_t required_size = CALC_BUFFER_SIZE(config->num_leds);
    if (config->buffer_size < required_size)
    {
        // Buffer too small
        return -4;
    }

    // Initialize all LEDs to off state
    memset(config->spi_buffer, 0, config->buffer_size);
    return 0;
}

int rled_ws2812_clear(const rled_ws2812_config_t* config)
{
    if (!config || !config->spi_buffer)
    {
        return -1;
    }

    memset(config->spi_buffer, 0, config->buffer_size);

    // Send the cleared data to strip
    return ws2812_transmit_buffer(config);
}

int rled_ws2812_set_all(const rled_ws2812_config_t* config, uint8_t r, uint8_t g, uint8_t b)
{
    if (!config || !config->spi_buffer)
    {
        return -1;
    }

    uint8_t* buffer_ptr = config->spi_buffer;

    // Encode all LEDs with the same color
    for (uint16_t i = 0; i < config->num_leds; i++)
    {
        ws2812_encode_pixel(g, r, b, &buffer_ptr);
    }

    // Send the data to strip
    return ws2812_transmit_buffer(config);
}

int rled_ws2812_set_color(const rled_ws2812_config_t* config, uint8_t r, uint8_t g, uint8_t b)
{
    // For compatibility with existing rled.c - set first LED only
    return rled_ws2812_set_led(config, 0, r, g, b);
}

int rled_ws2812_set_led(const rled_ws2812_config_t* config, uint16_t led_index, uint8_t r, uint8_t g, uint8_t b)
{
    if (!config || !config->spi_buffer || led_index >= config->num_leds)
    {
        return -1;
    }

    // Validate buffer bounds before pointer arithmetic
    uint16_t led_offset = led_index * COLORS_PER_PIXEL * BITS_PER_COLOR;
    if (led_offset + (COLORS_PER_PIXEL * BITS_PER_COLOR) > config->buffer_size)
    {
        return -4;  // Buffer overflow protection
    }

    // Encode only the specified LED
    uint8_t* buffer_ptr = config->spi_buffer + led_offset;

    // First, clear the target LED
    memset(buffer_ptr, 0, COLORS_PER_PIXEL * BITS_PER_COLOR);

    // Then encode the new color
    ws2812_encode_pixel(g, r, b, &buffer_ptr);

    // Send the data to strip
    return ws2812_transmit_buffer(config);
}

int rled_ws2812_set_strip(const rled_ws2812_config_t* config, const uint8_t* colors, uint16_t num_leds)
{
    if (!config || !config->spi_buffer || !colors)
    {
        return -1;
    }

    if (num_leds > config->num_leds)
    {
        num_leds = config->num_leds;  // Limit to available LEDs
    }

    uint8_t* buffer_ptr = config->spi_buffer;

    // Clear entire buffer first
    memset(config->spi_buffer, 0, config->buffer_size);

    // Encode all LEDs from the color array
    for (uint16_t i = 0; i < num_leds; i++)
    {
        uint8_t r = colors[i * 3 + 0];
        uint8_t g = colors[i * 3 + 1];
        uint8_t b = colors[i * 3 + 2];
        ws2812_encode_pixel(g, r, b, &buffer_ptr);
    }

    // Send the data to strip
    return ws2812_transmit_buffer(config);
}