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
int8_t modified = -1;   //if modified is -1, it means that we're adding an item
//Otherwis it will be used as index for foodItemList

//DEFAULT BUTTON DEFINITION
Graphics_Button dataButton = { 0, 0, 0, 0, 1, false, 0x001733,
GRAPHICS_COLOR_WHITE,
                               0x002ee6,
                               GRAPHICS_COLOR_WHITE,
                               GRAPHICS_COLOR_WHITE, 0, 0, "test",
                               &g_sFontFixed6x8 };

//Deep copy implementation for foodItem
void copyFoodItem(FoodItem_t *f1, FoodItem_t *f2)
{
    int8_t j;
    for (j = 0; j < MAX_FOOD_NAME_LENGTH - 1; j++)
        f1->name[j] = f2->name[j];
    f1->day = f2->day;
    f1->quantity = f2->quantity;
    f1->month = f2->month;
    f1->year = f2->year;
}

//function for setting up a button. nchar is the number of chars that you want inside of the button - 1

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

//this function handles all the logic for printing a button, from positioning to what it contains
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
        break;  //name buttons
    case 5:
        c[0] = getQuantity(newEntry); //conversion from int to ascii number
        c[1] = '\0';
        setButton(QUANTITYBUTTONX, QUANTITYBUTTONY, (int8_t*) c, 0);
        break;  //quantity buttons
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
        break;  //date buttons
    }
    dataButton.selected = selected;
    Graphics_drawButton(&g_sContext, &dataButton);
}

//this function initializes all the interface
void showAddFood(int8_t oldEntry) //index of entry to modify, if -1 a new Item will be added to the list
{
    if (oldEntry == -1)
    {
        RTC_C_Calendar date = RTC_C_getCalendarTime();  //current date
        memset(newEntry.name, 0, 5);
        newEntry.quantity = 1;
        newEntry.day = findElement(days, DAYSLENGTH, date.dayOfmonth);
        newEntry.month = findElement(months, MONTHSLENGTH, date.month);
        newEntry.year = findElement(years, YEARSLENGTH, date.year);
    }
    else
    {
        modified = oldEntry;
        copyFoodItem(&newEntry, &foodList[oldEntry]);
    }
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_clearDisplay(&g_sContext);
    //I FIRST PRINT ALL THE TEXT
    Graphics_drawString(&g_sContext, "USE ANALOG TO MOVE", AUTO_STRING_LENGTH,
                        0, 0, true);
    Graphics_drawString(&g_sContext, "PRESS S2 TO CONFIRM", AUTO_STRING_LENGTH,
                        0, CHARBUTTONHEIGHT, true);
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

//this function handles the x axis changes in the interface
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
//It has logic for accurate and consistent dates
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

void confirmChoise()   //This function is called by pressing s2 in the interface
//it adds the new entry to the list, or modifies the old one
{
    if (modified != -1) //if true modify old entry
    {
        copyFoodItem(&foodList[modified], &newEntry);
        currSelection = FOODLIST;
        initSelection();
        modified = -1;
    }
    else
    {
        //add newEntry to array/list
        if (length < MAX_FOOD_ITEMS_COUNT)
        {
            copyFoodItem(&foodList[length++], &newEntry); //add newEntry to foodList
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawString(&g_sContext, "FOOD HAS BEEN ADDED!",
            AUTO_STRING_LENGTH,
                                ADDEDFOODX,
                                ADDEDFOODY,
                                true);
            customDelay(100000);
            afselected = 0;
            showAddFood(-1);
        }
        else
        {
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawString(&g_sContext, "FOOD LIST IS FULL!",
            AUTO_STRING_LENGTH,
                                ADDEDFOODX,
                                ADDEDFOODY,
                                true);
            customDelay(100000);
            afselected = 0;
            showAddFood(-1);
        }
    }
    expiredFood();  //checks if food has expired
}
