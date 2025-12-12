#ifndef RLED_PWM_H
#define RLED_PWM_H

#include <stdint.h>

typedef struct rled_pwm_config {
    void* htim;
    uint32_t channel;
} rled_pwm_config_t;

// Returns 0 on success, negative on error
int rled_pwm_init(const rled_pwm_config_t* config);
int rled_pwm_on(const rled_pwm_config_t* config);
int rled_pwm_off(const rled_pwm_config_t* config);
int rled_pwm_set_brightness(const rled_pwm_config_t* config, uint8_t brightness);

#endif // RLED_PWM_H
