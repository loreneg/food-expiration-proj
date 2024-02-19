#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <ti/grlib/button.h>

#include <stdio.h>

#include "Drivers/Lcd/Crystalfontz128x128_ST7735.h"

#include "Logic/Graphics/foodListGraphics.h"
#include "Logic/Graphics/graphicsContext.h"
#include "Logic/logic.h"

//list format:
//nnnnn: q0, dd-mmm-yy

//DEFAULT BUTTON DEFINITION FOR THE LIST
Graphics_Button ListButton = { 0, 128, 0, 12, 0, false, 0x001733, 0x001733,
                               0x002ee6,
                               GRAPHICS_COLOR_WHITE,
                               GRAPHICS_COLOR_WHITE, 0, (HEIGHT - 6) / 2,
                               "", &g_sFontFixed6x8 };

char n[WIDTHCHAR + 1];      //temporary variable used for the button text
char month[4];              //3 char + terminator char
uint8_t page = 0;           //current page (ecery page contains 10 items)
uint8_t oldSelected = 0;    //old Selection, used for page change detection


//prints button
void printButton(uint8_t i, uint8_t pos, bool selected)
{
    ListButton.selected = selected;
    ListButton.yMin = pos * HEIGHT;                        //button position (0 - 9) * HEIGHT in pixels
    ListButton.yMax = pos * HEIGHT + HEIGHT;
    ListButton.textXPos = 0;
    ListButton.textYPos = pos * HEIGHT + (HEIGHT - 6) / 2;  //last operations needed for text centering
    convertMonthToString(months[foodList[i].month], month);
    char name[MAX_FOOD_NAME_LENGTH];                        //temporary variable for foodItem name
    int8_t j;
    for (j = 0; j < MAX_FOOD_NAME_LENGTH - 1; j++)
        name[j] = alphabet[foodList[i].name[j]];
    name[MAX_FOOD_NAME_LENGTH - 1] = '\0';
    sprintf(n, "%-5s: Q%-1c, %02x-%-3s-%02x", name, getQuantity(foodList[i]),
            days[foodList[i].day], month, years[foodList[i].year]);
    ListButton.text = (int8_t*) n;
    if(hasExpired(foodList[i])){
        ListButton.fillColor = GRAPHICS_COLOR_RED;          //if food has expired, show red background
    } else{
        ListButton.fillColor = 0x001733;
    }
    Graphics_drawButton(&g_sContext, &ListButton);
}


//This function resets the display and initializes the interface
void showFoodList()
{
    Graphics_clearDisplay(&g_sContext);
    uint8_t i;
    for (i = page * LINES; i < min(LINES * (page + 1), length); i++)
        printButton(i, i % LINES, false);                               //for each foodItem i initialize its button
    //the printButton function itself handles all the logic for the positioning of the button
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext, "S1:del S2:edit S3:men",
                                AUTO_STRING_LENGTH,
                                0,
                                BUTTONSLISTINGX,
                                true);
}

//initializes all the variables

void initSelection()
{
    flselected = 0;
    CS_initClockSignal(CS_MCLK, CS_MODOSC_SELECT, CS_CLOCK_DIVIDER_4); //small overclock for showing data faster 6MHz
    oldSelected = 0;
    page = 0;
    showFoodList();
    printButton(0, 0, true);
}


//updates the selected button by checking current and last position
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
