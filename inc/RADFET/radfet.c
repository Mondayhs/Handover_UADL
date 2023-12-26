/*
 * radfet.c
 *
 *  Created on: 2023¦~12¤ë22¤é
 *      Author: OLDBOY
 */

#include ".\radfet.h"

/*==============================================================================
	RADFET Initial function
 */
void Radfet_Init(void){  //Initialize & Configure MSS GPIOs for RADFET & ADC
	MSS_GPIO_config( MSS_GPIO_14 , MSS_GPIO_OUTPUT_MODE );	// RADFET_CTRL_
	MSS_GPIO_config( MSS_GPIO_15 , MSS_GPIO_OUTPUT_MODE );
	MSS_GPIO_config( MSS_GPIO_16 , MSS_GPIO_OUTPUT_MODE );

}

/*==============================================================================
	RADFET control function
 */
void Control_R1(void){
    /* R1 */
	MSS_GPIO_set_output(MSS_GPIO_14, 1);
	MSS_GPIO_set_output(MSS_GPIO_15, 0);
	MSS_GPIO_set_output(MSS_GPIO_16, 1);
 }

void Control_R2(void){
    /* R2 */
	MSS_GPIO_set_output(MSS_GPIO_14, 1);
	MSS_GPIO_set_output(MSS_GPIO_15, 1);
	MSS_GPIO_set_output(MSS_GPIO_16, 0);


void Control_EN(void){
	    /* R2 */
	MSS_GPIO_set_output(MSS_GPIO_14, 1);
	MSS_GPIO_set_output(MSS_GPIO_15, 1);
	MSS_GPIO_set_output(MSS_GPIO_16, 1);
 }

