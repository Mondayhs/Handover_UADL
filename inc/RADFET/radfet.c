/*
 * radfet.c
 *
 *  Created on: 2023�~12��22��
 *      Author: OLDBOY
 */
#define BIT30 0x40000000
#include ".\radfet.h"

/*==============================================================================
	RADFET Initial function
 */
void Radfet_Init(void){  // Initialize & Configure MSS GPIOs for RADFET & ADC
// FSSW T1
	MSS_GPIO_config( MSS_GPIO_14 , MSS_GPIO_OUTPUT_MODE );	// RADFET_CTRL_R1
	MSS_GPIO_config( MSS_GPIO_16 , MSS_GPIO_OUTPUT_MODE );	// RADFET_CTRL_EN
	MSS_GPIO_config( MSS_GPIO_15, MSS_GPIO_OUTPUT_MODE ); // RADFET_CTRL_R2
	MSS_GPIO_config( MSS_GPIO_1, MSS_GPIO_OUTPUT_MODE );
	MSS_GPIO_config( MSS_GPIO_30, MSS_GPIO_INPUT_MODE );
}

/*==============================================================================
	RADFET control function
 */
void Control_R1(void){
    /* R1 */
	MSS_GPIO_set_output(MSS_GPIO_14, 1);
	MSS_GPIO_set_output(MSS_GPIO_16, 0);
	MSS_GPIO_set_output(MSS_GPIO_15, 1);
 }

void Reset(void) {
    /* R1 */
	MSS_GPIO_set_output(MSS_GPIO_14, 0);
	MSS_GPIO_set_output(MSS_GPIO_16, 0);
	MSS_GPIO_set_output(MSS_GPIO_15, 0);
 }

void ReadNOutput(void) {
	// FSW T3
		uint8_t _data_[24];
		uint32_t ans = 0;
		for (uint8_t i = 0; i < 24; i++) {
			MSS_GPIO_set_output(MSS_GPIO_1, 1);
			uint32_t GPIO_inputs = MSS_GPIO_get_inputs();
			if ((GPIO_inputs & BIT30) == BIT30) (_data_[i]) = 1;
			else (_data_[i]) = 0;
			MSS_GPIO_set_output(MSS_GPIO_1, 0);
		}
		ans = Insert(_data_);
		ans = ans * 2.5 / (16777216  - 1);
}

uint32_t Insert(uint8_t* _address_) {
	uint32_t value = 0;
	for (int j = 0; j < 24; j++) {
		value = value << 1;
		if (*(_address_ + j) ) value+= 1;
		else ;
	}
	return value;
}
