#include "ti_msp_dl_config.h"
#include "stdint.h"

/**
* @brief  控制B电机PWM占空比（PA28）
 * @param  Duty PWM占空比。
 *     @arg 取值: 0 - 100.0
 * @retval
 */
void MotorB_PWM_Duty(float Duty)
{
    DL_TimerG_setCaptureCompareValue(MotorBPWM_INST,(1000 * Duty / 100.0), GPIO_MotorBPWM_C0_IDX);
}

/**
* @brief  控制A电机PWM占空比（PB20）
 * @param  Duty PWM占空比。
 *     @arg 取值: 0 - 100.0
 * @retval
 */
void MotorA_PWM_Duty(float Duty)
{
    DL_TimerG_setCaptureCompareValue(MotorAPWM_INST,(1000 * Duty / 100.0), GPIO_MotorAPWM_C0_IDX);
}
