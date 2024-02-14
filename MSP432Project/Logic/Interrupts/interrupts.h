#ifndef LOGIC_INTERRUPTS_INTERRUPTS_H_
#define LOGIC_INTERRUPTS_INTERRUPTS_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/grlib/grlib.h>

// Graphics
#include "Logic/Graphics/graphicsContext.h"     //imported twice (present also in hardware_init.h) just to avoid problems in case of future changes in hardware_init.h
//#include "Logic/Graphics/direction_graphics.h"
//#include "Logic/Graphics/images_definitions.h"

// Logic of the project (all functions which drive the hardware based on decisions on variables values)
#include "Logic/logic.h"

extern int8_t menuUnlocked; //This variable unlocks the menu in the bootup
extern int8_t notOnMenuScreen;

#endif
