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

I2C_Status_t I2C_CheckBusy() {
	uint32_t timeout = I2C_TIMEOUT;

	while (I2C1 -> SR1 & (1 << 1)) {
		if (--timeout == 0) return I2C_ERROR_BUSY;
	}
	return I2C_OK;
}

I2C_Status_t I2C_Start() {
	uint32_t timeout = I2C_TIMEOUT;

	I2C1 -> CR1 |= (1 << 8);

	while (!(I2C1 -> SR1 & (1 << 0))) {
		if (--timeout == 0) return I2C_ERROR_START;
	}
	return I2C_OK;
}

I2C_Status_t I2C_SendAddress(uint8_t address, uint8_t read) {
	uint32_t timeout = I2C_TIMEOUT;

	I2C1 -> DR = (address << 1) | read;

	while (!(I2C1 -> SR1 & (1 << 1))) {
		if (I2C1 -> SR1 & (1 << 10)) {
			I2C_Stop();
			return I2C_ERROR_ADDR_NACK;
		}

	    if(I2C1->SR1 & ((1 << 8) | (1 << 9) | (1 << 11))) {
	        I2C_Stop();
	        return I2C_ERROR_BUS;
	    }

		if (--timeout == 0) {
			I2C_Stop();
			return I2C_ERROR_TIMEOUT;
		}
	}

	uint8_t dummyRead = I2C1 -> SR1;
	dummyRead = I2C1 -> SR2;
	(void)dummyRead;
	return I2C_OK;
}

I2C_Status_t I2C_SendData(uint8_t data) {
	uint32_t timeout = I2C_TIMEOUT;

	while (!(I2C1 -> SR1 & (1 << 7))) {
		if (--timeout == 0) {
			I2C_Stop();
			return I2C_ERROR_DATA_NACK;
		}
	}

	I2C1 -> DR = data;

	timeout = I2C_TIMEOUT;

	while (!(I2C1 -> SR1 & (1 << 2))) {
		if (I2C1 -> SR1 & (1 << 10)) {
			I2C_Stop();
			return I2C_ERROR_DATA_NACK;
		}

	    if(I2C1->SR1 & ((1 << 8) | (1 << 9) | (1 << 11))) {
	        I2C_Stop();
	        return I2C_ERROR_BUS;
	    }
		if (--timeout == 0) return I2C_ERROR_TIMEOUT;
	}
	return I2C_OK;
}

void I2C_Stop() {
	I2C1 -> CR1 |= (1 << 9);
}

I2C_Status_t I2C_Write(uint8_t address, uint8_t data) {
	I2C_Status_t status;

	status = I2C_CheckBusy();
	if (status != I2C_OK) return status;

	status = I2C_Start();
	if (status != I2C_OK) return status;

	status = I2C_SendAddress(address, 0);
	if (status != I2C_OK) return status;

	status = I2C_SendData(data);
	if (status != I2C_OK) return status;

	I2C_Stop();
	return I2C_OK;
}

I2C_Status_t I2C_RecoverBus(void) {
    I2C1 -> CR1 |= (1 << I2C_SWRST);
    I2C1 -> CR1 &= ~(1 << I2C_SWRST);

    I2C_Init();

    return I2C_OK;
}


