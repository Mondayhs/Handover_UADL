/*
 * radfet.c
 *
 *  Created on: 2023嚙羯12嚙踝蕭22嚙踝蕭
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

void Control_sleep (void){
	/* sleep */
	MSS_GPIO_set_output(MSS_GPIO_14, 0);
	MSS_GPIO_set_output(MSS_GPIO_15, 0);
	MSS_GPIO_set_output(MSS_GPIO_16, 0);
 }

void Control_SCLK(void){
	int Data;
	uint8_t *_data_ = (uint8_t*)calloc(24, sizeof(uint8_t));
	for(uint8_t i=0; i<24; i++){
		MSS_GPIO_set_output(MSS_GPIO_1, 1);
		uint32_t GPIO_inputs = MSS_GPIO_get_inputs();
		if((GPIO_inputs & BIT30) == BIT30)*(_data_+i) = 1;
		else*(_data_+i) = 0;
		MSS_GPIO_set_output(MSS_GPIO_1, 0);
	}
	//有問題，無法看到是否正確結果
	uint32_t data;
	data = Insert_1bit(_data_);
	Data = ((data*2.5)/16777215);

}
//不確定是否正確
uint32_t Insert_1bit(uint8_t *_address_){
	    uint32_t value = 0;
	    for(int j=0; j<24; j++){
	        value = value << 1;
	        if(*(_address_+j)) value+=1;
	        else;
	    }
	    return value;
	}



