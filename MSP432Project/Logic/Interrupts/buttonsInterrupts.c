#include "interrupts.h"
#include <stdio.h>

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
                    initSelection();        //initialize foodList
                    notOnMenuScreen = 1;    //quit menu
                }
                else
                {                           //print error
                    Graphics_setForegroundColor(&g_sContext,
                    GRAPHICS_COLOR_WHITE);
                    Graphics_drawString(&g_sContext, "NO FOOD IN THE LIST!!",
                    AUTO_STRING_LENGTH,
                                        0, 0,
                                        true);
                }
                break;
            case ADDFOOD:
                afselected = 0;  //current button is the first one
                showAddFood(-1); //-1 means that I want to add a new Entry to the list
                notOnMenuScreen = 1;    //quit menu
                break;
            }
        }
        else if (menuUnlocked && notOnMenuScreen && currSelection == FOODLIST)  //if we're on foodList section and press s2
        {
            CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
            currSelection = ADDFOOD;                                            //we move to add food
            showAddFood(flselected);                                            //to modify the selected Item
        }
        else if (menuUnlocked && notOnMenuScreen && currSelection == ADDFOOD)
        {
            flselected = 0;                                                     //If we're on addfood and press s2
            afselected = 0;
            confirmChoise();                                                    //we confirm the choise
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
        if (menuUnlocked && notOnMenuScreen && currSelection == FOODLIST)               //If we're on the foodList section and press s1
        {
            removeItem(foodList, &length, flselected);                                  //we remove the selected Item
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
