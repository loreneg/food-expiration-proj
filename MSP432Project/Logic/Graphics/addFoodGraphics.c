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
int8_t modified = -1;

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
        c[0] = getQuantity(newEntry); //conversion from int to ascii number
        c[1] = '\0';
        setButton(QUANTITYBUTTONX, QUANTITYBUTTONY, (int8_t*) c, 0);
        break;
    case 6:
        sprintf(c, "%02x", days[newEntry.day]);
        setButton(DAYBUTTONX, DATEBUTTONY, (int8_t*) c, 1);
        break;
    case 7:
        convertMonthToString(months[newEntry.month], c);
        setButton(MONTHBUTTONX, DATEBUTTONY, (int8_t*) c, 2);
        break;
    case 8:
        sprintf(c, "%02x", years[newEntry.year]);
        setButton(YEARBUTTONX, DATEBUTTONY, (int8_t*) c, 1);
        break;
    }
    dataButton.selected = selected;
    Graphics_drawButton(&g_sContext, &dataButton);
}

void showAddFood(int8_t oldEntry)   //index of entry to modify
{
    if (oldEntry == -1)
    {
        RTC_C_Calendar date = RTC_C_getCalendarTime();  //current date
        memset(&newEntry.name, 0, 5);
        newEntry.quantity = 1;
        newEntry.day = findElement(days, DAYSLENGTH, date.dayOfmonth);
        newEntry.month = findElement(months, MONTHSLENGTH, date.month);
        newEntry.year = findElement(years, YEARSLENGTH, date.year);
    }
    else
    {
        //strcpy((char*)newEntry.name, (char*)foodList[oldEntry].name);
        modified = oldEntry;
        int8_t j;
        for (j = 0; j < MAX_FOOD_NAME_LENGTH - 1; j++)
            newEntry.name[j] = foodList[oldEntry].name[j];
        newEntry.day = foodList[oldEntry].day;
        newEntry.quantity = foodList[oldEntry].quantity;
        newEntry.month = foodList[oldEntry].month;
        newEntry.year = foodList[oldEntry].year;
    }
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_clearDisplay(&g_sContext);
    //I FIRST PRINT ALL THE TEXT
    //printing of name section
    Graphics_drawString(&g_sContext, "name:", AUTO_STRING_LENGTH, NAMEX,
    NAMEY,
                        true);
    //printing of quantity section
    Graphics_drawString(&g_sContext, "quantity:", AUTO_STRING_LENGTH,
    QUANTITYX,
                        QUANTITYY,
                        true);
    //printing of date section
    Graphics_drawString(&g_sContext, "date:", AUTO_STRING_LENGTH, DATEX,
    DATEY,
                        true);
    Graphics_drawString(&g_sContext, "/", AUTO_STRING_LENGTH, DAYSEPARATOR,
    DATEBUTTONY + CHARBUTTONTEXTOFFSET,
                        true);
    Graphics_drawString(&g_sContext, "/", AUTO_STRING_LENGTH,
    MONTHSEPARATOR,
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

void changeSelected(uint8_t i, int8_t direction) //this function handles the editing for the newEntry struct
{
    switch (i)
    {
    //name buttons handlers
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        //checks if values are in range, and the new direction
        if ((direction == 1 && newEntry.name[i] < NAMESELECTIONLENGTH - 1)
                || (direction == -1 && newEntry.name[i] > 0))
            newEntry.name[i] += direction;
        break;
        //quantity handler
    case 5:
        if ((direction == 1 && newEntry.quantity < 9)
                || (direction == -1 && newEntry.quantity > 1))
            newEntry.quantity += direction;
        break;
        //day handler
    case 6:
        switch (newEntry.month + 1)
        {
        //the maximum days depends on the month
        //max = 31
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if ((direction == 1 && newEntry.day < 30)
                    || (direction == -1 && newEntry.day > 0))
                newEntry.day += direction;
            break;
        case 2:
            //max could be either 28 or 29 depending on year
            if (years[newEntry.year] % 4 == 0)
            {
                if ((direction == 1 && newEntry.day < 28)
                        || (direction == -1 && newEntry.day > 0))
                    newEntry.day += direction;
            }
            else
            {
                if ((direction == 1 && newEntry.day < 27)
                        || (direction == -1 && newEntry.day > 0))
                    newEntry.day += direction;
            }
            break;
            //max = 30
        default:
            if ((direction == 1 && newEntry.day < 29)
                    || (direction == -1 && newEntry.day > 0))
                newEntry.day += direction;
            break;
        }
        break;
        //months handler
    case 7:
        if ((direction == 1 && newEntry.month < MONTHSLENGTH - 1)
                || (direction == -1 && newEntry.month > 0))
        {
            if (newEntry.day > 27)
            {
                newEntry.day = 27;
                printDataButton(6, false);
            }
            newEntry.month += direction;
        }
        break;
        //years handler
    case 8:
        if ((direction == 1 && newEntry.year < YEARSLENGTH)
                || (direction == -1 && newEntry.year > 0))
        {
            if (newEntry.day > 27)
            {
                newEntry.day = 27;
                printDataButton(6, false);
            }
            newEntry.year += direction;
        }
        break;
    }
    printDataButton(i, true);
}

void confirmChoise()
{
    if (modified != -1) //if true modify old entry
    {
        int8_t j;
        for (j = 0; j < MAX_FOOD_NAME_LENGTH - 1; j++)
            foodList[modified].name[j] = newEntry.name[j];
        foodList[modified].day = newEntry.day;
        foodList[modified].quantity = newEntry.quantity;
        foodList[modified].month = newEntry.month;
        foodList[modified].year = newEntry.year;
        currSelection = FOODLIST;
        initSelection();
    }
    else
    {
        //add newEntry to array/list
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawString(&g_sContext, "CIBO AGGIUNTO!", AUTO_STRING_LENGTH,
        NAMEX,
                            NAMEY,
                            true);
        customDelay(100000);
        afselected = 0;
        showAddFood(-1);
    }

}
