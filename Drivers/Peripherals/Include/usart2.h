#ifndef PERIPHERALS_INCLUDE_USART2_H_
#define PERIPHERALS_INCLUDE_USART2_H_

#include "main.h"
#include <stdio.h>
#include <stdarg.h>

#define USART2_CLOCK 1 << 17
#define GPIO_A_CLOCK 1 << 0
#define GPIO_A_TX    3
#define GPIO_A_RX    2
#define USART2_BAUD  16000000 / 9600
#define USART2_RECEI 2
#define USART2_TRANS 3
#define USART2_ENABLE 13

#define USART2_TIMEOUT  5000

void USART_Init(void);
void USART2_Print(const char*, ...);

#endif /* PERIPHERALS_INCLUDE_USART2_H_ */
