#include "rled_pwm.h"
#include "../../wrappers/tim/tim.h"

int rled_pwm_init(const rled_pwm_config_t* config)
{
    if (!config || !config->htim)
    {
        return -1;
    }
    // Assume TIM is configured and started elsewhere
    tim_pwm_start(config->htim, config->channel);
    return 0;
}

int rled_pwm_on(const rled_pwm_config_t* config)
{
    if (!config || !config->htim)
    {
        return -1;
    }
    tim_set_compare(config->htim, config->channel, 255);  // Assuming period is 255
    return 0;
}

int rled_pwm_off(const rled_pwm_config_t* config)
{
    if (!config || !config->htim)
    {
        return -1;
    }
    tim_set_compare(config->htim, config->channel, 0);
    return 0;
}

int rled_pwm_set_brightness(const rled_pwm_config_t* config, uint8_t brightness)
{
    if (!config || !config->htim)
    {
        return -1;
    }
    tim_set_compare(config->htim, config->channel, brightness);  // Assuming period is 255
    return 0;
}