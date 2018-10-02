/*
 * PWM.h
 *
 *  Created on: 25 oct. 2017
 *      Author: manuel
 */

#ifndef PWM_H_
#define PWM_H_

#include "FlexTimer.h"
#include "MK64F12.h"

void Flex_Init_PWM_Ready(void);
void PWM_Slow(uint8 parameter);
void PWM_Fast(uint8 parameter);
void TemperatureControllingMotor();

#endif /* PWM_H_ */
