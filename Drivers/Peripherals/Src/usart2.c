#include "usart2.h"

void USART_Init(void) {
	RCC -> APB1ENR |= (USART2_CLOCK);
	RCC -> AHB1ENR |= (GPIO_A_CLOCK);

	GPIOA -> MODER &= ~((3 << (2 * GPIO_A_TX)) | (3 << (2 * GPIO_A_RX)));
	GPIOA -> MODER |= (2 << (2 * GPIO_A_TX)) | (2 << (2 * GPIO_A_RX));

	GPIOA -> AFR[0] |= (7 << (4 * GPIO_A_TX)) | (7 << (4 *  GPIO_A_RX));

	USART2 -> BRR = USART2_BAUD;
	USART2 -> CR1 |= (1 << GPIO_A_TX) | (1 << (USART2_ENABLE));
}

void USART2_Print(const char* str, ...) {
    char buffer[100];
    uint16_t timeout = USART2_TIMEOUT;

    va_list args;
    va_start(args, str);
    vsprintf(buffer, str, args);
    va_end(args);

    char* ptr = buffer;
    while(*ptr) {
        while(!(USART2->SR & (1 << 7))) {
        	if (--timeout == 0) break;
        }
        USART2->DR = *ptr++;
    }
}
