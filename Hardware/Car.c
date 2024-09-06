#include "ti_msp_dl_config.h"
#include "Car.h"
#include "PWM.h"
#include "board.h"

/**
 * @brief  控制小车驱动轮电机状态及转速。
 * @param  Status 小车状态。
 *      @arg 有效取值:
 *       - \b Car_F    : 向前
 *       - \b Car_L    : 原地左转
 *       - \b Car_R    : 原地右转
 *       - \b Car_Stop : 停止（此时传入函数的PWM占空比值将被忽略，建议设为0）
 * @param  leftMotorDuty 左电机PWM占空比。
 *      @arg 取值: 0 - 100.0
 * @param  rightMotorDuty 右电机PWM占空比。
 *      @arg 取值: 0 - 100.0
 * @retval 无
 */
void Car_Status(uint8_t Status, float leftMotorDuty, float rightMotorDuty)
{
    if(Status == Car_F)
    {
        DL_GPIO_clearPins(GPIO_Motor_PORT,
            GPIO_Motor_BIN2_PIN |
            GPIO_Motor_BIN1_PIN |
            GPIO_Motor_AIN1_PIN |
            GPIO_Motor_AIN2_PIN
        );
        delay_us(10);
        
        DL_GPIO_setPins(GPIO_Motor_PORT, GPIO_Motor_BIN1_PIN | GPIO_Motor_AIN1_PIN);
    }

    if(Status == Car_L)
    {
        DL_GPIO_clearPins(GPIO_Motor_PORT,
            GPIO_Motor_BIN2_PIN |
            GPIO_Motor_BIN1_PIN |
            GPIO_Motor_AIN1_PIN |
            GPIO_Motor_AIN2_PIN
        );
        delay_us(10);
        
        DL_GPIO_setPins(GPIO_Motor_PORT, GPIO_Motor_BIN1_PIN | GPIO_Motor_AIN2_PIN);
    }
    
    if(Status == Car_R)
    {
        DL_GPIO_clearPins(GPIO_Motor_PORT,
            GPIO_Motor_BIN2_PIN |
            GPIO_Motor_BIN1_PIN |
            GPIO_Motor_AIN1_PIN |
            GPIO_Motor_AIN2_PIN
        );
        delay_us(10);
        
        DL_GPIO_setPins(GPIO_Motor_PORT, GPIO_Motor_BIN2_PIN | GPIO_Motor_AIN1_PIN);
    }

    if(Status == Car_Stop)
    {
        DL_GPIO_clearPins(GPIO_Motor_PORT,
            GPIO_Motor_BIN2_PIN |
            GPIO_Motor_BIN1_PIN |
            GPIO_Motor_AIN1_PIN |
            GPIO_Motor_AIN2_PIN
        );
        leftMotorDuty = 0;
        rightMotorDuty = 0;
        delay_us(10);
    }
    
    MotorA_PWM_Duty(leftMotorDuty);  // 左轮占空比
    MotorB_PWM_Duty(rightMotorDuty);  // 右轮占空比
}
