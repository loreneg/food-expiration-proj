#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <ti/grlib/button.h>

#include <stdio.h>

#include "Drivers/Lcd/Crystalfontz128x128_ST7735.h"

#include "Logic/Graphics/foodListGraphics.h"
#include "Logic/Graphics/graphicsContext.h"
#include "Logic/logic.h"

//list format:
//nnnnn: q00, dd-mmm-yy

//STANDARD DEFINITION OF A BUTTON
Graphics_Button ListButton = { 0, 128, 0, 12, 0, false, 0x001733, 0x001733,
                               0x002ee6,
                               GRAPHICS_COLOR_WHITE,
                               GRAPHICS_COLOR_WHITE, 0, (HEIGHT - 6) / 2,
                               "test", &g_sFontFixed6x8 };

char n[WIDTHCHAR + 1];
char month[4];  //3 char + terminator char
uint8_t page = 0;
uint8_t oldSelected = 0;

//This function allows us to print the month's name instead of the number

void convertMonthToString(uint8_t month, char *month_string)
{
    switch (month)
    {
    case 0x01:
        sprintf(month_string, "Jan");
        break;
    case 0x02:
        sprintf(month_string, "Feb");
        break;
    case 0x03:
        sprintf(month_string, "Mar");
        break;
    case 0x04:
        sprintf(month_string, "Apr");
        break;
    case 0x05:
        sprintf(month_string, "May");
        break;
    case 0x06:
        sprintf(month_string, "Jun");
        break;
    case 0x07:
        sprintf(month_string, "Jul");
        break;
    case 0x08:
        sprintf(month_string, "Aug");
        break;
    case 0x09:
        sprintf(month_string, "Sep");
        break;
    case 0x11:
        sprintf(month_string, "Nov");
        break;
    case 0x12:
    default:
        sprintf(month_string, "Dec");
        break;
    }
}

void printButton(uint8_t i, uint8_t pos, bool selected)
{
    ListButton.selected = selected;
    ListButton.yMin = pos * HEIGHT;
    ListButton.yMax = pos * HEIGHT + HEIGHT;
    ListButton.textXPos = 0;
    ListButton.textYPos = pos * HEIGHT + (HEIGHT - 6) / 2;
    convertMonthToString(foodList[i].month, month);
    sprintf(n, "%-4s: Q%-2d, %02x-%-3s-%02x", foodList[i].name,
            foodList[i].quantity, foodList[i].day, month, foodList[i].year);
    ListButton.text = (int8_t*) n;
    Graphics_drawButton(&g_sContext, &ListButton);
}

void showFoodList()
{
    Graphics_clearDisplay(&g_sContext);
    //Graphics_drawStringCentered(&g_sContext, "FOODLIST", AUTO_STRING_LENGTH, LCD_WIDTH / 2, LCD_HEIGHT / 2, TRANSPARENT_TEXT);
    int i;
    char n[WIDTHCHAR + 1];
    char month[4];  //3 char + terminator char
    for (i = page * LINES; i < LINES * (page + 1); i++)
    {
        uint8_t pos = i % LINES;
        ListButton.selected = false;
        ListButton.yMin = pos * HEIGHT;
        ListButton.yMax = pos * HEIGHT + HEIGHT;
        ListButton.textXPos = 0;
        ListButton.textYPos = pos * HEIGHT + (HEIGHT - 6) / 2;
        convertMonthToString(foodList[i].month, month);
        sprintf(n, "%-4s: Q%-2d, %02x-%-3s-%02x", foodList[i].name,
                foodList[i].quantity, foodList[i].day, month, foodList[i].year);
        ListButton.text = (int8_t*) n;
        Graphics_drawButton(&g_sContext, &ListButton);
    }
}

void initSelection()
{
    CS_initClockSignal(CS_MCLK, CS_MODOSC_SELECT, CS_CLOCK_DIVIDER_4);  //small overclock for showing data faster 6MHz
    oldSelected = 0;
    page = 0;
    showFoodList();
    printButton(0, 0, true);
}

void enableSelection(uint8_t i)
{
    uint8_t pos = i % LINES;
    uint8_t oldPos = oldSelected % LINES;
    if ((oldPos == 0 && pos == LINES - 1) || (oldPos == LINES - 1 && pos == 0))
    {
        page = i / LINES;
        showFoodList();
        printButton(i, pos, true);
    }
    else
    {
        if (oldPos != pos)
        {
            printButton(i, pos, true);
            printButton(oldSelected, oldPos, false);
        }
    }
    oldSelected = i;
}
