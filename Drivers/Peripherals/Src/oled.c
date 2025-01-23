#include "oled.h"

OLED_Status_t OLED_Send_Command(uint8_t cmd) {
    if(I2C_Start() != I2C_OK) return OLED_ERROR_I2C;
    if(I2C_SendAddress(OLED_ADDR, 0) != I2C_OK) return OLED_ERROR_I2C;
    if(I2C_SendData(CMD_MODE) != I2C_OK) return OLED_ERROR_I2C;
    if(I2C_SendData(cmd) != I2C_OK) return OLED_ERROR_I2C;
    I2C_Stop();
    return OLED_OK;
}

OLED_Status_t OLED_Clear() {
	OLED_Status_t status;

    status = OLED_Send_Command(DISPLAY_OFF);
    if (status != OLED_OK) return status;

    status = OLED_Send_Command(MEMORY_ADDR);
    if (status != OLED_OK) return status;
    status = OLED_Send_Command(HORIZ_ADDR);
    if (status != OLED_OK) return status;

    status = OLED_Send_Command(COLUMN_ADDR);
    if (status != OLED_OK) return status;
    status = OLED_Send_Command(0x00);			// Column 0
    if (status != OLED_OK) return status;
    status = OLED_Send_Command(0x7F);			// Column 127
    if (status != OLED_OK) return status;

    status = OLED_Send_Command(PAGE_ADDR);
    if (status != OLED_OK) return status;
    status = OLED_Send_Command(0x00);    		// Page 0
    if (status != OLED_OK) return status;
    status = OLED_Send_Command(0x07);    		// Page 7
    if (status != OLED_OK) return status;

    for (uint16_t i = 0; i < 1024; i++) {
    	if (I2C_Start() != I2C_OK) return OLED_ERROR_I2C;
    	if (I2C_SendAddress(OLED_ADDR, 0) != I2C_OK) return OLED_ERROR_I2C;
    	if (I2C_SendData(DATA_MODE) != I2C_OK) return OLED_ERROR_I2C;
    	if (I2C_SendData(0x00) != I2C_OK) return OLED_ERROR_I2C;
        I2C_Stop();
    }

    status = OLED_Send_Command(DISPLAY_ON);
    if (status != OLED_OK) return status;

    return status;
}

OLED_Status_t OLED_Init() {
	OLED_Status_t status;

	status = OLED_Send_Command(DISPLAY_OFF);
	if (status != OLED_OK) return status;

	status = OLED_Send_Command(CHARGE_PUMP);
	if (status != OLED_OK) return status;
	status = OLED_Send_Command(0x14);
	if (status != OLED_OK) return status;

	status = OLED_Send_Command(MULTIPLEX_R);
	if (status != OLED_OK) return status;
	status = OLED_Send_Command(0x3F); 				// 64 lines
	if (status != OLED_OK) return status;

	status = OLED_Send_Command(DISP_OFFSET);
	if (status != OLED_OK) return status;
	status = OLED_Send_Command(0x00); 				// No offset
	if (status != OLED_OK) return status;

	status = OLED_Send_Command(0x40); 				// Start Line 0
	if (status != OLED_OK) return status;

	status = OLED_Send_Command(SEGMENT_RE);
	if (status != OLED_OK) return status;
	status = OLED_Send_Command(COM_SCAN_D);
	if (status != OLED_OK) return status;

	status = OLED_Send_Command(NORM_DISP);
	if (status != OLED_OK) return status;

	status = OLED_Send_Command(DISPLAY_ON);
	if (status != OLED_OK) return status;

	status = OLED_Clear();
	if (status != OLED_OK) return status;

	return status;
}

// col must be <= 127 and page must be <= 7
OLED_Status_t OLED_SetCursor(uint8_t col, uint8_t page) {
	if (col > 127 || page > 7) return OLED_ERROR_PARAM;

	OLED_Status_t status;

	status = OLED_Send_Command(COLUMN_ADDR);
	if (status != OLED_OK) return status;
	status = OLED_Send_Command(col);
	if (status != OLED_OK) return status;
	status = OLED_Send_Command(127);
	if (status != OLED_OK) return status;

	status = OLED_Send_Command(PAGE_ADDR);
	if (status != OLED_OK) return status;
	status = OLED_Send_Command(page);
	if (status != OLED_OK) return status;
	status = OLED_Send_Command(7);
	if (status != OLED_OK) return status;

	return status;
}

OLED_Status_t OLED_WriteChar(char c) {
    if (c < 32 || c > 127) return OLED_ERROR_PARAM;

    const uint8_t* charData = font_5x7[c - 32];

    for (int i = 0; i < 5; i++) {
        if (I2C_Start() != I2C_OK) return OLED_ERROR_I2C;
        if (I2C_SendAddress(OLED_ADDR, 0) != I2C_OK) return OLED_ERROR_I2C;
        if (I2C_SendData(DATA_MODE) != I2C_OK) return OLED_ERROR_I2C;
        if (I2C_SendData(charData[i]) != I2C_OK) return OLED_ERROR_I2C;
        I2C_Stop();
    }
    return OLED_OK;
}

OLED_Status_t OLED_WriteString(const char* str) {

    while (*str) {
       if (OLED_WriteChar(*str++) != OLED_OK) return OLED_ERROR_I2C;
    }
    return OLED_OK;
}
