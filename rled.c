#include "rled.h"
#include "hw/gpio/rled_gpio.h"
#include "hw/pwm/rled_pwm.h"
#include "hw/rgb/rled_rgb.h"
#include "hw/ws2812/rled_ws2812.h"

int rled_init(rled_t* led)
{
    if (!led)
    {
        return RLED_ERR_NULL_POINTER;
    }

    int result = RLED_OK;

    switch (led->type)
    {
    case RLED_TYPE_GPIO:
        result = rled_gpio_init(led->config.gpio);
        break;
    case RLED_TYPE_PWM:
        result = rled_pwm_init(led->config.pwm);
        break;
    case RLED_TYPE_RGB:
        result = rled_rgb_init(led->config.rgb);
        break;
    case RLED_TYPE_WS2812:
        result = rled_ws2812_init(led->config.ws2812);
        break;
    default:
        return RLED_ERR_INVALID_TYPE;
    }

    return result;
}

int rled_on(rled_t* led)
{
    if (!led)
    {
        return RLED_ERR_NULL_POINTER;
    }

    int result = RLED_OK;

    switch (led->type)
    {
    case RLED_TYPE_GPIO:
        result = rled_gpio_on(led->config.gpio);
        break;
    case RLED_TYPE_PWM:
        result = rled_pwm_on(led->config.pwm);
        break;
    case RLED_TYPE_RGB:
        result = rled_rgb_on(led->config.rgb);
        break;
    case RLED_TYPE_WS2812:
        // For WS2812, turn on with white color (full brightness)
        result = rled_ws2812_set_all(led->config.ws2812, 255, 255, 255);
        break;
    default:
        return RLED_ERR_INVALID_TYPE;
    }

    return result;
}

int rled_off(rled_t* led)
{
    if (!led)
    {
        return RLED_ERR_NULL_POINTER;
    }

    int result = RLED_OK;

    switch (led->type)
    {
    case RLED_TYPE_GPIO:
        result = rled_gpio_off(led->config.gpio);
        break;
    case RLED_TYPE_PWM:
        result = rled_pwm_off(led->config.pwm);
        break;
    case RLED_TYPE_RGB:
        result = rled_rgb_off(led->config.rgb);
        break;
    case RLED_TYPE_WS2812:
        result = rled_ws2812_clear(led->config.ws2812);
        break;
    default:
        return RLED_ERR_INVALID_TYPE;
    }

    return result;
}

int rled_toggle(rled_t* led)
{
    if (!led)
    {
        return RLED_ERR_NULL_POINTER;
    }

    switch (led->type)
    {
    case RLED_TYPE_GPIO:
        return rled_gpio_toggle(led->config.gpio);
    default:
        // Toggle only supported for GPIO
        return RLED_ERR_INVALID_TYPE;
    }
}

int rled_set_brightness(rled_t* led, uint8_t brightness)
{
    if (!led)
    {
        return RLED_ERR_NULL_POINTER;
    }

    switch (led->type)
    {
    case RLED_TYPE_PWM:
        return rled_pwm_set_brightness(led->config.pwm, brightness);
    default:
        // Set brightness only supported for PWM
        return RLED_ERR_INVALID_TYPE;
    }
}

int rled_set_color(rled_t* led, uint8_t r, uint8_t g, uint8_t b)
{
    if (!led)
    {
        return RLED_ERR_NULL_POINTER;
    }

    int result = RLED_OK;

    switch (led->type)
    {
    case RLED_TYPE_RGB:
        result = rled_rgb_set_color(led->config.rgb, r, g, b);
        break;
    case RLED_TYPE_WS2812:
        result = rled_ws2812_set_all(led->config.ws2812, r, g, b);
        break;
    default:
        return RLED_ERR_INVALID_TYPE;
    }

    return result;
}
