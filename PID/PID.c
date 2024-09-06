/*
 * PID.c
 *
 *  Created on: 2024年7月17日
 *      Author: Bairu
 */

#include "PID.h"

/**
 * @brief  指数加权移动平均滤波
 * @param  input 输入值
 * @param  filtered_value 上次滤波后的输入值
 * @param  alpha 滤波系数
 * @retval 滤波后结果
 */
float exponential_filter(float input, float filtered_value, float alpha)
{
    return alpha * input + (1.0 - alpha) * filtered_value;
}

/**
 * @brief  位置式PID参数初始化
 * @param  pid PID参数结构体变量
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
    pid->filtered_input = 0.0;
}

/**
 * @brief  重设位置式PID目标值
 * @param  pid PID参数结构体变量
 * @param  target 目标值
 * @retval 无
 */
void PID_ResetTarget(PID *pid, float target)
{
    pid->target = target;
}

/**
 * @brief  重设位置式PID各项系数
 * @param  pid PID参数结构体变量
 * @param  Kx 要修改的系数
 *      @arg 有效取值:
 *          - \b 1 : Kp
 *          - \b 2 : Ki
 *          - \b 3 : Kd
 * @param  coefficient 值
 * @retval 无
 */
void PID_Reset_pid(PID *pid, uint8_t Kx, float coefficient)
{
    switch (Kx)
    {
    case 1:
        pid->Kp = coefficient;
        break;
    case 2:
        pid->Ki = coefficient;
        break;
    case 3:
        pid->Kd = coefficient;
        break;
    }
}

/**
 * @brief  位置式PID运算。
 * @param  pid PID参数结构体变量
 * @param  input 检测到的实时值
 * @retval 位置式PID运算结果
 */
float PID_Compute(PID *pid, float input)
{
    // // 对输入值进行滤波
    // pid->filtered_input = exponential_filter(input, pid->filtered_input, 0.2); // 0.2为滤波系数
    // pid->error = pid->target - pid->filtered_input;    // 计算误差

    pid->error = pid->target - input;    // 计算误差
    pid->integral += pid->error;    // 累积误差
    float p_term = pid->Kp * pid->error;    // 比例项
    float i_term = pid->Ki * pid->integral;    // 积分项
    float d_term = pid->Kd * (pid->error - pid->last_error);    // 微分项

    // 积分限幅
    if(i_term > pid->maxIntegral) i_term = pid->maxIntegral;
    else if(i_term < pid->minIntegral) i_term = pid->minIntegral;

    // 更新上次误差
    pid->last_error = pid->error;

    float PID_Output = p_term + i_term + d_term;

    // PID输出限幅
    if(PID_Output > pid->maxOutput) PID_Output = pid->maxOutput;
    else if(PID_Output < pid->minOutput) PID_Output = pid->minOutput;

    return PID_Output;
}

/**
 * @brief  增量式PID参数初始化
 * @param  incpid PID参数结构体变量
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
 * @param  incpid PID参数结构体变量
 * @param  target 目标值
 * @retval 无
 */
void IncPID_ResetTarget(IncPID *incpid, float target)
{
    incpid->target = target;
}

/**
 * @brief  重设增量式PID各项系数
 * @param  pid PID参数结构体变量
 * @param  Kx 要修改的系数
 *      @arg 有效取值:
 *          - \b 1 : Kp
 *          - \b 2 : Ki
 *          - \b 3 : Kd
 * @param  coefficient 值
 * @retval 无
 */
void IncPID_Reset_pid(IncPID *incpid, uint8_t Kx, float coefficient)
{
    switch (Kx)
    {
    case 1:
        incpid->Kp = coefficient;
        break;
    case 2:
        incpid->Ki = coefficient;
        break;
    case 3:
        incpid->Kd = coefficient;
        break;
    }
}

/**
 * @brief  增量式PID运算。
 * @param  incpid PID参数结构体变量
 * @param  input 检测到的实时值
 * @retval 增量式PID运算结果
 */
float IncPID_Compute(IncPID *incpid, float input)
{
    incpid->error = incpid->target - input;
    // incpid->error = input - incpid->target;    // 因openMV画面水平反转，故反写误差计算

    float p_term = incpid->Kp * (incpid->error - incpid->last_error);    // 比例项
    float i_term = incpid->Ki * incpid->error;    // 积分项
    float d_term = incpid->Kd * (incpid->error - 2 * incpid->last_error + incpid->prev_error);    // 微分项

    incpid->prev_error = incpid->last_error;
    incpid->last_error = incpid->error;

    incpid->IncPID_Output += (p_term + i_term + d_term);

    // PID输出限幅
    if(incpid->IncPID_Output > incpid->maxOutput) incpid->IncPID_Output = incpid->maxOutput;
    else if(incpid->IncPID_Output < incpid->minOutput) incpid->IncPID_Output = incpid->minOutput;

    return incpid->IncPID_Output;
}
