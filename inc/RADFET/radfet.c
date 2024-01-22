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
	MSS_GPIO_config( MSS_GPIO_15 , MSS_GPIO_OUTPUT_MODE );	// RADFET_CTRL_
	MSS_GPIO_config( MSS_GPIO_16 , MSS_GPIO_OUTPUT_MODE );	// RADFET_CTRL_

}

/*==============================================================================
	RADFET control function
 */
void Control_R1(void){
    /* R1 */
	MSS_GPIO_set_output(MSS_GPIO_14, 1);//CTRL_EN
	MSS_GPIO_set_output(MSS_GPIO_15, 0);//CTRL_R2
	MSS_GPIO_set_output(MSS_GPIO_16, 1);//CTRL_R1

 }
 void Control_R2(void){
    /* R2 */
	MSS_GPIO_set_output(MSS_GPIO_14, 1);//CTRL_EN
	MSS_GPIO_set_output(MSS_GPIO_15, 1);//CTRL_R2
	MSS_GPIO_set_output(MSS_GPIO_16, 0);//CTRL_R1

 }
 void Control_Zero(void){
    /* return to zero */
	MSS_GPIO_set_output(MSS_GPIO_14, 0);//CTRL_EN
	MSS_GPIO_set_output(MSS_GPIO_15, 0);//CTRL_R2
	MSS_GPIO_set_output(MSS_GPIO_16, 0);//CTRL_R1

 }
