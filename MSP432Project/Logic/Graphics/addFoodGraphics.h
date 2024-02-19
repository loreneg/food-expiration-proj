#ifndef __ADDFOODGRAPHICS_H__
#define __ADDFOODGRAPHICS_H__

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Logic/Graphics/foodListGraphics.h"
#include "Logic/logic.h"

#define PRODNAMELENGTH 5
#define NAMEY 29
#define NAMEX 0
#define PRODNAMEX 0
#define PRODNAMEY 40
#define FONTWIDTH 6
#define CHARBUTTONWIDTH 8   //these values were taken using g_sFontFixed6x8 font
#define CHARBUTTONHEIGHT 10
#define CHARBUTTONTEXTOFFSET 2
#define QUANTITYY 53
#define QUANTITYX 0
#define QUANTITYBUTTONY 64
#define QUANTITYBUTTONX 0
#define DATEY 77
#define DATEX 0
#define DATEBUTTONY 88
#define DAYBUTTONX 0
#define MONTHBUTTONX 22
#define YEARBUTTONX 50
#define DAYSEPARATOR 16
#define MONTHSEPARATOR 44
#define ADDEDFOODY 108
#define ADDEDFOODX 0

#define NAMESELECTIONLENGTH 37
#define QUANTITYSELECTIONLENGTH 9   //from 1 to 9
#define DAYSLENGTH 31
#define MONTHSLENGTH 12
#define YEARSLENGTH 6   //from 2024 to 2030, could be incremented


void showAddFood(int8_t i);
void enableAddFoodSelection(uint8_t i);
void changeSelected(uint8_t i, int8_t direction);
void confirmChoise();

#endif
