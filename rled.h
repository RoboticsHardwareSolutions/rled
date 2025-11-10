#ifndef RLED_H
#define RLED_H

#include <stdint.h>

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
void rled_init(rled_t* led);
void rled_on(rled_t* led);
void rled_off(rled_t* led);
void rled_toggle(rled_t* led);                                      // Optional
void rled_set_brightness(rled_t* led, uint8_t brightness);          // For PWM
void rled_set_color(rled_t* led, uint8_t r, uint8_t g, uint8_t b);  // For RGB and WS2812

#endif  // RLED_H
