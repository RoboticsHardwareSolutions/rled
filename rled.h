#ifndef RLED_H
#define RLED_H

#include <stdint.h>

// Error codes
typedef enum
{
    RLED_OK                = 0,
    RLED_ERR_NULL_POINTER  = -1,
    RLED_ERR_INVALID_TYPE  = -2,
    RLED_ERR_INIT_FAILED   = -3,
    RLED_ERR_INVALID_PARAM = -4,
    RLED_ERR_PATTERN_BUSY  = -5
} rled_error_t;

// Forward declarations for hardware config structs
typedef struct rled_gpio_config   rled_gpio_config_t;
typedef struct rled_pwm_config    rled_pwm_config_t;
typedef struct rled_rgb_config    rled_rgb_config_t;
typedef struct rled_ws2812_config rled_ws2812_config_t;

// LED types
typedef enum
{
    RLED_TYPE_GPIO,   // Regular LED with GPIO
    RLED_TYPE_PWM,    // LED with PWM for brightness
    RLED_TYPE_RGB,    // RGB LED with GPIO/PWM
    RLED_TYPE_WS2812  // Addressable RGB LED (WS2812)
} rled_type_t;

// Opaque types for hardware handles
typedef void*    GPIO_Port;
typedef void*    TIM_Handle;
typedef void*    SPI_Handle;
typedef uint16_t GPIO_Pin;
typedef uint32_t TIM_Channel;

// Union for configurations (using void* for abstraction)
typedef union
{
    void* gpio;    // Points to rled_gpio_config_t
    void* pwm;     // Points to rled_pwm_config_t
    void* rgb;     // Points to rled_rgb_config_t
    void* ws2812;  // Points to rled_ws2812_config_t
} rled_config_u;

// Main LED structure
typedef struct
{
    rled_type_t   type;
    rled_config_u config;
} rled_t;

// Application level APIs
// Returns RLED_OK on success, error code on failure
int rled_init(rled_t* led);
int rled_on(rled_t* led);
int rled_off(rled_t* led);
int rled_toggle(rled_t* led);
int rled_set_brightness(rled_t* led, uint8_t brightness);
int rled_set_color(rled_t* led, uint8_t r, uint8_t g, uint8_t b);

// Include hardware-specific config definitions
#include "hw/gpio/rled_gpio.h"
#include "hw/pwm/rled_pwm.h"
#include "hw/rgb/rled_rgb.h"
#include "hw/ws2812/rled_ws2812.h"

#endif  // RLED_H
