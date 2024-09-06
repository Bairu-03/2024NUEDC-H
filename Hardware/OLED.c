#include "oled.h"
#include "oledfont.h"  	 
#include "ti/driverlib/m0p/dl_core.h"

//反显函数
void OLED_ColorTurn(uint8_t i)
{
    if(i==0)
    {
        OLED_WR_Byte(0xA6,OLED_CMD);//正常显示
    }
    if(i==1)
    {
        OLED_WR_Byte(0xA7,OLED_CMD);//反色显示
    }
}

//屏幕旋转180度
void OLED_DisplayTurn(uint8_t i)
{
    if(i==0)
    {
        OLED_WR_Byte(0xC8,OLED_CMD);//正常显示
        OLED_WR_Byte(0xA1,OLED_CMD);
    }
    if(i==1)
    {
        OLED_WR_Byte(0xC0,OLED_CMD);//反转显示
        OLED_WR_Byte(0xA0,OLED_CMD);
    }
}

//起始信号
void OLED_I2C_Start(void)
{
    OLED_SDA_Set();
    OLED_SCL_Set();

    OLED_SDA_Clr();
    OLED_SCL_Clr();
}

//结束信号
void OLED_I2C_Stop(void)
{
    OLED_SDA_Clr();
    OLED_SCL_Set();

    OLED_SDA_Set();
}

//等待信号响应
void OLED_I2C_WaitAck(void) //测数据信号的电平
{
    OLED_SDA_Set();

    OLED_SCL_Set();

    OLED_SCL_Clr();
}

//写入一个字节
void OLED_Send_Byte(uint8_t dat)
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        OLED_SCL_Clr();//将时钟信号设置为低电平
        if(dat&0x80)//将dat的8位从最高位依次写入
        {
            OLED_SDA_Set();
        }
        else
        {
            OLED_SDA_Clr();
        }

        OLED_SCL_Set();

        OLED_SCL_Clr();
        dat<<=1;
    }
}

//发送一个字节
//向SSD1306写入一个字节。
//mode:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(uint8_t dat,uint8_t mode)
{
    OLED_I2C_Start();
    OLED_Send_Byte(0x78);
    OLED_I2C_WaitAck();
    if(mode){OLED_Send_Byte(0x40);}
    else{OLED_Send_Byte(0x00);}
    OLED_I2C_WaitAck();
    OLED_Send_Byte(dat);
    OLED_I2C_WaitAck();
    OLED_I2C_Stop();
}

/**
 * @brief  向OLED屏发送命令。
 * @param  Command 要写入的命令。
 * @retval 无
 */
void OLED_WriteCommand(uint8_t Command)
{
    OLED_I2C_Start();
    OLED_Send_Byte(0x78); // 从机地址
    OLED_I2C_WaitAck();
    OLED_Send_Byte(0x00); // 写命令
    OLED_I2C_WaitAck();
    OLED_Send_Byte(Command);
    OLED_I2C_WaitAck();
    OLED_I2C_Stop();
}

/**
 * @brief  向OLED屏发送数据。
 * @param  Data 要写入的数据。
 * @retval 无
 */
void OLED_WriteData(uint8_t Data)
{
    OLED_I2C_Start();
    OLED_Send_Byte(0x78); // 从机地址
    OLED_I2C_WaitAck();
    OLED_Send_Byte(0x40); // 写数据
    OLED_I2C_WaitAck();
    OLED_Send_Byte(Data);
    OLED_I2C_WaitAck();
    OLED_I2C_Stop();
}

/**
 * @brief  设置屏幕显示起始坐标。
 * @param  Line 行（页）地址，以左上角为原点，向下方向的坐标。
 *     @arg 取值: 0 - 7
 * @param  Column 列地址，以左上角为原点，向右方向的坐标。
 *     @arg 取值: 0 - 127
 * @retval 无
 */
void OLED_SetCursor(uint8_t Line, uint8_t Column)
{
    OLED_WriteCommand(0xB0 | Line);                   // 设置行地址位置
    OLED_WriteCommand(0x10 | ((Column & 0xF0) >> 4)); // 设置列地址位置高4位
    OLED_WriteCommand(0x00 | (Column & 0x0F));        // 设置列地址位置低4位
}
	  
//开启OLED显示    
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
    uint8_t i,n;		    
    for(i=0;i<8;i++)  
    {  
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
        OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
        for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
    } //更新显示
}

