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
    if((status & GPIO_PIN1)){
        //user has chosen modality
        if(menuUnlocked && notOnMenuScreen){
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
    if((status & GPIO_PIN5)){

        if(menuUnlocked && !notOnMenuScreen){   //if on menu
            switch(currSelection){
            case FOODLIST:
                flselected = 0;
                initSelection();
                break;
            case ADDFOOD:
                showAddFood();
                break;
            }

            notOnMenuScreen = 1;    //quit menu
        }

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
    if((status & GPIO_PIN1)){
        menuUnlocked = 1;   //The menu gets unlocked
    }
}
