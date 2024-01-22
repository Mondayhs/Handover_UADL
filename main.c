// 20231225
// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <string.h>
// #include "inc/RADFET/radfet.h"
// #include "firmware\CMSIS\system_m2sxxx.h"

// void delay(uint32_t num){
//     // 80u: 420ms    230u = 122ms    280u = 100ms (for release)
//     // 2000u: 8.4ms  1000u: 16.82ms  500u: 33.63ms  80u: 210ms  18u: 934ms  17u: 989ms  16u: 1.05s(for debug)
//     volatile uint32_t delay_count = SystemCoreClock / num;
//     while(delay_count > 0u)
//     {
//         --delay_count;
//     }
// }

// int main(){

// 	Radfet_Init();	//Radfet & ADC GPIO Initialize

// 	for (int i = 0; i < 5; i++)
// 	{
// 		Control_sleep();
// 		delay(16u);

// 		Control_R1();
// 		delay(16u);

// 		Control_sleep();
// 		delay(16u);

// 		Control_R2();
// 		delay(16u);

// 	    return 0;
// 	}

// }


// 20240102
#include "firmware\drivers\mss_uart\mss_uart.h"
#define Microsemi_logo \
"\n\r \
** ** ******* ****** ***** **** ***** ****** ** ** ******* \n\r \
* * * * * * * * * * * * * * * * * \n\r \
* * * * * * ***** * * **** ****** * * * * * \n\r \
* * * * * * * * * * * * * * * \n\r \
* * ******* ****** * * **** ***** ****** * * ******* "
/* Main function */
int main()
{
const uint8_t greeting[] = "\n\rWelcome to SmartFusion "
"- customizable system-on-chip (cSoC)";
/* Initialize and configure UART0. */
MSS_UART_init
(
&g_mss_uart0,
MSS_UART_57600_BAUD,
MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
);
/* Send the Microsemi Logo over the UART_0 */
MSS_UART_polled_tx_string( &g_mss_uart0, (const uint8_t *)Microsemi_logo);
/* Send greeting message over the UART_0 */
MSS_UART_polled_tx( &g_mss_uart0, greeting, sizeof(greeting) );
while(1)
{
}
return 0;
}
