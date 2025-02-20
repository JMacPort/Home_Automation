#ifndef PERIPERALS_LCD_H_
#define PERIPERALS_LCD_H_

#include "i2c.h"
#include "font_5x7.h"

#define OLED_ADDR	0x3C

#define DISPLAY_ON  0xAF
#define DISPLAY_OFF	0xAE
#define MEMORY_ADDR 0x20
#define HORIZ_ADDR	0x00
#define COLUMN_ADDR 0x21
#define PAGE_ADDR   0x22
#define CMD_MODE	0x00
#define DATA_MODE	0x40
#define CHARGE_PUMP 0x8D
#define MULTIPLEX_R 0xA8
#define DISP_OFFSET 0xD3
#define SEGMENT_RE  0xA1
#define COM_SCAN_D  0xC8
#define NORM_DISP   0xA6

typedef enum {
	OLED_ERROR_PARAM,
	OLED_ERROR_I2C,
	OLED_OK
} OLED_Status_t;

OLED_Status_t OLED_Send_Command(uint8_t cmd);
OLED_Status_t OLED_ClearScreen();
OLED_Status_t OLED_Init();
OLED_Status_t OLED_SetCursor(uint8_t, uint8_t);
OLED_Status_t OLED_WriteChar(char);
OLED_Status_t OLED_WriteString(const char*);

#endif /* PERIPERALS_LCD_H_ */
