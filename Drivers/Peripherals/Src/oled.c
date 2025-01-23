#include "oled.h"

void OLED_Send_Command(uint8_t cmd) {
    I2C_Start();
    I2C_SendAddress(OLED_ADDR, 0);
    I2C_SendData(CMD_MODE);
    I2C_SendData(cmd);
    I2C_Stop();
}

void OLED_Clear() {
    OLED_Send_Command(DISPLAY_OFF);

    OLED_Send_Command(MEMORY_ADDR);
    OLED_Send_Command(HORIZ_ADDR);

    OLED_Send_Command(COLUMN_ADDR);
    OLED_Send_Command(0x00);			// Column 0
    OLED_Send_Command(0x7F);			// Column 127

    OLED_Send_Command(PAGE_ADDR);
    OLED_Send_Command(0x00);    		// Page 0
    OLED_Send_Command(0x07);    		// Page 7

    for (uint16_t i = 0; i < 1024; i++) {
        I2C_Start();
        I2C_SendAddress(OLED_ADDR, 0);
        I2C_SendData(DATA_MODE);
        I2C_SendData(0x00);
        I2C_Stop();
    }

    OLED_Send_Command(DISPLAY_ON);
}

void OLED_Init() {
    OLED_Send_Command(DISPLAY_OFF);

    OLED_Send_Command(CHARGE_PUMP);
    OLED_Send_Command(0x14);

    OLED_Send_Command(MULTIPLEX_R);
    OLED_Send_Command(0x3F); 				// 64 lines

    OLED_Send_Command(DISP_OFFSET);
    OLED_Send_Command(0x00); 				// No offset

    OLED_Send_Command(0x40); 				// Start Line 0

    OLED_Send_Command(SEGMENT_RE);
    OLED_Send_Command(COM_SCAN_D);

    OLED_Send_Command(NORM_DISP);

    OLED_Send_Command(DISPLAY_ON);

    OLED_Clear();
}

void OLED_SetCursor(uint8_t col, uint8_t page) {
    OLED_Send_Command(COLUMN_ADDR);
    OLED_Send_Command(col);
    OLED_Send_Command(127);

    OLED_Send_Command(PAGE_ADDR);
    OLED_Send_Command(page);
    OLED_Send_Command(7);
}

void OLED_WriteChar(char c) {
    if (c < 32 || c > 127) c = 32;

    const uint8_t* charData = font_5x7[c - 32];

    for (int i = 0; i < 5; i++) {
        I2C_Start();
        I2C_SendAddress(OLED_ADDR, 0);
        I2C_SendData(DATA_MODE);
        I2C_SendData(charData[i]);
        I2C_Stop();
    }
}

void OLED_WriteString(const char* str) {
    while (*str) {
        OLED_WriteChar(*str++);
    }
}
