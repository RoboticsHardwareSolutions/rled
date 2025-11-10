#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef void*    GPIO_Port;  // Opaque type for GPIO port
typedef uint16_t GPIO_Pin;

typedef int GPIO_State;

void       gpio_write_pin(GPIO_Port port, GPIO_Pin pin, GPIO_State state);
void       gpio_toggle_pin(GPIO_Port port, GPIO_Pin pin);
GPIO_State gpio_read_pin(GPIO_Port port, GPIO_Pin pin);

#endif  // GPIO_H
