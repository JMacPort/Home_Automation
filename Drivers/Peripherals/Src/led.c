#include "main.h"
#include "led.h"

void LED_Init() {
	RCC -> APB1ENR |= (1 << GPIO_PORT_A);

	GPIOA -> MODER &= ~(LED_MODE << LED_PIN);
	GPIOA -> MODER |= (LED_MODE << LED_PIN);
}

void LED_ON() {GPIOA -> ODR |= (1 << LED_PIN);}

void LED_OFF() {GPIOA -> ODR &= ~(1 << LED_PIN);}

led MyLED = {LED_ON, LED_OFF};
