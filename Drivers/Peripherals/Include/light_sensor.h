#ifndef PERIPERALS_LIGHT_SENSOR_H_
#define PERIPERALS_LIGHT_SENSOR_H_

#include "i2c.h"

#define LIGHT_ADDR 0x23
#define LIGHT_ON   0x01
#define LIGHT_CONT 0x10

#define READ_TIMEOUT 1000

typedef enum {
	LIGHT_ERROR_I2C,
	LIGHT_ERROR_READING,
	LIGHT_OK
} Light_Status_t;

typedef struct {
    uint16_t value;
    Light_Status_t status;
} Light_Reading_t;

Light_Status_t Light_Init();
uint16_t Light_Reading();

#endif /* PERIPERALS_LIGHT_SENSOR_H_ */
