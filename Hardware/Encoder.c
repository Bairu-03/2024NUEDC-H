#include "ti_msp_dl_config.h"
#include "Encoder.h"

uint32_t gpioA;
uint16_t PA9_Count = 0;
uint16_t PA8_Count = 0;
uint16_t PA9PulseNumber = 0;
uint16_t PA8PulseNumber = 0;

uint8_t Enable_CP = 0;  // 为1时启动PA8、PA9引脚输入脉冲累计
uint16_t CumulativePulsePA8 = 0, CumulativePulsePA9 = 0; // 脉冲累计值

/**
 * @brief  初始化PA9，PA8编码器计数功能
 * @param  无
 * @retval 无
 */
void Encoder_Init(void)
{
    // 开启定时器0中断
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    //开启GPIOA端口中断
    NVIC_EnableIRQ(GPIO_Encoder_INT_IRQN);
}

/**
 * @brief  获取PA9引脚编码器脉冲数
 * @param  无
 * @retval 100ms内的脉冲数
 */
uint16_t getEAPulseNum(void)
{
    return PA9PulseNumber;
}

/**
 * @brief  获取PA8引脚编码器脉冲数
 * @param  无
 * @retval 100ms内的脉冲数
 */
uint16_t getEBPulseNum(void)
{
    return PA8PulseNumber;
}

void TIMER_0_INST_IRQHandler(void)
{
    PA9PulseNumber = PA9_Count;
    PA8PulseNumber = PA8_Count;
    PA9_Count = 0;
    PA8_Count = 0;
}

void GROUP1_IRQHandler(void)//Group1的中断服务函数
{
    //获取中断信号
    gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA,
    GPIO_Encoder_MotorB_PIN | GPIO_Encoder_MotorA_PIN);
    
    if((gpioA & GPIO_Encoder_MotorB_PIN) == GPIO_Encoder_MotorB_PIN)
    {
        PA8_Count++;
        
        // PA8脉冲累计
        if(Enable_CP == 1)
        {
            CumulativePulsePA8++;
            if(CumulativePulsePA8 > 65530)
                CumulativePulsePA8 = 0;
        }
    }
    
    if((gpioA & GPIO_Encoder_MotorA_PIN) == GPIO_Encoder_MotorA_PIN)
    {
        PA9_Count++;
        
        // PA9脉冲累计
        if(Enable_CP == 1)
        {
            CumulativePulsePA9++;
            if(CumulativePulsePA9 > 65530)
                CumulativePulsePA9 = 0;
        }
    }
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_Encoder_MotorB_PIN | GPIO_Encoder_MotorA_PIN);
}
