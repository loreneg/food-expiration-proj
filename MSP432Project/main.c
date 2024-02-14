#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/grlib/grlib.h>

#include <stdio.h>

#include "Drivers/init.h"
#include "Logic/logic.h"
//#include "Hardware/Graphics/direction_graphics.h"

// for debugging and testing

void main(void)
{
    // initializes all the hardware
    _hwInit();

    // draws fridge startup image
    start_graphics();

    // draws the menu
    start_menu();

    //activates master interrupt and timer
    activate_peripherals();


    while(1)
    {
        // MSP432 goes into sleep mode until next interrupt is fired
        PCM_gotoLPM0();
    }
}






