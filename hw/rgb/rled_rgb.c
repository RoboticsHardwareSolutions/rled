#include "rled_rgb.h"
#include "../../wrappers/tim/tim.h"

int rled_rgb_init(const rled_rgb_config_t* config)
{
    if (!config || !config->htim_r || !config->htim_g || !config->htim_b)
    {
        return -1;
    }
    // Assume TIMs are configured and started elsewhere
    tim_pwm_start(config->htim_r, config->channel_r);
    tim_pwm_start(config->htim_g, config->channel_g);
    tim_pwm_start(config->htim_b, config->channel_b);
    return 0;
}

int rled_rgb_on(const rled_rgb_config_t* config)
{
    if (!config || !config->htim_r || !config->htim_g || !config->htim_b)
    {
        return -1;
    }
    tim_set_compare(config->htim_r, config->channel_r, 255);
    tim_set_compare(config->htim_g, config->channel_g, 255);
    tim_set_compare(config->htim_b, config->channel_b, 255);
    return 0;
}

int rled_rgb_off(const rled_rgb_config_t* config)
{
    if (!config || !config->htim_r || !config->htim_g || !config->htim_b)
    {
        return -1;
    }
    tim_set_compare(config->htim_r, config->channel_r, 0);
    tim_set_compare(config->htim_g, config->channel_g, 0);
    tim_set_compare(config->htim_b, config->channel_b, 0);
    return 0;
}

int rled_rgb_set_color(const rled_rgb_config_t* config, uint8_t r, uint8_t g, uint8_t b)
{
    if (!config || !config->htim_r || !config->htim_g || !config->htim_b)
    {
        return -1;
    }
    tim_set_compare(config->htim_r, config->channel_r, r);
    tim_set_compare(config->htim_g, config->channel_g, g);
    tim_set_compare(config->htim_b, config->channel_b, b);
    return 0;
}