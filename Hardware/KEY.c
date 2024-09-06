#include "ti_msp_dl_config.h"
#include "board.h"
#include "KEY.h"

uint8_t get_Key1Num(void)
{
    uint8_t Key1Num;
    if(DL_GPIO_readPins(GPIO_KEY_KEY1_PORT, GPIO_KEY_KEY1_PIN) == 0)
    {
        while(DL_GPIO_readPins(GPIO_KEY_KEY1_PORT, GPIO_KEY_KEY1_PIN) == 0);
        Key1Num = 0;
    }
    else
    {
        Key1Num = 1;
    }
    return Key1Num;
}

uint8_t get_Key2Num(void)
{
    uint8_t Key2Num;
    if(DL_GPIO_readPins(GPIO_KEY_KEY2_PORT, GPIO_KEY_KEY2_PIN) == 0)
    {
        while(DL_GPIO_readPins(GPIO_KEY_KEY2_PORT, GPIO_KEY_KEY2_PIN) == 0);
        Key2Num = 0;
    }
    else
    {
        Key2Num = 1;
    }
    return Key2Num;
}

uint8_t get_Key3Num(void)
{
    uint8_t Key3Num;
    if(DL_GPIO_readPins(GPIO_KEY_KEY3_PORT, GPIO_KEY_KEY3_PIN) == 0)
    {
        while(DL_GPIO_readPins(GPIO_KEY_KEY3_PORT, GPIO_KEY_KEY3_PIN) == 0);
        Key3Num = 0;
    }
    else
    {
        Key3Num = 1;
    }
    return Key3Num;
}
