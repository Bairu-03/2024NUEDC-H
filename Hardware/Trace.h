#ifndef __TRACE_H
#define __TRACE_H

#include "stdint.h"

// 检测到黑线值为1
uint8_t get_TL3(void);  // PA21 左3 
uint8_t get_TL2(void);  // PA22 左2
uint8_t get_TL1(void);  // PA23 左1
uint8_t get_TM(void);  // PA24 中间
uint8_t get_TR1(void);  // PA25 右1
uint8_t get_TR2(void);  // PA26 右2
uint8_t get_TR3(void);  // PA27 右3
uint8_t get_T_ALL(void);  // 获取所有红外对管状态，高位为左，低位为右: 11111
char get_Terror(void);

#endif
