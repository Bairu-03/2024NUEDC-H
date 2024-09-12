#ifndef __ENCODER_H_
#define __ENCODER_H_

#include "stdint.h"

#define START 1
#define STOP  0

void Encoder_Init(void);
uint16_t getEAPulseNum(void);
uint16_t getEBPulseNum(void);
void switchCumulativePulse(uint8_t flag);
uint16_t getCumulativePulse(void);
void clearCumulativePulse(void);

#endif /* __ENCODER_H_ */
