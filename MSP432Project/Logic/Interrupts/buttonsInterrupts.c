#include "interrupts.h"
#include <stdio.h>

#define LCD_WIDTH 128
#define LCD_HEIGHT 128

int8_t menuUnlocked = 0;        //The menu is set to be locked
int8_t notOnMenuScreen = 0;        //The mode has still to be selected

void PORT4_IRQHandler(void)
{
    /* Check which pins generated the interrupts */
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    /* clear interrupt flag (to clear pending interrupt indicator */
    GPIO_clearInterruptFlag(GPIO_PORT_P4, status);

    /* check if we received P3.5 interrupt */
    if ((status & GPIO_PIN1))
    {
        //user has chosen modality
        if (menuUnlocked && notOnMenuScreen)
        {
            notOnMenuScreen = 0;
            drawMenu();
            drawSelection(8000);
        }
    }
}

//Interrupt handler for button S2 on boosterPack
void PORT3_IRQHandler(void)
{
    /* Check which pins generated the interrupts */
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    /* clear interrupt flag (to clear pending interrupt indicator */

    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);

    /* check if we received P3.5 interrupt */
    if ((status & GPIO_PIN5))
    {

        if (menuUnlocked && !notOnMenuScreen)
        {   //if on menu
            switch (currSelection)
            {
            case FOODLIST:
                if (length > 0)
                {
                    initSelection();
                    notOnMenuScreen = 1;    //quit menu
                }
                else
                {
                    Graphics_setForegroundColor(&g_sContext,
                    GRAPHICS_COLOR_WHITE);
                    Graphics_drawString(&g_sContext, "NESSUN CIBO IN LISTA!!",
                    AUTO_STRING_LENGTH,
                                        0, 0,
                                        true);
                }
                break;
            case ADDFOOD:
                afselected = 0;
                showAddFood(-1); //-1 means that I want to add a new Entry to the list
                notOnMenuScreen = 1;    //quit menu
                break;
            }
        }
        else if (menuUnlocked && notOnMenuScreen && currSelection == FOODLIST)
        {
            CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
            currSelection = ADDFOOD;
            showAddFood(flselected);
        }
        else if (menuUnlocked && notOnMenuScreen && currSelection == ADDFOOD)
        {
            flselected = 0;
            afselected = 0;
            confirmChoise();
        }
        else
            menuUnlocked = 1;   //The menu gets unlocked
    }
}

//Button S1 on BoosterPack Module
void PORT5_IRQHandler(void)
{
    /* Check which pins generated the interrupts */
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    /* clear interrupt flag (to clear pending interrupt indicator */
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    /* check if we received P5.1 interrupt */
    if ((status & GPIO_PIN1))
    {
        if (menuUnlocked && notOnMenuScreen && currSelection == FOODLIST)
        {
            removeItem(foodList, &length, flselected);
            expiredFood();  //I check if food has expired
            if (length > 0)
                initSelection();
            else
            {
                notOnMenuScreen = 0;
                drawMenu();
                drawSelection(8000);
            }

        }
        else
            menuUnlocked = 1;   //The menu gets unlocked
    }
}
