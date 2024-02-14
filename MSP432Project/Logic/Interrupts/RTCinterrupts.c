#include "interrupts.h"

void RTC_C_IRQHandler(void)
{
    uint32_t status;

    status = RTC_C_getEnabledInterruptStatus();
    RTC_C_clearInterruptFlag(status);

    if (status & RTC_C_TIME_EVENT_INTERRUPT)
    {

        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);

    }
}
