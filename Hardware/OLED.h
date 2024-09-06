#ifndef __OLED_H
#define __OLED_H			  	 
#include "ti_msp_dl_config.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#ifndef GPIO_OLED_PIN_SCL_PORT
#define GPIO_OLED_PIN_SCL_PORT GPIO_OLED_PORT 
#endif

#ifndef GPIO_OLED_PIN_SDA_PORT
#define GPIO_OLED_PIN_SDA_PORT GPIO_OLED_PORT 
#endif

//----------------------------------------------------------------------------------
//OLED SSD1306 I2C 时钟SCL PA12
#define		OLED_SCL_Set()			    (DL_GPIO_setPins(GPIO_OLED_PIN_SCL_PORT, GPIO_OLED_PIN_SCL_PIN))
#define		OLED_SCL_Clr()				(DL_GPIO_clearPins(GPIO_OLED_PIN_SCL_PORT, GPIO_OLED_PIN_SCL_PIN))

//----------------------------------------------------------------------------------
//OLED SSD1306 I2C 数据SDA PA13
#define		OLED_SDA_Set()				(DL_GPIO_setPins(GPIO_OLED_PIN_SDA_PORT, GPIO_OLED_PIN_SDA_PIN))
#define		OLED_SDA_Clr()			    (DL_GPIO_clearPins(GPIO_OLED_PIN_SDA_PORT, GPIO_OLED_PIN_SDA_PIN))
				   

//OLED控制用函数
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_SetCursor(uint8_t Line, uint8_t Column);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
uint32_t OLED_Pow(uint8_t m,uint8_t n);

void OLED_ShowChar(uint8_t Line, uint8_t Column, int8_t Char, uint8_t Size);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String, uint8_t Size);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Size);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Size);
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Num, uint8_t Intlen, uint8_t Declen, uint8_t Size);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Size);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Size);
void OLED_ShowCN(uint8_t Line, uint8_t Column, uint8_t Num);
void OLED_DrawBMP(uint8_t LineS, uint8_t LineE, uint8_t ColumnS, uint8_t ColumnE, uint8_t BMP[]);

void OLED_Init(void);
#endif  
	 



