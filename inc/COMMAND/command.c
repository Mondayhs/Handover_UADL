
#include ".\command.h"
#include "..\system\system.h"

//void Delays(uint32_t num)
//{
//    // 80u: 420ms    230u = 122ms    280u = 100ms (for release)
//    // 2000u: 8.4ms  1000u: 16.82ms  500u: 33.63ms  80u: 210ms  18u: 934ms  17u: 989ms  16u: 1.05s(for debug)
//    volatile uint32_t delay_count = SystemCoreClock / num;
//    while(delay_count > 0u)
//    {
//        --delay_count;
//    }
//}


int main(void)
{
	uint8_t HK_CMD[3] = {0x11, 0x13, 0x10};
    uint8_t message[12] = "Hello World";
     MSS_UART_init(&g_mss_uart1,
                   MSS_UART_921600_BAUD,
                   MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

     for (int i = 0; i < 5; i++)
     {
     MSS_UART_polled_tx(&g_mss_uart1, message, sizeof(message));
     Delays(16u);
     }

     return(0);
}
