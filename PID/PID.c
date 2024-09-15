/**
 * @file    PID.c
 * @version v1.3
 * @author  Bairu
 * @date    2024年8月21日 16:09:44
 * @brief   PID算法(位置式、增量式)
 */

#include "PID.h"

/**
 * @brief  位置式PID参数初始化
 * @param  pid PID参数结构体
 * @param  Kp 比例项系数
 * @param  Ki 积分项系数
 * @param  Kd 微分项系数
 * @param  target 目标值
 * @param  minIntegral 积分限幅-最小值
 * @param  maxIntegral 积分限幅-最大值
 * @param  minOutput PID输出限幅-最小值
 * @param  maxOutput PID输出限幅-最大值
 * @retval 无
 */
void PID_Init(PID *pid, float Kp, float Ki, float Kd, float target,
              float minIntegral, float maxIntegral,
              float minOutput, float maxOutput)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->target = target;
    pid->minIntegral = minIntegral;
    pid->maxIntegral = maxIntegral;
    pid->minOutput = minOutput;
    pid->maxOutput = maxOutput;
    pid->error = 0.0;
    pid->last_error = 0.0;
    pid->integral = 0.0;
}

/**
 * @brief  重设位置式PID目标值
 * @param  pid PID参数结构体
 * @param  target 目标值
 * @retval 无
 */
void PID_ResetTarget(PID *pid, float target)
{
    pid->target = target;
}

/**
 * @brief  重设位置式PID各项系数
 * @param  pid PID参数结构体
 * @param  K_x 要修改的系数
 *      @arg 有效取值:
 *          - \b K_p : p项系数
 *          - \b K_i : i项系数
 *          - \b K_d : d项系数
 * @param  value 系数的新值
 * @retval 无
 */
void PID_Reset_pid(PID *pid, uint8_t K_x, float value)
{
    switch (K_x)
    {
    case K_p:
        pid->Kp = value;
        break;
    case K_i:
        pid->Ki = value;
        break;
    case K_d:
        pid->Kd = value;
        break;
    }
}

/**
 * @brief  位置式PID运算。
 * @param  pid PID参数结构体
 * @param  input 当前值
 * @retval 位置式PID运算结果
 */
float PID_Compute(PID *pid, float input)
{
    pid->error = pid->target - input;                        // 计算误差
    pid->integral += pid->error;                             // 累积误差
    float p_term = pid->Kp * pid->error;                     // 比例项
    float i_term = pid->Ki * pid->integral;                  // 积分项
    float d_term = pid->Kd * (pid->error - pid->last_error); // 微分项

    // 积分限幅
    if (i_term > pid->maxIntegral)
        i_term = pid->maxIntegral;
    else if (i_term < pid->minIntegral)
        i_term = pid->minIntegral;

    // 更新上次误差
    pid->last_error = pid->error;

    float PID_Output = p_term + i_term + d_term;

    // PID输出限幅
    if (PID_Output > pid->maxOutput)
        PID_Output = pid->maxOutput;
    else if (PID_Output < pid->minOutput)
        PID_Output = pid->minOutput;

    return PID_Output;
}

/**
 * @brief  增量式PID参数初始化
 * @param  incpid PID参数结构体
 * @param  Kp 比例项系数
 * @param  Ki 积分项系数
 * @param  Kd 微分项系数
 * @param  target 目标值
 * @param  minOutput PID输出限幅-最小值
 * @param  maxOutput PID输出限幅-最大值
 * @retval 无
 */
void IncPID_Init(IncPID *incpid, float Kp, float Ki, float Kd, float target,
                 float minOutput, float maxOutput)
{
    incpid->Kp = Kp;
    incpid->Ki = Ki;
    incpid->Kd = Kd;
    incpid->target = target;
    incpid->minOutput = minOutput;
    incpid->maxOutput = maxOutput;
    incpid->error = 0.0;
    incpid->last_error = 0.0;
    incpid->prev_error = 0.0;
    incpid->IncPID_Output = 0.0;
}

/**
 * @brief  重设增量式PID目标值
 * @param  incpid PID参数结构体
 * @param  target 目标值
 * @retval 无
 */
void IncPID_ResetTarget(IncPID *incpid, float target)
{
    incpid->target = target;
}

/**
 * @brief  重设增量式PID各项系数
 * @param  pid PID参数结构体
 * @param  K_x 要修改的系数
 *      @arg 有效取值:
 *          - \b K_p : p项系数
 *          - \b K_i : i项系数
 *          - \b K_d : d项系数
 * @param  value 系数的新值
 * @retval 无
 */
void IncPID_Reset_pid(IncPID *incpid, uint8_t K_x, float value)
{
    switch (K_x)
    {
    case K_p:
        incpid->Kp = value;
        break;
    case K_i:
        incpid->Ki = value;
        break;
    case K_d:
        incpid->Kd = value;
        break;
    }
}

/**
 * @brief  增量式PID运算。
 * @param  incpid PID参数结构体
 * @param  input 当前值
 * @retval 增量式PID运算结果
 */
float IncPID_Compute(IncPID *incpid, float input)
{
    incpid->error = incpid->target - input;

    float p_term = incpid->Kp * (incpid->error - incpid->last_error);                          // 比例项
    float i_term = incpid->Ki * incpid->error;                                                 // 积分项
    float d_term = incpid->Kd * (incpid->error - 2 * incpid->last_error + incpid->prev_error); // 微分项

    // 更新误差
    incpid->prev_error = incpid->last_error;
    incpid->last_error = incpid->error;

    incpid->IncPID_Output += (p_term + i_term + d_term);

    // PID输出限幅
    if (incpid->IncPID_Output > incpid->maxOutput)
        incpid->IncPID_Output = incpid->maxOutput;
    else if (incpid->IncPID_Output < incpid->minOutput)
        incpid->IncPID_Output = incpid->minOutput;

    return incpid->IncPID_Output;
}

/**
 * @brief  指数加权移动平均滤波
 * @param  input 输入值
 * @param  filtered_value 上次滤波后的值
 * @param  alpha 滤波系数
 * @retval 滤波后结果
 */
float EWMA_filter(float input, float filtered_value, float alpha)
{
    return alpha * input + (1.0 - alpha) * filtered_value;
}
