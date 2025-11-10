#include "rled_ws2812.h"
#include "../../wrappers/spi/spi.h"
#include <string.h>

// WS2812 timing constants (typical values for 800kHz SPI)
#define WS2812_ONE_FRAME 0xFF     // 11111111 - for '1' bit
#define WS2812_ZERO_FRAME 0xC0    // 11000000 - for '0' bit (adjust based on timing)
#define WS2812_RESET_DELAY_US 80  // Minimum reset delay in microseconds
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
static void ws2812_reset_delay(void)
{
    // Simple delay implementation - replace with proper delay function
    for (volatile int i = 0; i < WS2812_RESET_DELAY_US * 10; i++)
        ;
}

// Helper function to transmit buffer data
static void ws2812_transmit_buffer(rled_ws2812_device_t* device)
{
    if (device && device->hspi && device->spi_buffer)
    {
        spi_transmit(device->hspi, device->spi_buffer, device->buffer_size, 1000);
        ws2812_reset_delay();
    }
}

void rled_ws2812_init(rled_ws2812_device_t* device, const rled_ws2812_config_t* config)
{
    if (!device || !config)
    {
        return;
    }

    device->hspi           = config->hspi;
    device->port           = config->port;
    device->pin            = config->pin;
    device->num_leds       = config->num_leds;
    device->one_frame      = WS2812_ONE_FRAME;
    device->zero_frame     = WS2812_ZERO_FRAME;
    device->reset_delay_us = WS2812_RESET_DELAY_US;

    // Use external buffer provided in config
    device->buffer_size = config->buffer_size;
    device->spi_buffer  = config->spi_buffer;

    if (!device->spi_buffer)
    {
        // Handle null buffer error
        return;
    }

    // Validate buffer size
    uint16_t required_size = CALC_BUFFER_SIZE(config->num_leds);
    if (device->buffer_size < required_size)
    {
        // Buffer too small
        return;
    }

    // Initialize all LEDs to off state
    memset(device->spi_buffer, 0, device->buffer_size);
}

void rled_ws2812_clear(rled_ws2812_device_t* device)
{
    if (!device || !device->spi_buffer)
    {
        return;
    }

    memset(device->spi_buffer, 0, device->buffer_size);

    // Send the cleared data to strip
    ws2812_transmit_buffer(device);
}

void rled_ws2812_set_all(rled_ws2812_device_t* device, uint8_t r, uint8_t g, uint8_t b)
{
    if (!device || !device->spi_buffer)
    {
        return;
    }

    uint8_t* buffer_ptr = device->spi_buffer;

    // Encode all LEDs with the same color
    for (uint16_t i = 0; i < device->num_leds; i++)
    {
        ws2812_encode_pixel(g, r, b, &buffer_ptr);
    }

    // Send the data to strip
    ws2812_transmit_buffer(device);
}

void rled_ws2812_set_color(rled_ws2812_device_t* device, uint8_t r, uint8_t g, uint8_t b)
{
    // For compatibility with existing rled.c - set first LED only
    rled_ws2812_set_led(device, 0, r, g, b);
}

void rled_ws2812_set_led(rled_ws2812_device_t* device, uint16_t led_index, uint8_t r, uint8_t g, uint8_t b)
{
    if (!device || !device->spi_buffer || led_index >= device->num_leds)
    {
        return;
    }

    // Encode only the specified LED
    uint8_t* buffer_ptr = device->spi_buffer + (led_index * COLORS_PER_PIXEL * BITS_PER_COLOR);

    // First, clear the target LED
    memset(buffer_ptr, 0, COLORS_PER_PIXEL * BITS_PER_COLOR);

    // Then encode the new color
    ws2812_encode_pixel(g, r, b, &buffer_ptr);

    // Send the data to strip
    ws2812_transmit_buffer(device);
}

void rled_ws2812_set_strip(rled_ws2812_device_t* device, const uint8_t* colors, uint16_t num_leds)
{
    if (!device || !device->spi_buffer || !colors)
    {
        return;
    }

    if (num_leds > device->num_leds)
    {
        num_leds = device->num_leds;  // Limit to available LEDs
    }

    uint8_t* buffer_ptr = device->spi_buffer;

    // Clear entire buffer first
    memset(device->spi_buffer, 0, device->buffer_size);

    // Encode all LEDs from the color array
    for (uint16_t i = 0; i < num_leds; i++)
    {
        uint8_t r = colors[i * 3 + 0];
        uint8_t g = colors[i * 3 + 1];
        uint8_t b = colors[i * 3 + 2];
        ws2812_encode_pixel(g, r, b, &buffer_ptr);
    }

    // Send the data to strip
    ws2812_transmit_buffer(device);
}
