#include "main.h"
#include "usart2.h"
#include "button.h"
#include "i2c.h"
#include "led.h"
#include "oled.h"

void System_Init();

int main() {
	System_Init();

	USART2_Print("UPDATED....\r\n");

	while(1) {

	}
}

void System_Init() {
	USART_Init();
	Button_Init();
	I2C_Init();
	OLED_Init();
	LED_Init();
}
