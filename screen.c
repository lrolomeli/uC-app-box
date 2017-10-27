/*
 * Screen.c
 *
 *  Created on: 23 oct. 2017
 *      Author: manuel
 */
#include "SPI.h"
#include "GPIO.h"
#include "DatatypeDefinitions.h"
#include "LCDNokia5110.h"
#include "LCDNokia5110Images.h"
#include "GlobalFunctions.h"
#include "screen.h"

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const SPI_ConfigType SPI_Config={SPI_DISABLE_FIFO,
								 SPI_LOW_POLARITY,
								 SPI_LOW_PHASE,
								 SPI_MSB,
								 SPI_0,
								 SPI_MASTER,
								 GPIO_MUX2,
								 SPI_BAUD_RATE_2,
								 SPI_FSIZE_8,
								{GPIO_D,BIT1,BIT2}
								};

/*! This array hold the initial picture that is shown in the LCD*/
extern const uint8 ITESO[504];

void Screen_Ready(){
	SPI_init(&SPI_Config); /*! Configuration function for the LCD port*/
	LCDNokia_init(); /*! Configuration function for the LCD */
}

void screen1()
{
	uint8 string1[]="VELOCIDAD"; /*! String to be printed in the LCD*/
	uint8 string2[]="80%"; /*! String to be printed in the LCD*/
	uint8 string3[]="TEMPERATURA"; /*! String to be printed in the LCD*/
	uint8 string4[]="20'C"; /*! String to be printed in the LCD*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_gotoXY(12,1); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(4,3);
			LCDNokia_sendString(string3); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(25,4);
			LCDNokia_sendString(string4); /*! It print a string stored in an array*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
}

void screen2()
{

	uint8 string1[]="1)ALARMA"; /*! String to be printed in the LCD*/
	uint8 string2[]="2)FTM TEMP"; /*! String to be printed in the LCD*/
	uint8 string3[]="3)% DE INC"; /*! String to be printed in the LCD*/
	uint8 string4[]="4)CTRL MNL"; /*! String to be printed in the LCD*/
	uint8 string5[]="5)FRECUENCIA"; /*! String to be printed in the LCD*/
	//LCDNokia_bitmap(&ITESO[0]); /*! It prints an array that hold an image, in this case is the initial picture*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_gotoXY(0,0); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(0,2);
			LCDNokia_sendString(string3); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(string4); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(0,4);
			LCDNokia_sendString(string5); /*! It print a string stored in an array*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
}

void screen3()
{
	uint8 string1[]="ALARMA"; /*! String to be printed in the LCD*/
	uint8 string2[]="30'C"; /*! String to be printed in the LCD*/
	uint8 string3[]="(-)B1 (+)B2"; /*! String to be printed in the LCD*/
	uint8 string4[]="(OK)B3"; /*! String to be printed in the LCD*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_gotoXY(20,1); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(4,3);
			LCDNokia_sendString(string3); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(20,4);
			LCDNokia_sendString(string4); /*! It print a string stored in an array*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
}

void screen4()
{
	uint8 string1[]="FORMATO TEMP"; /*! String to be printed in the LCD*/
	uint8 string2[]="TEMP = 30'C"; /*! String to be printed in the LCD*/
	uint8 string3[]="(-)B1 (+)B2"; /*! String to be printed in the LCD*/
	uint8 string4[]="(OK)B3"; /*! String to be printed in the LCD*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_gotoXY(0,1); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(5,2);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(4,3);
			LCDNokia_sendString(string3); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(20,4);
			LCDNokia_sendString(string4); /*! It print a string stored in an array*/
     		LCDNokia_clear();/*! It clears the information printed in the LCD*/
}

void screen5()
{
	uint8 string1[]="FORMATO TEMP"; /*! String to be printed in the LCD*/
	uint8 string2[]="TEMP = 30'F"; /*! String to be printed in the LCD*/
	uint8 string3[]="(-)B1 (+)B2"; /*! String to be printed in the LCD*/
	uint8 string4[]="(OK)B3"; /*! String to be printed in the LCD*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_gotoXY(0,1); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(5,2);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(4,3);
			LCDNokia_sendString(string3); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(20,4);
			LCDNokia_sendString(string4); /*! It print a string stored in an array*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
}

void screen6()
{
	uint8 string1[]="% DE DECRE"; /*! String to be printed in the LCD*/
	uint8 string2[]="15%"; /*! String to be printed in the LCD*/
	uint8 string3[]="(-)B1 (+)B2"; /*! String to be printed in the LCD*/
	uint8 string4[]="(OK)B3"; /*! String to be printed in the LCD*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_gotoXY(8,1); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(30,2);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(4,3);
			LCDNokia_sendString(string3); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(20,4);
			LCDNokia_sendString(string4); /*! It print a string stored in an array*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
}

void screen7()
{
	uint8 string1[]="% DE INCRE"; /*! String to be printed in the LCD*/
	uint8 string2[]="15%"; /*! String to be printed in the LCD*/
	uint8 string3[]="(-)B1 (+)B2"; /*! String to be printed in the LCD*/
	uint8 string4[]="(OK)B3"; /*! String to be printed in the LCD*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_gotoXY(8,1); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(30,2);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(4,3);
			LCDNokia_sendString(string3); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(20,4);
			LCDNokia_sendString(string4); /*! It print a string stored in an array*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
}

void screen8()
{
	uint8 string1[]="CTRL MNL"; /*! String to be printed in the LCD*/
	uint8 string2[]="50%"; /*! String to be printed in the LCD*/
	uint8 string3[]="(1)B1 (0)B2"; /*! String to be printed in the LCD*/
	uint8 string4[]="(OK)B3"; /*! String to be printed in the LCD*/
	uint8 string5[]="(-)B4 (+)B5"; /*! String to be printed in the LCD*/
	LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_gotoXY(12,0); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(30,1);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(4,2);
			LCDNokia_sendString(string3); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(20,3);
			LCDNokia_sendString(string4); /*! It print a string stored in an array*/
     		LCDNokia_gotoXY(4,4);
			LCDNokia_sendString(string5); /*! It print a string stored in an array*/
			LCDNokia_clear();/*! It clears the information printed in the LCD*/

}
