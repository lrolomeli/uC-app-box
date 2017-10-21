/*
 * button.c
 *
 *  Created on: 19 Oct 2017
 *      Author: lrolo
 */
#include <stdio.h>
#include "MK64F12.h"
#include "GPIO.h"
#include "button.h"
#include "NVIC.h"
#include "PIT.h"

const button_ConfigType button_Config = {GPIO_INPUT,
										pinControlRegisterPORTBSW,
										{GPIO_B,BIT20,BIT9,BIT3,BIT10,BIT11},
										PIT_CH0_IRQ,
										PORTB_IRQ,
										PRIORITY_7,
										PRIORITY_8,
										PRIORITY_12
										};

void buttonsReady(void)
{
	button_init(&button_Config); /*! Configuration function  */
	PIT_delay(PIT_0, SYSTEMCLOCK, 0.0001);
}

void principal(void){
	if(PIT_getIntrStatus())
	if(TRUE == GPIO_getIRQStatus(button_Config.GPIOForButton.GPIO_portName)){
		printf("hello world\n");
		GPIO_clearIRQStatus(button_Config.GPIOForButton.GPIO_portName);
		PIT_delay(PIT_0, SYSTEMCLOCK, .005);
	}
}


void button_init(const button_ConfigType* button_Config)
/**This function contains all the initialisation of the button organised as an structure*/
{
	GPIO_clockGating(button_Config->GPIOForButton.GPIO_portName);
	PIT_clockGating();
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button1, & (button_Config->pinControlRegisterPORTB));
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button2, & (button_Config->pinControlRegisterPORTB));
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button3, & (button_Config->pinControlRegisterPORTB));
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button4, & (button_Config->pinControlRegisterPORTB));
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button5, & (button_Config->pinControlRegisterPORTB));
	GPIO_clearIRQStatus(button_Config->GPIOForButton.GPIO_portName);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button1);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button2);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button3);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button4);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button5);
	NVIC_setBASEPRI_threshold(button_Config->GlobalPriority);
	NVIC_enableInterruptAndPriority(button_Config->GPIO_ISR, button_Config->GPIO_Priority);
	NVIC_enableInterruptAndPriority(button_Config->PIT_ISR, button_Config->PIT_Priority);
	EnableInterrupts;
}
