#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <ti/grlib/button.h>

#include <stdio.h>
#include <string.h>

#include "Drivers/Lcd/Crystalfontz128x128_ST7735.h"

#include "Logic/Graphics/addFoodGraphics.h"
#include "Logic/Graphics/graphicsContext.h"
#include "Logic/logic.h"

//temporary string for printing
char c[4];
//old selection, just for graphics cleanup
uint8_t oldSelection = 0;

FoodItem_t newEntry;    //item that will be added to the list

//STANDARD DEFINITION OF A BUTTON
Graphics_Button dataButton = { 0, 0, 0, 0, 1, false, 0x001733,
GRAPHICS_COLOR_WHITE,
                               0x002ee6,
                               GRAPHICS_COLOR_WHITE,
                               GRAPHICS_COLOR_WHITE, 0, 0, "test",
                               &g_sFontFixed6x8 };

void setButton(uint16_t xMin, uint16_t yMin, int8_t *text, uint8_t nchar) //function for setting up a button. nchar is the number of chars that you want inside of the button - 1
{
    dataButton.xMin = xMin;
    dataButton.xMax = xMin + CHARBUTTONWIDTH + FONTWIDTH * nchar;
    dataButton.yMin = yMin;
    dataButton.yMax = yMin + CHARBUTTONHEIGHT;
    dataButton.textXPos = xMin + CHARBUTTONTEXTOFFSET;
    dataButton.textYPos = yMin + CHARBUTTONTEXTOFFSET;
    dataButton.text = text;
}

void printDataButton(uint8_t i, bool selected)
{
    switch (i)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        c[0] = alphabet[newEntry.name[i]];
        c[1] = '\0';
        setButton(PRODNAMEX + i * 11, PRODNAMEY, (int8_t*) c, 0);
        break;
    case 5:
        c[0] = newEntry.quantity + 48;  //conversion from int to ascii number
        c[1] = '\0';
        setButton(QUANTITYBUTTONX, QUANTITYBUTTONY, (int8_t*) c, 0);
        break;
    case 6:
        sprintf(c, "%02x", newEntry.day);
        setButton(DAYBUTTONX, DATEBUTTONY, (int8_t*) c, 1);
        break;
    case 7:
        convertMonthToString(foodList[i].month, c);
        setButton(MONTHBUTTONX, DATEBUTTONY, (int8_t*) c, 2);
        break;
    case 8:
        sprintf(c, "%02x", newEntry.year);
        setButton(YEARBUTTONX, DATEBUTTONY, (int8_t*) c, 1);
        break;
    }
    dataButton.selected = selected;
    Graphics_drawButton(&g_sContext, &dataButton);
}

void showAddFood()
{
    RTC_C_Calendar date = RTC_C_getCalendarTime();  //current date
    memset(&newEntry.name, 0, 5);
    newEntry.quantity = 1;
    newEntry.day = date.dayOfmonth;
    newEntry.month = date.month;
    newEntry.year = date.year;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_clearDisplay(&g_sContext);
    //I FIRST PRINT ALL THE TEXT
    //printing of name section
    Graphics_drawString(&g_sContext, "name:", AUTO_STRING_LENGTH, NAMEX, NAMEY,
    true);
    //printing of quantity section
    Graphics_drawString(&g_sContext, "quantity:", AUTO_STRING_LENGTH, QUANTITYX,
    QUANTITYY,
                        true);
    //printing of date section
    Graphics_drawString(&g_sContext, "date:", AUTO_STRING_LENGTH, DATEX, DATEY,
    true);
    Graphics_drawString(&g_sContext, "/", AUTO_STRING_LENGTH, DAYSEPARATOR,
    DATEBUTTONY + CHARBUTTONTEXTOFFSET,
                        true);
    Graphics_drawString(&g_sContext, "/", AUTO_STRING_LENGTH, MONTHSEPARATOR,
    DATEBUTTONY + CHARBUTTONTEXTOFFSET,
                        true);
    //AND SECONDLY I PRINT ALL THE BUTTONS
    uint8_t i;
    for (i = 0; i < 9; i++)
        printDataButton(i, false);
    oldSelection = 0;
    printDataButton(0, true);
}

void enableAddFoodSelection(uint8_t i)
{
    if (i != oldSelection)
    {
        printDataButton(i, true);
        printDataButton(oldSelection, false);
        oldSelection = i;
    }
}

void changeSelected(uint8_t i, int8_t direction)
{
    switch (i)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        if ((direction == 1 && newEntry.name[i] < NAMESELECTIONLENGTH - 1)
                || (direction == -1 && newEntry.name[i] > 0))
            newEntry.name[i] += direction;
        break;
    case 5:
        if ((direction == 1 && newEntry.quantity < 9)
                || (direction == -1 && newEntry.quantity > 1))
            newEntry.quantity += direction;
        break;
    case 6:
        if ((direction == 1 && newEntry.quantity < 9)
                        || (direction == -1 && newEntry.quantity > 1))
                    newEntry.quantity += direction;
        break;
    case 7:
        break;
    case 8:
        break;
    }
    printDataButton(i, true);
}
