#ifndef __ENCODER_H_
#define __ENCODER_H_

#include "stdint.h"

extern uint8_t Enable_CP;  // 为1时启动PA8、PA9引脚输入脉冲累计
extern uint16_t CumulativePulsePA8, CumulativePulsePA9; // 脉冲累计值

void Encoder_Init(void);
uint16_t getEAPulseNum(void);
uint16_t getEBPulseNum(void);

#endif /* __ENCODER_H_ */