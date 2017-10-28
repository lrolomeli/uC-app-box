/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */

#include "FlexTimer.h"
#include "MK64F12.h"
#include "GPIO.h"
#include <stdio.h>

const FTM_ConfigType FTM_Config1={FTM_0,
								 FTM_ENABLE,
								 FLEX_TIMER_CLKS_1,
								 FLEX_TIMER_PS_1,
								 FLEX_TIMER_Cn_0
								};

volatile uint16 OvTimesVar = 0;
uint8 insideOfPeriodFlag = FALSE;

volatile uint16 temp[2]={0,0};
volatile uint8 i = 0;
volatile float period=0;
volatile float fperiod=0;
volatile float frequency=0;

void FTM0_IRQHandler(void)
{

	if(FTM0->SC & FTM_SC_TOF_MASK)
	{
		if(insideOfPeriodFlag)
			OvTimesVar++;
		FTM0->SC &= ~(FTM_SC_TOF_MASK);
	}


	if(FTM0->CONTROLS[0].CnSC & FTM_CnSC_CHF_MASK)
	{
		temp[i%2] = (FTM0->CONTROLS[0].CnV & FTM_CnV_VAL_MASK);//se va a guardar el dato en dicho flanco del counter del timer
		if(!(i%2))//si es el primer flanco
			insideOfPeriodFlag=TRUE;
		else if(i%2)
		{
			insideOfPeriodFlag=FALSE;
			period = (((float)(temp[1]-temp[0])) + ((float)(OvTimesVar * MOD_MAX_COUNT)));
			fperiod =(float)((float)period /(float)21000000);
			frequency = 1.0 / fperiod;
			printf("%d\n",(uint16)frequency);
			temp[1]=0;
			temp[0]=0;
			OvTimesVar=0;
		}
		i++;
		if(i==2)
			i=0;

		FTM0->CONTROLS[0].CnSC &= ~(FTM_CnSC_CHF_MASK);
	}

}



void FlexTimer_Init(void)
{

	FTM_InputCapture_Init(&FTM_Config1);

	/** Clock gating for the FlexTimer 0*/
	//FTM_ClockGatting(FTM_0);

	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
	* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
	//FTM_enableWrite(FTM_0, FTM_ENABLE);

	//FTM_enableFTM(FTM_0, FTM_ENABLE);

	/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
	//FTM0->CONF |= FTM_CONF_BDMMODE(3);

	//FTM_setCountOverflow(FTM_0, FTM_MOD_MOD_MASK);

	//USES THE SYSTEM CLOCK / PRESCALER 1
	//FTM_enableOVFInterrupt(FTM_0, FTM_ENABLE);
	//FTM_setClkSource(FTM_0, FLEX_TIMER_CLKS_1);
	//FTM_setPrescaler(FTM_0, FLEX_TIMER_PS_1);

	//FTM0->SC &= ~(FTM_SC_CPWMS_MASK);

	//The Input Capture mode is selected when:
	//• DECAPEN = 0
	//• COMBINE = 0
	//• CPWMS = 0
	//FTM0->COMBINE &= ~(FTM_COMBINE_COMBINE0_MASK);
	//FTM0->COMBINE &= ~(FTM_COMBINE_DECAPEN0_MASK);

	//• MSnB:MSnA = 0:0, and
	//• ELSnB:ELSnA ≠ 0:0
	//• ELSnB:ELSnA = 0:1 for rising edge
	//FTM0->CONTROLS[0].CnSC &= ~(FTM_CnSC_MSA_MASK);
	//FTM0->CONTROLS[0].CnSC &= ~(FTM_CnSC_MSB_MASK);
	//FTM0->CONTROLS[0].CnSC |= FTM_CnSC_ELSA_MASK;
	//FTM0->CONTROLS[0].CnSC &= ~(FTM_CnSC_ELSB_MASK);

	//FTM_setCnInputCapture(FTM_0, FLEX_TIMER_Cn_0);

	//ENABLES INTERRUPT CHANNEL REQUEST OF FLEX TIMER
	//FTM_enableCnInterrupt(FTM_0, FLEX_TIMER_Cn_0, FTM_ENABLE);

}

void FTM_ClockGatting(FTM_ChannelType channel)
{
	switch(channel)
	{
	case FTM_0:
		SIM->SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;
		break;
	case FTM_1:
		SIM->SCGC6 |= FLEX_TIMER_1_CLOCK_GATING;
		break;
	case FTM_2:
		SIM->SCGC6 |= FLEX_TIMER_2_CLOCK_GATING;
		break;
	default:
		SIM->SCGC3 |= FLEX_TIMER_3_CLOCK_GATING;
		break;
	}
}

