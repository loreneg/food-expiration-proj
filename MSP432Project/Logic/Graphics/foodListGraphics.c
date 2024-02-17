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
                               "", &g_sFontFixed6x8 };

char n[WIDTHCHAR + 1];
char month[4];  //3 char + terminator char
uint8_t page = 0;
uint8_t oldSelected = 0;

void printButton(uint8_t i, uint8_t pos, bool selected)
{
    ListButton.selected = selected;
    ListButton.yMin = pos * HEIGHT;
    ListButton.yMax = pos * HEIGHT + HEIGHT;
    ListButton.textXPos = 0;
    ListButton.textYPos = pos * HEIGHT + (HEIGHT - 6) / 2;
    convertMonthToString(months[foodList[i].month], month);
    char name[MAX_FOOD_NAME_LENGTH];
    int8_t j;
    for (j = 0; j < MAX_FOOD_NAME_LENGTH - 1; j++)
        name[j] = alphabet[foodList[i].name[j]];
    name[MAX_FOOD_NAME_LENGTH - 1] = '\0';
    sprintf(n, "%-5s:Q%-2c, %02x-%-3s-%02x", name, getQuantity(foodList[i]),
            days[foodList[i].day], month, years[foodList[i].year]);
    ListButton.text = (int8_t*) n;
    Graphics_drawButton(&g_sContext, &ListButton);
}

void showFoodList()
{
    Graphics_clearDisplay(&g_sContext);
    //Graphics_drawStringCentered(&g_sContext, "FOODLIST", AUTO_STRING_LENGTH, LCD_WIDTH / 2, LCD_HEIGHT / 2, TRANSPARENT_TEXT);
    uint8_t i;
    for (i = page * LINES; i < min(LINES * (page + 1), length); i++)
        printButton(i, i % LINES, false);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext, "s1:delete s2:modify",
                                AUTO_STRING_LENGTH,
                                0,
                                BUTTONSLISTINGX,
                                true);
}

void initSelection()
{
    flselected = 0;
    CS_initClockSignal(CS_MCLK, CS_MODOSC_SELECT, CS_CLOCK_DIVIDER_4); //small overclock for showing data faster 6MHz
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
