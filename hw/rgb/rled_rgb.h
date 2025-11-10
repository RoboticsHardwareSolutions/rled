#ifndef RLED_RGB_H
#define RLED_RGB_H

#include <stdint.h>

typedef struct {
    void* htim_r;
    uint32_t channel_r;
    void* htim_g;
    uint32_t channel_g;
    void* htim_b;
    uint32_t channel_b;
} rled_rgb_config_t;

void rled_rgb_init(const rled_rgb_config_t* config);
void rled_rgb_on(const rled_rgb_config_t* config);  // Turn on white?
void rled_rgb_off(const rled_rgb_config_t* config);
void rled_rgb_set_color(const rled_rgb_config_t* config, uint8_t r, uint8_t g, uint8_t b);

#endif // RLED_RGB_H
