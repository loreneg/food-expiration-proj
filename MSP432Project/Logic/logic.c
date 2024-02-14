#include "logic.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/grlib/grlib.h>

#include "Drivers/init.h"
#include "Logic/Graphics/menuGraphics.h"
#include <stdio.h>

Selection_t currSelection = FOODLIST;

FoodItem_t foodList[MAX_FOOD_ITEMS_COUNT];
uint8_t flselected = 0; //selected variable for the foodlist section
uint8_t afselected = 0; //selected variable for the add food section

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


void _hwInit()
{
    //Initializes all unused ports in order to address power consumption, this function is not mandatory and should just remove the warning (see the implementation for further info on why the warning is still present):
    //"Detected uninitialized Port 1 in this project. Recommend initializing all unused ports to eliminate wasted current consumption on unused pins."
    _lowPowerInit();

    //sets core voltage level and number of wait states used by flash controller for read operation
    _PCM_Flash_WDT_Init();

    //initialize RTC for accurate time tracking

    _RTCInit();

    //initialize LED on Pin 1.0
    _ledInit();

    //initialize TimerA2 and TimerA3 into upMode
    //_timersInit();

    //initialize buttons S1 and S2 (pins J4.32 and J4.33) on BoosterPack Module and Joystick button (Port4 PIN 1)
    _buttonsInit();

    // it is possible to initialize Joystick or accelerometer only if they have been selected by the user in the menu, but this configuration could allow to use both at the same time

    //initialize ADC for Joystick
    _joystickInit();

    //initialize LCD
    _graphicsInit();


    //variable init. Just for testing
    int i;
    for(i = 0; i < MAX_FOOD_ITEMS_COUNT; i++){
        sprintf(foodList[i].name, "%d", i);
        foodList[i].quantity = 6;
        RTC_C_Calendar date = RTC_C_getCalendarTime();
        foodList[i].day = date.dayOfmonth;
        foodList[i].month = date.month;
        foodList[i].year = date.year;
    }
}

// start the first fridge image at the startup
void start_graphics()
{
    // outputs fridge image
    startupImage();
}

void start_menu()
{
    drawMenu();
    drawSelectionFoodList();
}

void activate_peripherals()
{
    // enable master interrupt
    Interrupt_enableMaster();

    // start first timer (TIMER_A3)
    //Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_UP_MODE);
    ADC14_toggleConversionTrigger();
}


void drawSelection(uint64_t y){
    if(y>9800){
        currSelection = (Selection_t) ((--currSelection) % 2);  // Selection_t casting in order to avoid "enumerated type mixed with another type" warning
    } else if(y<7000){
        currSelection = (Selection_t) (++currSelection % 2);        // Selection_t casting in order to avoid "enumerated type mixed with another type" warning
    }

    if(currSelection == FOODLIST){
        drawSelectionFoodList();
    }

    if(currSelection == ADDFOOD){
        drawSelectionAddFood();
    }
}

void drawSelectionList(uint64_t y){
    if(y>9800 && flselected > 0){
        flselected = (uint8_t)(--flselected % MAX_FOOD_ITEMS_COUNT);
    } else if(y<7000){
        flselected = (uint8_t)(++flselected % MAX_FOOD_ITEMS_COUNT);      // Selection_t casting in order to avoid "enumerated type mixed with another type" warning
    }

    enableSelection(flselected);
}

void drawSelectionData(uint64_t y, uint64_t x){

}

