#ifndef _MINE_CONTROL_H_
#define _MINE_CONTROL_H_

#include "sys.h"


void MineMotor_Init(void);
void SetMineMotorSpeed_WithRamp(uint8_t num, int16_t TargetSpeed);

void RescueTest(void);


#endif


