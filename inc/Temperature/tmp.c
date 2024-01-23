#include ".\tmp.h"

/*==============================================================================
	Thermistor Initial function
 */
void Tmp_Init(void){  //Initialize & Configure SetPriority & core_i2c
	/*-------------------------------------------------------------------------
     * Initialize the system tick for 10mS operation or 1 tick every 100th of
     * a second and also make sure it is lower priority than the I2C IRQs.
    */
	NVIC_SetPriority(SysTick_IRQn, 0xFFu);
	NVIC_SetPriority(UART1_IRQn, 0xFEu);
	NVIC_SetPriority(Timer1_IRQn, 0xFDu);
    SysTick_Config(MSS_SYS_M3_CLK_FREQ / 100);
	I2C_init(&g_core_i2c0, COREI2C_BASE_ADDR, COREI2C_DUMMY_ADDR, I2C_PCLK_DIV_256);

	i2c_cnt = 0;
	g_master_tx_som[0] = 0x90;		// for VIN2 = 0x90, VIN7 =0xE0
	g_master_tx_radfet[0] = 0xE0;
}

/*==============================================================================
	Thermistor control function
 */
void Read_Diode(void){
	i2c_status_t i2c_status;
	memset(_diode_data_, 0, 2);
	memset(_SOM_tmp_, 0, 2);
	memset(_RADFET_tmp_, 0, 2);

	/* Check i2c count */
	if(i2c_cnt > 300){
		I2C_init(&g_core_i2c0, COREI2C_BASE_ADDR, COREI2C_DUMMY_ADDR, I2C_PCLK_DIV_256);
		i2c_cnt = 0;
	}
	else;

	/* Read SOM temperature */
	I2C_write(&g_core_i2c0, ADC7998_SLAVE_ADDR, g_master_tx_som, 1, I2C_HOLD_BUS);
	i2c_status = I2C_wait_complete( &g_core_i2c0, I2C_TIMEOUT);
	I2C_read(&g_core_i2c0, ADC7998_SLAVE_ADDR, _SOM_tmp_, 2, I2C_RELEASE_BUS);
	i2c_status = I2C_wait_complete( &g_core_i2c0, I2C_TIMEOUT);
	if(i2c_status != 0){
		I2C_init(&g_core_i2c0, COREI2C_BASE_ADDR, COREI2C_DUMMY_ADDR, I2C_PCLK_DIV_256);
		i2c_cnt = 0;
	}
	else i2c_cnt++;

	/* Read RADFET temperature */
	I2C_write(&g_core_i2c0, ADC7998_SLAVE_ADDR, g_master_tx_radfet, 1, I2C_HOLD_BUS);
	i2c_status = I2C_wait_complete( &g_core_i2c0, I2C_TIMEOUT);
	I2C_read(&g_core_i2c0, ADC7998_SLAVE_ADDR, _RADFET_tmp_, 2, I2C_RELEASE_BUS );
	i2c_status = I2C_wait_complete( &g_core_i2c0, I2C_TIMEOUT);
	if(i2c_status != 0){
		I2C_init(&g_core_i2c0, COREI2C_BASE_ADDR, COREI2C_DUMMY_ADDR, I2C_PCLK_DIV_256);
		i2c_cnt = 0;
	}
	else i2c_cnt++;

	_diode_data_[0] = Tmp_Transform(_SOM_tmp_);
	_diode_data_[1] = Tmp_Transform(_RADFET_tmp_);
}

/*==============================================================================
	Temperature Transfer funtion
 */
int8_t Tmp_Transform(uint8_t* tmp){
	float convert = 0;
	uint16_t cal = 0;
	int8_t result = 0;

	for(uint8_t i=0; i<2; i++){
		cal = cal << 8;
		cal += tmp[i];
	}
	convert = cal%4096; //erase the first 4 blank bits
	convert = 3.3*(convert/4096); //convert to voltage data
	convert = (convert*39000)/(3.3-convert); //convert to diode data

	if(convert <= thermistor_table_[109]) result = 0x99; //Tmp too high
	else if(convert >= thermistor_table_[0]) result = 0xAA; //Tmp too low
	else{
		for(uint16_t i=0; i<110; i++){ //convert to temperature data
			if(convert > thermistor_table_[i]){
				result = i-33;
				break;
			}
			else;
		}
	}

	return result;
}

/*==============================================================================
	Thermistor Temperature Table (from -33 to 76 oC)
 */
uint32_t thermistor_table_[110] ={
	2137491, 185717, 174725, 164446, 						//-33 ~ -30
	154830, 145833, 137409, 129521, 122132, 				//-29 ~ -25
	115206, 108714, 102624, 96911, 91550,					//-24 ~ -20
	86516, 81787, 77345, 73170	,69244,						//-19 ~ -15
	65552, 62078, 58809, 55730, 52831,						//-14 ~ -10
	50099, 47524, 45097, 42808, 40648,						// -9 ~  -5
	38609, 36685, 34868, 33151, 31529,						// -4 ~   0
	29995, 28545, 27174, 25876, 24648, 						//  1 ~   5
	23485, 22384, 21340, 20352, 19414, 						//  6 ~  10
	18526, 17683, 16883, 16124, 15404, 						// 11 ~  15
	14720, 14070, 13452, 12865, 12307, 						// 16 ~  20
	11777, 11272, 10792, 10335, 9900, 						// 21 ~  25
	9473, 9066, 8680, 8312, 7962,	 						// 26 ~  30
	7628, 7310, 7008, 6719, 6444, 							// 31 ~  35
	6182, 5932, 5694, 5466, 5249, 							// 36 ~  40
	5042, 4844, 4654, 4474, 4301, 							// 41 ~  45
	4136, 3978, 3827, 3683, 3545, 							// 46 ~  50
	3412, 3286, 3165, 3049, 2938, 							// 51 ~  55
	2831, 2729, 2631, 2537, 2447, 							// 56 ~  60
	2361, 2278, 2199, 2123, 2050, 							// 61 ~  65
	1979, 1912, 1847, 1785, 1725, 							// 66 ~  70
	1667, 1612, 1559, 1508, 1459, 1411 						// 71 ~  76
};

/*==============================================================================
	Core I2C Handler set
 */
void FabricIrq0_IRQHandler(void){
    I2C_isr(&g_core_i2c0);
}

void SysTick_Handler(void) {
    I2C_system_tick(&g_core_i2c0, 2);
}
