#include "light_sensor.h"

Light_Status_t Light_Sensor_Init(){
	if (I2C_Write(LIGHT_ADDR, LIGHT_ON) != I2C_OK) return LIGHT_ERROR_I2C;
	if (I2C_Write(LIGHT_ADDR, LIGHT_CONTINOUS) != I2C_OK) return LIGHT_ERROR_I2C;
	return LIGHT_OK;
}

Light_Reading_t Light_Reading() {
	Light_Reading_t reading = {0, LIGHT_OK};
	uint8_t first, second;
	uint16_t timeout = READ_TIMEOUT;

	if (I2C_Start() != I2C_OK) {
		reading.status = LIGHT_ERROR_I2C;
		return reading;
	}
	if (I2C_Send_Address(LIGHT_ADDR, 1) != I2C_OK) {
		reading.status = LIGHT_ERROR_I2C;
		return reading;
	}

	I2C1 -> CR1 |= (1 << 10);				// Send ACK

	while(!(I2C1 -> SR1 & (1 << 6))){
		if (--timeout == 0) {
			reading.status = LIGHT_ERROR_READING;
			return reading;
		}
	}
	first = I2C1 -> DR;

	I2C1 -> CR1 &= ~(1 << 10);				// Clear ACK

	timeout = READ_TIMEOUT;
	while(!(I2C1 -> SR1 & (1 << 6))) {
		if (--timeout == 0) {
			reading.status = LIGHT_ERROR_READING;
			return reading;
		}
	}
	second = I2C1 -> DR;

	I2C_Stop();

	reading.value = (first << 8) | second;
	return reading;
}
