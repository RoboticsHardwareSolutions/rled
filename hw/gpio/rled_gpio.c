#include "rled_gpio.h"
#include "../../wrappers/gpio/gpio.h"

void rled_gpio_init(const rled_gpio_config_t* config)
{
    // Assume GPIO is already configured as output elsewhere
}

void rled_gpio_on(const rled_gpio_config_t* config)
{
    gpio_write_pin(config->port, config->pin, 1u);
}

void rled_gpio_off(const rled_gpio_config_t* config)
{
    gpio_write_pin(config->port, config->pin, 0u);
}

void rled_gpio_toggle(const rled_gpio_config_t* config)
{
    gpio_toggle_pin(config->port, config->pin);
}
