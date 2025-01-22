#ifndef PERIPHERALS_INCLUDE_I2C_H_
#define PERIPHERALS_INCLUDE_I2C_H_

#define I2C_TIMEOUT 250

#define I2C_CLOCK 	21
#define I2C_SWRST   15
#define I2C_CLOCK_FRQ 42
#define I2C_CCR		210
#define I2C_TRISE	43
#define I2C_ENABLE  1 << 0

void I2C_Init(void);
uint8_t I2C_CheckBusy(void);
void I2C_Start(void);
void I2C_SendAddress(uint8_t address, uint8_t read);
void I2C_SendData(uint8_t data);
void I2C_Stop();
void I2C_Write(uint8_t address, uint8_t data);

typedef enum {
    I2C_OK,
    I2C_ERROR_BUSY,
    I2C_ERROR_START,
    I2C_ERROR_ADDR_NACK,
    I2C_ERROR_DATA_NACK,
    I2C_ERROR_TIMEOUT,
    I2C_ERROR_BUS
} I2C_Status_t;

#endif /* PERIPHERALS_INCLUDE_I2C_H_ */
