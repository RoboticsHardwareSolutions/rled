#include "rled_gpio.h"
#include "../../wrappers/gpio/gpio.h"

int rled_gpio_init(const rled_gpio_config_t* config)
{
    if (!config)
    {
        return -1;  // RLED_ERR_NULL_POINTER
    }
    // Assume GPIO is already configured as output elsewhere
    return 0;
}

int rled_gpio_on(const rled_gpio_config_t* config)
{
    if (!config || !config->port)
    {
        return -1;
    }
    gpio_write_pin(config->port, config->pin, 1u);
    return 0;
}

int rled_gpio_off(const rled_gpio_config_t* config)
{
    if (!config || !config->port)
    {
        return -1;
    }
    gpio_write_pin(config->port, config->pin, 0u);
    return 0;
}

int rled_gpio_toggle(const rled_gpio_config_t* config)
{
    if (!config || !config->port)
    {
        return -1;
    }
    gpio_toggle_pin(config->port, config->pin);
    return 0;
}