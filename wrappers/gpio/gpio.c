#include "gpio.h"
#include "stm32g0xx_hal.h"

void gpio_write_pin(GPIO_Port port, GPIO_Pin pin, GPIO_State state)
{
    HAL_GPIO_WritePin((GPIO_TypeDef*) port, pin, (GPIO_PinState) state);
}

void gpio_toggle_pin(GPIO_Port port, GPIO_Pin pin)
{
    HAL_GPIO_TogglePin((GPIO_TypeDef*) port, pin);
}

GPIO_State gpio_read_pin(GPIO_Port port, GPIO_Pin pin)
{
    return HAL_GPIO_ReadPin((GPIO_TypeDef*) port, pin);
}
