#include "ti_msp_dl_config.h"
#include "Trace.h"

uint8_t get_TL3(void)
{
    if(DL_GPIO_readPins(GPIO_Trace_PORT, GPIO_Trace_TL3_PIN) > 0)
    {
        return 1;
    }
    return 0;
}

uint8_t get_TL2(void)
{
    if(DL_GPIO_readPins(GPIO_Trace_PORT, GPIO_Trace_TL2_PIN) > 0)
    {
        return 1;
    }
    return 0;
}

uint8_t get_TL1(void)
{
    if(DL_GPIO_readPins(GPIO_Trace_PORT, GPIO_Trace_TL1_PIN) > 0)
    {
        return 1;
    }
    return 0;
}

uint8_t get_TM(void)
{
    if(DL_GPIO_readPins(GPIO_Trace_PORT, GPIO_Trace_TM_PIN) > 0)
    {
        return 1;
    }
    return 0;
}

uint8_t get_TR1(void)
{
    if(DL_GPIO_readPins(GPIO_Trace_PORT, GPIO_Trace_TR1_PIN) > 0)
    {
        return 1;
    }
    return 0;
}

uint8_t get_TR2(void)
{
    if(DL_GPIO_readPins(GPIO_Trace_PORT, GPIO_Trace_TR2_PIN) > 0)
    {
        return 1;
    }
    return 0;
}

uint8_t get_TR3(void)
{
    if(DL_GPIO_readPins(GPIO_Trace_PORT, GPIO_Trace_TR3_PIN) > 0)
    {
        return 1;
    }
    return 0;
}

uint8_t get_T_ALL(void)
{
    uint8_t temp = 0;
    temp += get_TL3();
    temp <<= 1;
    temp += get_TL2();
    temp <<= 1;
    temp += get_TL1();
    temp <<= 1;
    temp += get_TM();
    temp <<= 1;
    temp += get_TR1();
    temp <<= 1;
    temp += get_TR2();
    temp <<= 1;
    temp += get_TR3();
    return temp;
}

char get_Terror(void)
{
    char error;
    if(get_T_ALL() == 0x08)  // 0001000 正
    {
        error = 10;
    }
    else if(get_T_ALL() == 0x10)  // 0010000 偏右
    {
        error = 13;
    }
    else if(get_T_ALL() == 0x20)  // 0100000 大偏右
    {
        error = 14;
    }
    // 1000000 或 1100000 或 1110000 或 0110000 更大偏右
    else if(get_T_ALL() == 0x40 || get_T_ALL() == 0x60 || get_T_ALL() == 0x70 || get_T_ALL() == 0x30)  
    {
        error = 16;
    }
    else if(get_T_ALL() == 0x04)  // 0000100 偏左
    {
        error = 7;
    }
    else if(get_T_ALL() == 0x02)  // 0000010 大偏左
    {
        error = 6;
    }
    // 0000001 或 0000011 或 0000111 或 0000110 更大偏左
    else if(get_T_ALL() == 0x01 || get_T_ALL() == 0x03 || get_T_ALL() == 0x07 || get_T_ALL() == 0x06)
    {
        error = 4;
    }
    else
    {
        error = 10;
    }
    return error;
}
