#include "main.h"
#include "i2c.h"


void I2C_Init() {
	RCC -> APB1ENR |= (1 << I2C_CLOCK);
	I2C1 -> CR1 |= (1 << I2C_SWRST);
	I2C1 -> CR1 &= ~(1 << I2C_SWRST);
	I2C1 -> CR2 |= (I2C_CLOCK_FRQ);
	I2C1 -> CCR = I2C_CCR;
	I2C1 -> TRISE = I2C_TRISE;
	I2C1 -> CR1 |= (I2C_ENABLE);
}

uint8_t I2C_CheckBusy() {
	if (I2C1 -> SR1 & (1 << 1)) {
		return 1;
	}
	return 0;
}

void I2C_Start() {
	I2C1 -> CR1 |= (1 << 8);

	while (!(I2C1 -> SR1 & (1 << 0)));
}

void I2C_SendAddress(uint8_t address, uint8_t read) {
	I2C1 -> DR = (address << 1) | read;

	while (!(I2C1 -> SR1 & (1 << 1)));

	uint8_t dummyRead = I2C1 -> SR1;
	dummyRead = I2C1 -> SR2;
	(void)dummyRead;
}

void I2C_SendData(uint8_t data) {
	while (!(I2C1 -> SR1 & (1 << 7)));

	I2C1 -> DR = data;

	while (!(I2C1 -> SR1 & (1 << 2)));
}

void I2C_Stop() {
	I2C1 -> CR1 |= (1 << 9);
}

void I2C_Write(uint8_t address, uint8_t data) {
	I2C_CheckBusy();
	I2C_Start();
	I2C_SendAddress(address, 0);
	I2C_SendData(data);
	I2C_Stop();
}


