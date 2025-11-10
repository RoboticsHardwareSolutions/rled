#ifndef RLED_GPIO_H
#define RLED_GPIO_H

#include <stdint.h>

// Configuration structure for GPIO LED
typedef struct
{
    void*    port;
    uint16_t pin;
} rled_gpio_config_t;

void rled_gpio_init(const rled_gpio_config_t* config);
void rled_gpio_on(const rled_gpio_config_t* config);
void rled_gpio_off(const rled_gpio_config_t* config);
void rled_gpio_toggle(const rled_gpio_config_t* config);

#endif  // RLED_GPIO_H
