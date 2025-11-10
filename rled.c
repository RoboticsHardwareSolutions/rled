#include "rled.h"
#include "hw/gpio/rled_gpio.h"
#include "hw/pwm/rled_pwm.h"
#include "hw/rgb/rled_rgb.h"
#include "hw/ws2812/rled_ws2812.h"

// Device instance for WS2812 (would typically be managed by application)
static rled_ws2812_device_t ws2812_device;

void rled_init(rled_t* led)
{
    switch (led->type)
    {
    case RLED_TYPE_GPIO:
        rled_gpio_init(led->config.gpio);
        break;
    case RLED_TYPE_PWM:
        rled_pwm_init(led->config.pwm);
        break;
    case RLED_TYPE_RGB:
        rled_rgb_init(led->config.rgb);
        break;
    case RLED_TYPE_WS2812:
        rled_ws2812_init(&ws2812_device, led->config.ws2812);
        break;
    default:
        // Error handling
        break;
    }
}

void rled_on(rled_t* led)
{
    switch (led->type)
    {
    case RLED_TYPE_GPIO:
        rled_gpio_on(led->config.gpio);
        break;
    case RLED_TYPE_PWM:
        rled_pwm_on(led->config.pwm);
        break;
    case RLED_TYPE_RGB:
        rled_rgb_on(led->config.rgb);
        break;
    case RLED_TYPE_WS2812:
        // For WS2812, turn on with white color (full brightness)
        rled_ws2812_set_all(&ws2812_device, 255, 255, 255);
        break;
    default:
        break;
    }
}

void rled_off(rled_t* led)
{
    switch (led->type)
    {
    case RLED_TYPE_GPIO:
        rled_gpio_off(led->config.gpio);
        break;
    case RLED_TYPE_PWM:
        rled_pwm_off(led->config.pwm);
        break;
    case RLED_TYPE_RGB:
        rled_rgb_off(led->config.rgb);
        break;
    case RLED_TYPE_WS2812:
        rled_ws2812_clear(&ws2812_device);
        break;
    default:
        break;
    }
}

void rled_toggle(rled_t* led)
{
    switch (led->type)
    {
    case RLED_TYPE_GPIO:
        rled_gpio_toggle(led->config.gpio);
        break;
    // For others, maybe not applicable, or implement if needed
    default:
        break;
    }
}

void rled_set_brightness(rled_t* led, uint8_t brightness)
{
    switch (led->type)
    {
    case RLED_TYPE_PWM:
        rled_pwm_set_brightness(led->config.pwm, brightness);
        break;
    // For others, not applicable
    default:
        break;
    }
}

void rled_set_color(rled_t* led, uint8_t r, uint8_t g, uint8_t b)
{
    switch (led->type)
    {
    case RLED_TYPE_RGB:
        rled_rgb_set_color(led->config.rgb, r, g, b);
        break;
    case RLED_TYPE_WS2812:
        rled_ws2812_set_all(&ws2812_device, r, g, b);
        break;
    default:
        break;
    }
}
