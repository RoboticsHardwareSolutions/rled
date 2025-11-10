#include "rled_rgb.h"
#include "../../wrappers/tim/tim.h"

void rled_rgb_init(const rled_rgb_config_t* config) {
    // Assume TIMs are configured and started elsewhere
    tim_pwm_start(config->htim_r, config->channel_r);
    tim_pwm_start(config->htim_g, config->channel_g);
    tim_pwm_start(config->htim_b, config->channel_b);
}

void rled_rgb_on(const rled_rgb_config_t* config) {
    tim_set_compare(config->htim_r, config->channel_r, 255);
    tim_set_compare(config->htim_g, config->channel_g, 255);
    tim_set_compare(config->htim_b, config->channel_b, 255);
}

void rled_rgb_off(const rled_rgb_config_t* config) {
    tim_set_compare(config->htim_r, config->channel_r, 0);
    tim_set_compare(config->htim_g, config->channel_g, 0);
    tim_set_compare(config->htim_b, config->channel_b, 0);
}

void rled_rgb_set_color(const rled_rgb_config_t* config, uint8_t r, uint8_t g, uint8_t b) {
    tim_set_compare(config->htim_r, config->channel_r, r);
    tim_set_compare(config->htim_g, config->channel_g, g);
    tim_set_compare(config->htim_b, config->channel_b, b);
}
