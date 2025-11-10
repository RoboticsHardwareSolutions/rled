#include "tim.h"
#include "stm32g0xx_hal.h"

void tim_pwm_start(TIM_Handle htim, TIM_Channel channel) {
    HAL_TIM_PWM_Start((TIM_HandleTypeDef*)htim, channel);
}

void tim_pwm_stop(TIM_Handle htim, TIM_Channel channel) {
    HAL_TIM_PWM_Stop((TIM_HandleTypeDef*)htim, channel);
}

void tim_set_compare(TIM_Handle htim, TIM_Channel channel, uint32_t compare) {
    __HAL_TIM_SET_COMPARE((TIM_HandleTypeDef*)htim, channel, compare);
}
