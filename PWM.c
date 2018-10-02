/*
 * PWM.c
 *
 *  Created on: 26 oct. 2017
 *      Author: manuel
 */

#include "FlexTimer.h"
#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "FlexTimer.h"
#include "PIT.h"
#include "NVIC.h"

sint16 dutyCycle = 204;
uint8 inputValueA = 0, inputPortC = 0;

const FTM_ConfigType FTM_Config2={FTM_3,
								 FTM_ENABLE,
								 FLEX_TIMER_CLKS_2,
								 FLEX_TIMER_PS_8,
								 FLEX_TIMER_Cn_4
								};

void Flex_Init_PWM_Ready(void){
	/**Clock gating for port A and C*/
	PIT_clockGating();
	SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC;
	PORTC->PCR[BIT8] = PORT_PCR_MUX(0x3);

	//EnableInterrupts;
	FTM_PWM_Init(&FTM_Config2);
	NVIC_enableInterruptAndPriority(PIT_CH0_IRQ, PRIORITY_8);
	EnableInterrupts;
	PIT_delay(PIT_0, SYSTEMCLOCK, 0.00001);
}

void PWM_Slow(uint8 parameter){
	if(PIT_getIntrStatus()){
		if(dutyCycle > 22){
			dutyCycle = dutyCycle - 12.33*parameter;
			FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, dutyCycle);
			PIT_delay(PIT_0, SYSTEMCLOCK, 0.25);
		}
		else{
			dutyCycle = 22;
			PIT_delay(PIT_0, SYSTEMCLOCK, 0.25);
		}
	}
}


void PWM_Fast(uint8 parameter){
	if(PIT_getIntrStatus()){
		if(dutyCycle < 240){
			dutyCycle = dutyCycle + 12.33*parameter;
			FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, dutyCycle);
			PIT_delay(PIT_0, SYSTEMCLOCK, 0.25);
		}
		else{
			dutyCycle = 240;
			PIT_delay(PIT_0, SYSTEMCLOCK, 0.25);
		}
	}
}

void TemperatureControllingMotor(){

	switch(getCelsius()){
	case 23:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 235);
		break;
	case 24:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 235);
		break;
	case 25:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, dutyCycle);
		break;
	case 26:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, dutyCycle);
		break;
	case 27:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 166);
		break;
	case 28:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 166);
		break;
	case 29:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 128);
		break;
	case 30:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 128);
		break;
	case 31:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 89);
		break;
	case 32:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 89);
		break;
	case 33:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 51);
		break;
	case 34:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 51);
		break;
	case 35:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 13);
		break;
	default:
		FTM_updateChValue(FTM_3, FLEX_TIMER_Cn_4, 204);
		break;

	}

}
