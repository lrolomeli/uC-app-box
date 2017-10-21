/*
 * main.c
 *
 *  Created on: 20 Oct 2017
 *      Author: lrolo
 */
#include <stdio.h>
#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "button.h"


int main(void){

	buttonsReady();

	while(TRUE){

		principal();

	}

	return 0;
}
