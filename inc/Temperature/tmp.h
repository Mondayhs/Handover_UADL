#ifndef _TEMPERATURE_FUN_H_
	#define _TEMPERATURE_FUN_H_

#include "..\Command/command.h"
#include "..\..\firmware\CMSIS\m2sxxx.h"
#include "..\..\firmware\drivers\mss_gpio\mss_gpio.h"
#include "..\..\firmware\drivers\mss_uart\mss_uart.h"
#include "..\..\firmware\drivers\CoreI2C\core_i2c.h"
#include "../../firmware/drivers_config/sys_config/sys_config.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* core i2c define */
#define  	I2C_TIMEOUT		2u
#define COREI2C_BASE_ADDR	0x50000000
#define COREI2C_DUMMY_ADDR 	0xFF
#define ADC7998_SLAVE_ADDR	0x20

/* thermistor funciton */
void Tmp_Init(void);
int8_t Tmp_Transform(uint8_t* tmp);
uint32_t thermistor_table_[110];

/* thermistor variables */
int8_t _diode_data_[2];			// SOM_tmp = _diode_data_[0], RADFET_tmp = _diode_data_[1]
uint8_t _SOM_tmp_[2];
uint8_t _RADFET_tmp_[2];
uint8_t i2c_cnt;				//Count for i2c use time
uint8_t g_master_tx_som[1];		// for VIN2 = 0x90, VIN7 =0xE0
uint8_t g_master_tx_radfet[1];

/* core i2c declaration */
i2c_instance_t g_core_i2c0;

/*==============================================================================
 Private functions.
 */
void Read_Diode(void);
		/*
			@Discreption
				This function will control   AD7998 to do "analog to Digital" and to read RADFET temperature.
				Useing I2C to contol and recieve.
			@Input
				none

			@Ouput
						//RADFET temperature
		*/

#endif /* _TEMPERATURE_FUN_H_ */
