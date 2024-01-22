/*
 * radfet.c
 *
 *  Created on: 2023�~12��22��
 *      Author: OLDBOY
 */

#include ".\radfet.h"

/*==============================================================================
	RADFET Initial function
 */

void Radfet_Init(void){  //Initialize & Configure MSS GPIOs for RADFET & ADC
	MSS_GPIO_config( MSS_GPIO_14 , MSS_GPIO_OUTPUT_MODE );	// RADFET_CTRL_EN
	MSS_GPIO_config( MSS_GPIO_15 , MSS_GPIO_OUTPUT_MODE );  //R2
	MSS_GPIO_config( MSS_GPIO_16 , MSS_GPIO_OUTPUT_MODE );  //R1
	MSS_GPIO_config( MSS_GPIO_1 , MSS_GPIO_OUTPUT_MODE );
	MSS_GPIO_config( MSS_GPIO_30 , MSS_GPIO_INPUT_MODE );
}


/*==============================================================================
	RADFET control function
 */
void Control_R1(void){
    /* R1 */
	MSS_GPIO_set_output(MSS_GPIO_14, 1);
	MSS_GPIO_set_output(MSS_GPIO_15, 1);
	MSS_GPIO_set_output(MSS_GPIO_16, 0);
 }

void Control_R2(void){
    /* R2 */
	MSS_GPIO_set_output(MSS_GPIO_14, 0);
	MSS_GPIO_set_output(MSS_GPIO_15, 1);
	MSS_GPIO_set_output(MSS_GPIO_16, 1);
}

void Control_Zero(void){
	/* reset */
	MSS_GPIO_set_output(MSS_GPIO_14, 0);
	MSS_GPIO_set_output(MSS_GPIO_15, 0);
	MSS_GPIO_set_output(MSS_GPIO_16, 0);
 }