//m^n函数
uint32_t OLED_Pow(uint8_t m,uint8_t n)
{
    uint32_t result=1;	 
    while(n--)result*=m;    
    return result;
}		

/**
 * @brief  OLED显示一个字符。
 * @param  Line 起始行位置。
 *     @arg 取值: 1 - 8
 * @param  Column 起始列位置。
 *     @arg 取值: 1 - 128
 * @param  Char 要显示的一个字符。
 *     @arg 取值: ASCII可见字符
 * @param  Size 字符大小。
 *     @arg 取值(宽x高): 6（6x8）、8（8x16）
 * @retval 无
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, int8_t Char, uint8_t Size)
{
    uint8_t i;
    if (Size == 8) // 字符大小8x16
    {
        OLED_SetCursor(Line - 1, Column - 1); // 设置光标位置在上半部分
        for (i = 0; i < 8; i++)
        {
            OLED_WriteData(OLED_F8x16[Char - ' '][i]); // 显示上半部分内容
        }
        OLED_SetCursor((Line - 1) + 1, Column - 1); // 设置光标位置在下半部分
        for (i = 0; i < 8; i++)
        {
            OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]); // 显示下半部分内容
        }
    }
    else // 字符大小6x8
    {
        OLED_SetCursor(Line - 1, Column - 1);
        for (i = 0; i < 6; i++)
        {
            OLED_WriteData(OLED_F6x8[Char - ' '][i]);
        }
    }
}

/**
 * @brief  OLED显示字符串。
 * @param  Line 起始行位置。
 *     @arg 取值: 1 - 8
 * @param  Column 起始列位置。
 *     @arg 取值: 1 - 128
 * @param  String 要显示的字符串。
 *     @arg 取值: ASCII可见字符
 * @param  Size 字符大小。
 *     @arg 取值(宽x高): 6（6x8）、8（8x16）
 * @retval 无
 */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String, uint8_t Size)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)
    {
        OLED_ShowChar(Line, Column + Size * i, String[i], Size);
    }
}

/**
 * @brief  OLED显示数字（十进制，正数）。
 * @param  Line 起始行位置。
 *     @arg 取值: 1 - 8
 * @param  Column 起始列位置。
 *     @arg 取值: 1 - 128
 * @param  Number 要显示的数字。
 *     @arg 取值: 0 - 4294967295
 * @param  Length 要显示数字的长度。
 *     @arg 取值: 1 - 10
 * @param  Size 字符大小。
 *     @arg 取值(宽x高): 6（6x8）、8（8x16）
 * @retval 无
 */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Size)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + Size * i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', Size);
    }
}

/**
 * @brief  OLED显示数字（十进制，带符号数）。
 * @param  Line 起始行位置。
 *     @arg 取值: 1 - 8
 * @param  Column 起始列位置。
 *     @arg 取值: 1 - 128
 * @param  Number 要显示的数字。
 *     @arg 取值: -2147483648 - +2147483647
 * @param  Length 要显示数字的长度。
 *     @arg 取值: 1 - 10
 * @param  Size 字符大小。
 *     @arg 取值(宽x高): 6（6x8）、8（8x16）
 * @retval 无
 */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Size)
{
    uint32_t Number1;
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+', Size);
        Number1 = Number;
    }
    else
    {
        OLED_ShowChar(Line, Column, '-', Size);
        Number1 = -Number;
    }
    OLED_ShowNum(Line, Column + Size, Number1, Length, Size);
}

/**
 * @brief  OLED显示有符号浮点数
 * @param  Line 起始行位置。
 *     @arg 取值: 1 - 8
 * @param  Column 起始列位置。
 *     @arg 取值: 1 - 128
 * @param  Num 要显示的数字。
 *     @arg 取值: -3.4028235E38 - +3.4028235E38
 * @param  Intlen 要显示的整数位数。
 *     @arg 取值: 1 - 10
 * @param  Declen 要显示的小数位数。
 *     @arg 取值: 1 - 10
 * @param  Size 字符大小。
 *     @arg 取值(宽x高): 6（6x8）、8（8x16）
 * @retval 无
 */
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Num, uint8_t Intlen, uint8_t Declen, uint8_t Size)
{
    uint8_t p;
    unsigned long m;

    OLED_ShowSignedNum(Line, Column, (int32_t)Num, Intlen, Size);

    if (Declen > 0)
        OLED_ShowChar(Line, Column + Size * (Intlen + 1), '.', Size);

    if(Num < 0) Num = -Num;
    for (p = 2, m = 10; p <= Declen + 1; p++, m *= 10)
    {
        OLED_ShowNum(Line, Column + Size * (Intlen + p), (unsigned long)((Num - (uint32_t)Num) * m) % 10, 1, Size);
    }
}

