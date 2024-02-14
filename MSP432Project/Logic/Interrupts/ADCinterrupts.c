#include "interrupts.h"

void customDelay(uint64_t CYCLES)
{
    uint64_t j;

    //this could throw a warning: Detected SW delay loop using empty loop. Recommend using a timer module instead
    //but the creator has decided not to use another timer to implement this function
    for(j=0;j<CYCLES;j++){}
}

void ADC14_IRQHandler(void)
{
    /* ADC results buffer that can store both the Joystick results and accelerometer ones */
    uint16_t resultsBuffer[3];

    uint64_t status;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);
    if(menuUnlocked){
    //still in menu mode
        if(!notOnMenuScreen)
        {
            //joystick
            if(status & ADC_INT1)
            {
                /* Store ADC14 conversion results */
                resultsBuffer[1] = ADC14_getResult(ADC_MEM1);

                if(resultsBuffer[1] < 7000 || resultsBuffer[1] > 9800){
                    customDelay(10000);
                    //switch modality in menu
                    drawSelection((uint64_t) resultsBuffer[1]);
                }
            }

            return;
        }

        if(currSelection == FOODLIST && notOnMenuScreen){
            resultsBuffer[1] = ADC14_getResult(ADC_MEM1);

            if(resultsBuffer[1] < 7000 || resultsBuffer[1] > 9800)
                drawSelectionList((uint64_t) resultsBuffer[1]);
        }
        if(currSelection == ADDFOOD && notOnMenuScreen){
                    resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
                    resultsBuffer[0] = ADC14_getResult(ADC_MEM0);

                    if(resultsBuffer[1] < 7000 || resultsBuffer[1] > 9800){
                        customDelay(10000);
                        //switch modality in menu
                        drawSelectionData((uint64_t) resultsBuffer[1], (uint64_t) resultsBuffer[0]);
                    }
                }
    }
}