void FTM_enableWrite(FTM_ChannelType channel, FTM_Enable writeEnable)
{
	switch(channel)
	{
	case FTM_0:
		if(writeEnable)
			FTM0->MODE |= FTM_MODE_WPDIS_MASK;

		else
			FTM0->MODE &= ~(FTM_MODE_WPDIS_MASK);
		break;

	case FTM_1:
		if(writeEnable)
			FTM1->MODE |= FTM_MODE_WPDIS_MASK;
		else
			FTM1->MODE &= ~(FTM_MODE_WPDIS_MASK);
		break;

	case FTM_2:
		if(writeEnable)
			FTM2->MODE |= FTM_MODE_WPDIS_MASK;
		else
			FTM2->MODE &= ~(FTM_MODE_WPDIS_MASK);
		break;

	default:
		if(writeEnable)
			FTM3->MODE |= FTM_MODE_WPDIS_MASK;
		else
			FTM3->MODE &= ~(FTM_MODE_WPDIS_MASK);
		break;
	}
}

void FTM_enableFTM(FTM_ChannelType channel, FTM_Enable FTMEN)
{
	switch(channel)
		{
		case FTM_0:
			if(FTMEN)
				FTM0->MODE |= FTM_MODE_FTMEN_MASK;
			else
				FTM0->MODE &= ~(FTM_MODE_FTMEN_MASK);
			break;

		case FTM_1:
			if(FTMEN)
				FTM1->MODE |= FTM_MODE_FTMEN_MASK;
			else
				FTM1->MODE &= ~(FTM_MODE_FTMEN_MASK);
			break;

		case FTM_2:
			if(FTMEN)
				FTM2->MODE |= FTM_MODE_FTMEN_MASK;
			else
				FTM2->MODE &= ~(FTM_MODE_FTMEN_MASK);
			break;

		default:
			if(FTMEN)
				FTM3->MODE |= FTM_MODE_FTMEN_MASK;
			else
				FTM3->MODE &= ~(FTM_MODE_FTMEN_MASK);
			break;
		}
}

void FTM_resetCount(FTM_ChannelType channel)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->CNT = FALSE;
			break;

		case FTM_1:
			FTM1->CNT = FALSE;
			break;

		case FTM_2:
			FTM2->CNT = FALSE;
			break;

		default:
			FTM3->CNT = FALSE;
			break;

		}
}

void FTM_setCountOverflow(FTM_ChannelType channel, uint32 contOVF)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->MOD = contOVF & FTM_MOD_MOD_MASK;
			break;

		case FTM_1:
			FTM1->MOD = contOVF & FTM_MOD_MOD_MASK;
			break;

		case FTM_2:
			FTM2->MOD = contOVF & FTM_MOD_MOD_MASK;
			break;

		default:
			FTM3->MOD = contOVF & FTM_MOD_MOD_MASK;
			break;
		}
}

void FTM_setInitialCountValue(FTM_ChannelType channel, uint32 initValue)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->CNTIN = initValue & FTM_CNTIN_INIT_MASK;
			break;

		case FTM_1:
			FTM1->CNTIN = initValue & FTM_CNTIN_INIT_MASK;
			break;

		case FTM_2:
			FTM2->CNTIN = initValue & FTM_CNTIN_INIT_MASK;
			break;

		default:
			FTM3->CNTIN = initValue & FTM_CNTIN_INIT_MASK;
			break;
		}
}

void FTM_setClkSource(FTM_ChannelType channel, FTM_ClkSource clkSource)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->SC |= (clkSource & FTM_SC_CLKS_MASK);
			break;

		case FTM_1:
			FTM1->SC |= (clkSource & FTM_SC_CLKS_MASK);
			break;

		case FTM_2:
			FTM2->SC |= (clkSource & FTM_SC_CLKS_MASK);
			break;

		default:
			FTM3->SC |= (clkSource & FTM_SC_CLKS_MASK);
			break;
		}
}

void FTM_setPrescaler(FTM_ChannelType channel, FTM_Prescaler PS)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->SC |= (PS & FTM_SC_PS_MASK);
			break;

		case FTM_1:
			FTM1->SC |= (PS & FTM_SC_PS_MASK);
			break;

		case FTM_2:
			FTM2->SC |= (PS & FTM_SC_PS_MASK);
			break;

		default:
			FTM3->SC |= (PS & FTM_SC_PS_MASK);
			break;
		}
}

