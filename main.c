
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "firmware\CMSIS\system_m2sxxx.h"
#include "inc/RADFET/radfet.h"
#include "inc\system\system.h"


int main(){

	Radfet_Init();	//Radfet & ADC GPIO Initialize


	for (int i = 0; i < 5; i++)
	{

	    Control_R1();
	    Delays(16u);

	    Control_SCLK();
	    Delays(16u);

	    Control_sleep();
	    Delays(16u);

	    Control_R2();
	    Delays(16u);

	    Control_SCLK();
	    Delays(16u);

	    Control_sleep();
	    Delays(16u);


	    return 0;
	}

}



//#include "firmware\drivers\mss_uart\mss_uart.h"
//#define Microsemi_logo \
//"\n\r \
//** ** ******* ****** ***** **** ***** ****** ** ** ******* \n\r \
//* * * * * * * * * * * * * * * * * \n\r \
//* * * * * * ***** * * **** ****** * * * * * \n\r \
//* * * * * * * * * * * * * * * \n\r \
//* * ******* ****** * * **** ***** ****** * * ******* "
///* Main function */
//int main()
//{
//const uint8_t greeting[] = "\n\rWelcome to SmartFusion "
//"- customizable system-on-chip (cSoC)";
//
///* Initialize and configure UART0. */
//MSS_UART_init
//(
//		&g_mss_uart0,
//		MSS_UART_57600_BAUD,
//		MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
//);
///* Send the Microsemi Logo over the UART_0 */
//MSS_UART_polled_tx_string( &g_mss_uart0, (const uint8_t *)Microsemi_logo);
///* Send greeting message over the UART_0 */
//MSS_UART_polled_tx( &g_mss_uart0, greeting, sizeof(greeting) );
//while(1)
//{
//}
//return 0;
//}

