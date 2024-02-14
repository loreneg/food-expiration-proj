#ifndef __ADDFOODGRAPHICS_H__
#define __ADDFOODGRAPHICS_H__

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Logic/Graphics/foodListGraphics.h"

#define PRODNAMELENGTH 5
#define NAMEY 21
#define NAMEX 0
#define PRODNAMEX 0
#define PRODNAMEY 32
#define FONTWIDTH 6
#define CHARBUTTONWIDTH 8   //these values were taken using g_sFontFixed6x8 font
#define CHARBUTTONHEIGHT 10
#define CHARBUTTONTEXTOFFSET 2
#define QUANTITYY 45
#define QUANTITYX 0
#define QUANTITYBUTTONY 56
#define QUANTITYBUTTONX 0
#define DATEY 69
#define DATEX 0
#define DATEBUTTONY 80
#define DAYBUTTONX 0
#define MONTHBUTTONX 22
#define YEARBUTTONX 50
#define DAYSEPARATOR 16
#define MONTHSEPARATOR 44

void showAddFood();
void enableAddFoodSelection(uint8_t i);
void printDataButton(uint8_t i, bool selected);

#endif
