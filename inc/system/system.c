
#include ".\system.h"


void Delays(uint32_t num)
{
    // 80u: 420ms    230u = 122ms    280u = 100ms (for release)
    // 2000u: 8.4ms  1000u: 16.82ms  500u: 33.63ms  80u: 210ms  18u: 934ms  17u: 989ms  16u: 1.05s(for debug)
    volatile uint32_t delay_count = SystemCoreClock / num;
    while(delay_count > 0u)
    {
        --delay_count;
    }
}



