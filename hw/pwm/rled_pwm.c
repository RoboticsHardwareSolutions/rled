#include "rled_pwm.h"
#include "../../wrappers/tim/tim.h"

void rled_pwm_init(const rled_pwm_config_t* config) {
    // Assume TIM is configured and started elsewhere
    tim_pwm_start(config->htim, config->channel);
}

void rled_pwm_on(const rled_pwm_config_t* config) {
    tim_set_compare(config->htim, config->channel, 255);  // Assuming period is 255
}

void rled_pwm_off(const rled_pwm_config_t* config) {
    tim_set_compare(config->htim, config->channel, 0);
}

void rled_pwm_set_brightness(const rled_pwm_config_t* config, uint8_t brightness) {
    tim_set_compare(config->htim, config->channel, brightness);  // Assuming period is 255
}
