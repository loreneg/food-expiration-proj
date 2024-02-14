#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <ti/grlib/button.h>

#include <stdio.h>

#include "Drivers/Lcd/Crystalfontz128x128_ST7735.h"

#include "Logic/Graphics/addFoodGraphics.h"
#include "Logic/Graphics/graphicsContext.h"
#include "Logic/logic.h"

//STANDARD DEFINITION OF A BUTTON
Graphics_Button dataButton = { 0, 0, 0, 0, 1, false, 0x001733,
                               GRAPHICS_COLOR_WHITE, 0x002ee6,
                               GRAPHICS_COLOR_WHITE,
                               GRAPHICS_COLOR_WHITE, 0, 0, "test",
                               &g_sFontFixed6x8 };

void setButton(uint16_t xMin, uint16_t yMin, int8_t *text, uint8_t nchar)  //function for setting up a button. nchar is the number of chars that you want inside of the button - 1
{
    dataButton.xMin = xMin;
    dataButton.xMax = xMin + CHARBUTTONWIDTH + FONTWIDTH*nchar;
    dataButton.yMin = yMin;
    dataButton.yMax = yMin + CHARBUTTONHEIGHT;
    dataButton.textXPos = xMin + CHARBUTTONTEXTOFFSET;
    dataButton.textYPos = yMin + CHARBUTTONTEXTOFFSET;
    dataButton.text = text;
}

void showAddFood()
{
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawString(&g_sContext, "name:", AUTO_STRING_LENGTH, NAMEX, NAMEY,
                        true);
    //printing of name section
    uint8_t i;
    for (i = 0; i < 5; i++)
    {
        setButton(PRODNAMEX + i * 11, PRODNAMEY, "B", 0);
        Graphics_drawButton(&g_sContext, &dataButton);
    }
    //printing of quantity section
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext, "quantity:", AUTO_STRING_LENGTH, QUANTITYX,
                        QUANTITYY, true);
    setButton(QUANTITYBUTTONX, QUANTITYBUTTONY, "1", 0);
    Graphics_drawButton(&g_sContext, &dataButton);
    //printing of date section
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext, "date:", AUTO_STRING_LENGTH, DATEX,DATEY, true);
    setButton(DAYBUTTONX, DATEBUTTONY, "14", 1);
    Graphics_drawButton(&g_sContext, &dataButton);
    setButton(MONTHBUTTONX, DATEBUTTONY, "Feb", 2);
    Graphics_drawButton(&g_sContext, &dataButton);
    setButton(YEARBUTTONX, DATEBUTTONY, "24", 1);
    Graphics_drawButton(&g_sContext, &dataButton);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext, "/", AUTO_STRING_LENGTH, DAYSEPARATOR, DATEBUTTONY+CHARBUTTONTEXTOFFSET, true);
    Graphics_drawString(&g_sContext, "/", AUTO_STRING_LENGTH, MONTHSEPARATOR, DATEBUTTONY+CHARBUTTONTEXTOFFSET, true);


}
