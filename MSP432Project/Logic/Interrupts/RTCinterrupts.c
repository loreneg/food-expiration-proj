#include "interrupts.h"

void RTC_C_IRQHandler(void)
{
    uint32_t status;

    status = RTC_C_getEnabledInterruptStatus();
    RTC_C_clearInterruptFlag(status);
    //interrupt handler for RTC event
    //called every time a new day arrives
    if (status & RTC_C_TIME_EVENT_INTERRUPT) //if there's expired food, led becomes red
    {
        expiredFood();
    }
}
