#ifndef TIM_H
#define TIM_H

#include <stdint.h>

typedef void* TIM_Handle;  // Opaque for TIM_HandleTypeDef
typedef uint32_t TIM_Channel;

void tim_pwm_start(TIM_Handle htim, TIM_Channel channel);
void tim_pwm_stop(TIM_Handle htim, TIM_Channel channel);
void tim_set_compare(TIM_Handle htim, TIM_Channel channel, uint32_t compare);

#endif // TIM_H
