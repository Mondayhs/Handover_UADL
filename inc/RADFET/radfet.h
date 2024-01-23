/*
 * radfet.h
 *
 *  Created on: 2023¦~12¤ë22¤é
 *      Author: OLDBOY
 */

#ifndef INC_RADFET_RADFET_H_
	#define INC_RADFET_RADFET_H_
#include "..\..\firmware\CMSIS\m2sxxx.h"
#include "..\..\firmware\drivers\mss_gpio\mss_gpio.h"
#include "../../firmware/drivers_config/sys_config/sys_config.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>



/* radfet function */
void Radfet_Init(void);


/*==============================================================================
 Private functions.
 */
void Control_R1(void);
void Reset(void);
void ReadNOutput(void);
uint32_t Insert(uint8_t*);

#endif /* INC_RADFET_RADFET_H_ */
