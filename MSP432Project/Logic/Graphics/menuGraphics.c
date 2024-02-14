#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>

#include <stdio.h>

#include "Drivers/Lcd/Crystalfontz128x128_ST7735.h"

#include "Logic/Graphics/menuGraphics.h"
#include "Logic/Graphics/images.h"
#include "Logic/Graphics/graphicsContext.h"
#include "Logic/Interrupts/interrupts.h"        //included for menuUnlocked variable
#include "Logic/logic.h"

void startupImage(){
    Graphics_drawImage(&g_sContext, &LOGO, 0, 0);
    while(!menuUnlocked){   //while the menu is still locked (Unlock by pressing button S1 or S2)
        __sleep();
    }
}

void drawMenu(){
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);  //set clock to 3MHz (stock)
    Graphics_drawImage(&g_sContext, &MENU, 0, 0);
}

//Draw the menu when the FoodList item is selected
void drawSelectionFoodList(){
    Graphics_drawImage(&g_sContext, &FOODLISTSELECTED, 13, 59);
    Graphics_drawImage(&g_sContext, &ADDFOOD, 13, 84);
    //Graphics_drawStringCentered(&g_sContext, (int8_t*)"0", AUTO_STRING_LENGTH, 55, 70,OPAQUE_TEXT);
}

void drawSelectionAddFood(){
    Graphics_drawImage(&g_sContext, &ADDFOODSELECTED, 13, 84);
    Graphics_drawImage(&g_sContext, &FOODLIST, 13, 59);
    //Graphics_drawStringCentered(&g_sContext, (int8_t*)"1", AUTO_STRING_LENGTH, 55, 70,OPAQUE_TEXT);
}

void drawNewSelection(uint8_t s){

}
