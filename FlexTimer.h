/**
	\file
	\brief
		This is the header file for the FlexTimer divice driver.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_


#include "MK64F12.h"
#include "DataTypeDefinitions.h"



#define FLEX_TIMER_0_CLOCK_GATING 0x01000000
#define FLEX_TIMER_1_CLOCK_GATING 0x02000000
#define FLEX_TIMER_2_CLOCK_GATING 0x04000000
#define FLEX_TIMER_3_CLOCK_GATING 0x02000000

#define FLEX_TIMER_FAULTIE  0x80
#define FLEX_TIMER_FAULTM_0   0x00
#define FLEX_TIMER_FAULTM_1   0x20
#define FLEX_TIMER_FAULTM_2   0x40
#define FLEX_TIMER_FAULTM_3   0x60
#define FLEX_TIMER_CAPTEST  0x10
#define FLEX_TIMER_PWMSYNC  0x08
#define FLEX_TIMER_WPDIS    0x04
#define FLEX_TIMER_INIT     0x02
#define FLEX_TIMER_FTMEN    0x01

#define FLEX_TIMER_TOF     0x80
#define FLEX_TIMER_TOIE    0x40
#define FLEX_TIMER_CPWMS   0x20



#define FLEX_TIMER_PWMLOAD_CH0 0x01
#define FLEX_TIMER_PWMLOAD_CH1 0x02
#define FLEX_TIMER_PWMLOAD_CH2 0x04
#define FLEX_TIMER_PWMLOAD_CH3 0x08
#define FLEX_TIMER_PWMLOAD_CH4 0x10
#define FLEX_TIMER_PWMLOAD_CH5 0x20
#define FLEX_TIMER_PWMLOAD_CH6 0x40
#define FLEX_TIMER_PWMLOAD_CH7 0x80
#define FLEX_TIMER_LDOK        0x200


#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80

#define  MOD_MAX_COUNT   65536


/*! These constants are used to select an specific port in the different API functions*/
typedef enum{FTM_0, /*!< Definition to select FTM 0 */
			 FTM_1, /*!< Definition to select FTM 1 */
			 FTM_2, /*!< Definition to select FTM 2 */
			 FTM_3 /*!< Definition to select FTM 3 */
			} FTM_ChannelType;

/*! These constants are used to select an specific port in the different API functions*/
typedef enum{FTM_DISABLE, /*!< FTM WRITE ENABLE */
			 FTM_ENABLE /*!< FTM WRITE DISABLE */
			} FTM_Enable;


/*! These constants are used to select an specific port in the different API functions*/
typedef enum{FLEX_TIMER_CLKS_0 = 0x00,
			 FLEX_TIMER_CLKS_1 = 0x08,
			 FLEX_TIMER_CLKS_2 = 0x10,
			 FLEX_TIMER_CLKS_3 = 0x18
			} FTM_ClkSource;

typedef enum{FLEX_TIMER_PS_1,
			 FLEX_TIMER_PS_2,
			 FLEX_TIMER_PS_4,
			 FLEX_TIMER_PS_8,
			 FLEX_TIMER_PS_16,
			 FLEX_TIMER_PS_32,
			 FLEX_TIMER_PS_64,
			 FLEX_TIMER_PS_128
			} FTM_Prescaler;

typedef enum{FLEX_TIMER_Cn_0,
			 FLEX_TIMER_Cn_1,
			 FLEX_TIMER_Cn_2,
			 FLEX_TIMER_Cn_3,
			 FLEX_TIMER_Cn_4,
			 FLEX_TIMER_Cn_5,
			 FLEX_TIMER_Cn_6,
			 FLEX_TIMER_Cn_7
			} FTM_CnType;



typedef struct{

	FTM_ChannelType FTM_Channel;
	FTM_Enable FTM_En;
	FTM_ClkSource FLEX_TIMER_CLKS;
	FTM_Prescaler FLEX_TIMER_PS;
	FTM_CnType FTM_Cn;

}FTM_ConfigType;


void FlexTimer_Init(void);
void FTM_ClockGatting(FTM_ChannelType channel);
void FTM_enableWrite(FTM_ChannelType channel, FTM_Enable writeEnable);
void FTM_enableFTM(FTM_ChannelType channel, FTM_Enable FTMEN);
void FTM_resetCount(FTM_ChannelType channel);
void FTM_setCountOverflow(FTM_ChannelType channel, uint32 contOVF);
void FTM_setInitialCountValue(FTM_ChannelType channel, uint32 initValue);
void FTM_setClkSource(FTM_ChannelType channel, FTM_ClkSource clkSource);
void FTM_setPrescaler(FTM_ChannelType channel, FTM_Prescaler PS);
void FTM_enableOVFInterrupt(FTM_ChannelType channel, FTM_Enable interruptEnable);
void FTM_setCnPWM(FTM_ChannelType channel, FTM_CnType cnChannel);
void FTM_setCnInputCapture(FTM_ChannelType channel, FTM_CnType cnChannel);
void FTM_enableCnInterrupt(FTM_ChannelType channel, FTM_CnType cnChannel, FTM_Enable interruptEnable);
void FTM_InputCapture_Init(const FTM_ConfigType* FTMconfig);

#endif /* FLEXTIMER_H_ */
