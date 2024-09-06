#ifndef __CAR_H
#define __CAR_H

#include "stdint.h"

#define Car_F 0
#define Car_L 1
#define Car_R 2
#define Car_Stop 3

void Car_Status(uint8_t Status, float leftMotorDuty, float rightMotorDuty);

#endif