void FTM_enableOVFInterrupt(FTM_ChannelType channel, FTM_Enable interruptEnable){
	switch(channel)
	{
	case FTM_0:
		if(interruptEnable)
			FTM0->SC |= FTM_SC_TOIE_MASK;
		else
			FTM0->SC &= ~(FTM_SC_TOIE_MASK);
		break;

	case FTM_1:
		if(interruptEnable)
			FTM1->SC |= FTM_SC_TOIE_MASK;
		else
			FTM1->SC &= ~(FTM_SC_TOIE_MASK);
		break;

	case FTM_2:
		if(interruptEnable)
			FTM2->SC |= FTM_SC_TOIE_MASK;
		else
			FTM2->SC &= ~(FTM_SC_TOIE_MASK);
		break;

	default:
		if(interruptEnable)
			FTM3->SC |= FTM_SC_TOIE_MASK;
		else
			FTM3->SC &= ~(FTM_SC_TOIE_MASK);
		break;
	}
}

void FTM_setCnPWM(FTM_ChannelType channel, FTM_CnType cnChannel)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->CONTROLS[cnChannel].CnSC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
			break;

		case FTM_1:
			FTM1->CONTROLS[cnChannel].CnSC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
			break;

		case FTM_2:
			FTM2->CONTROLS[cnChannel].CnSC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
			break;

		default:
			FTM3->CONTROLS[cnChannel].CnSC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
			break;
		}
}

void FTM_setCnInputCapture(FTM_ChannelType channel, FTM_CnType cnChannel)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->CONTROLS[cnChannel].CnSC |= FTM_CnSC_ELSA_MASK;
			break;

		case FTM_1:
			FTM1->CONTROLS[cnChannel].CnSC |= FTM_CnSC_ELSA_MASK;
			break;

		case FTM_2:
			FTM2->CONTROLS[cnChannel].CnSC |= FTM_CnSC_ELSA_MASK;
			break;

		default:
			FTM3->CONTROLS[cnChannel].CnSC |= FTM_CnSC_ELSA_MASK;
			break;
		}
}

void FTM_enableCnInterrupt(FTM_ChannelType channel, FTM_CnType cnChannel, FTM_Enable interruptEnable){
	switch(channel)
	{
	case FTM_0:
		if(interruptEnable)
			FTM0->CONTROLS[cnChannel].CnSC |= FTM_CnSC_CHIE_MASK;
		else
			FTM0->CONTROLS[cnChannel].CnSC &= ~(FTM_CnSC_CHIE_MASK);
		break;

	case FTM_1:
		if(interruptEnable)
			FTM1->CONTROLS[cnChannel].CnSC |= FTM_CnSC_CHIE_MASK;
		else
			FTM1->CONTROLS[cnChannel].CnSC &= ~(FTM_CnSC_CHIE_MASK);
		break;

	case FTM_2:
		if(interruptEnable)
			FTM2->CONTROLS[cnChannel].CnSC |= FTM_CnSC_CHIE_MASK;
		else
			FTM2->CONTROLS[cnChannel].CnSC &= ~(FTM_CnSC_CHIE_MASK);
		break;

	default:
		if(interruptEnable)
			FTM3->CONTROLS[cnChannel].CnSC |= FTM_CnSC_CHIE_MASK;
		else
			FTM3->CONTROLS[cnChannel].CnSC &= ~(FTM_CnSC_CHIE_MASK);
		break;
	}
}

void FTM_InputCapture_Init(const FTM_ConfigType* FTMconfig)
{
	FTM_ClockGatting(FTMconfig->FTM_Channel);
	FTM_enableWrite(FTMconfig->FTM_Channel, FTMconfig->FTM_En);
	FTM_enableFTM(FTMconfig->FTM_Channel, FTMconfig->FTM_En);
	FTM_setCountOverflow(FTMconfig->FTM_Channel, FTM_MOD_MOD_MASK);
	FTM_enableOVFInterrupt(FTMconfig->FTM_Channel, FTMconfig->FTM_En);
	FTM_setClkSource(FTMconfig->FTM_Channel, FTMconfig->FLEX_TIMER_CLKS);
	FTM_setPrescaler(FTMconfig->FTM_Channel, FTMconfig->FLEX_TIMER_PS);
	FTM_setCnInputCapture(FTMconfig->FTM_Channel, FTMconfig->FTM_Cn);
	FTM_enableCnInterrupt(FTMconfig->FTM_Channel, FTMconfig->FTM_Cn, FTMconfig->FTM_En);
}
