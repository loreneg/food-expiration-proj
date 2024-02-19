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

/*
 * In this project we decided to change the msp clock in certain areas for ease of use and smoother experience:
 * 3Mhz in the menu
 * 3Mhz in the add food section
 * 6Mhz in the food list section
 * */

void drawMenu(){
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);  //set clock to 3MHz (stock)
    Graphics_drawImage(&g_sContext, &MENU, 0, 0);                       //draws the actual menu
}

//Draw the menu when the FoodList item is selected
void drawSelectionFoodList(){
    Graphics_drawImage(&g_sContext, &FOODLISTSELECTED, 13, 59);         //draws the food list selected image
    Graphics_drawImage(&g_sContext, &ADDFOOD, 13, 84);                  //draws the add food not selected image
}

void drawSelectionAddFood(){
    Graphics_drawImage(&g_sContext, &ADDFOODSELECTED, 13, 84);          //draws the add food selected image
    Graphics_drawImage(&g_sContext, &FOODLIST, 13, 59);                 //draws the food list image
}
