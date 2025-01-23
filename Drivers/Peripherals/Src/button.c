#include "main.h"
#include "button.h"

void Button_Init() {
	RCC -> APB1ENR |= (1 << GPIO_PORT_A);

	GPIOA -> MODER &= ~(3 << (2 * BUTTON_PIN));

	GPIOA -> PUPDR &= ~(3 << (2 * BUTTON_PIN));
	GPIOA -> PUPDR |= (1 << (2 * BUTTON_PIN));
}