/**
 * @brief  OLED显示数字（十六进制，正数）。
 * @param  Line 起始行位置。
 *     @arg 取值: 1 - 8
 * @param  Column 起始列位置。
 *     @arg 取值: 1 - 128
 * @param  Number 要显示的数字。
 *     @arg 取值: 0 - 0xFFFFFFFF
 * @param  Length 要显示数字的长度。
 *     @arg 取值: 1 - 8
 * @param  Size 字符大小。
 *     @arg 取值(宽x高): 6（6x8）、8（8x16）
 * @retval 无
 */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Size)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++)
    {
        SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
        if (SingleNumber < 10)
        {
            OLED_ShowChar(Line, Column + Size * i, SingleNumber + '0', Size);
        }
        else
        {
            OLED_ShowChar(Line, Column + Size * i, SingleNumber - 10 + 'A', Size);
        }
    }
}

/**
 * @brief  OLED显示数字（二进制，正数）。
 * @param  Line 起始行位置。
 *     @arg 取值: 1 - 8
 * @param  Column 起始列位置。
 *     @arg 取值: 1 - 128
 * @param  Number 要显示的数字。
 *     @arg 取值: 0 - 1111 1111 1111 1111
 * @param  Length 要显示数字的长度。
 *     @arg 取值: 1 - 16
 * @param  Size 字符大小。
 *     @arg 取值(宽x高): 6（6x8）、8（8x16）
 * @retval 无
 */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Size)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + Size * i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0', Size);
    }
}

/**
 * @brief  OLED显示汉字。
 * @param  Line 起始行位置。
 *     @arg 取值: 1 - 8
 * @param  Column 起始列位置。
 *     @arg 取值: 1 - 128
 * @param  Num 要显示的汉字在字库数组中的索引号（下标号）。
 * @retval 无
 */
void OLED_ShowCN(uint8_t Line, uint8_t Column, uint8_t Num)
{
    uint8_t i;
    uint8_t wide = 16; // 字宽

    OLED_SetCursor(Line - 1, Column - 1); // 参数1:把光标设置在第几行. 参数2:把光标设置在第几列
    for (i = 0; i < wide; i++)
    {
        OLED_WriteData(OLED_HzK[Num][i]); // 显示上半部分内容
    }
    OLED_SetCursor((Line - 1) + 1, Column - 1);
    for (i = 0; i < wide; i++)
    {
        OLED_WriteData(OLED_HzK[Num][i + wide]); // 显示下半部分内容
    }
}

/**
 * @brief  OLED显示图片。
 * @param  LineS 绘制图片的起始行位置。
 *     @arg 取值: 1 - 8
 * @param  LineE 绘制图片的终止行位置。
 *     @arg 取值: 1 - 8
 * @param  ColumnS 绘制图片的起始列位置。
 *     @arg 取值: 1 - 128
 * @param  ColumnE 绘制图片的终止列位置。
 *     @arg 取值: 1 - 128
 * @param  BMP 图片模数组。
 * @retval 无
 */
void OLED_DrawBMP(uint8_t LineS, uint8_t LineE, uint8_t ColumnS, uint8_t ColumnE, uint8_t BMP[])
{
    uint32_t j = 0;
    uint8_t x, y;

    if ((LineE - 1) % 8 == 0)
        y = (LineE - 1) / 8;
    else
        y = (LineE - 1) / 8 + 1;
    for (y = (LineS - 1); y <= (LineE - 1); y++)
    {
        OLED_SetCursor(y, (ColumnS - 1));
        for (x = (ColumnS - 1); x <= (ColumnE - 1); x++)
        {
            OLED_WriteData(BMP[j++]);
        }
    }
}

//初始化SSD1306					    
void OLED_Init(void)
{
    uint32_t i, j;
    for (i = 0; i < 1000; i++) // 上电延时
        for (j = 0; j < 1000; j++);

    OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
    OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00,OLED_CMD);//-not offset
    OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
    OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
    OLED_WR_Byte(0x12,OLED_CMD);
    OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
    OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02,OLED_CMD);//
    OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
    OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
    OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
    OLED_Clear();
    OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
}  

