#include "logic.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/grlib/grlib.h>

#include "Drivers/init.h"
#include "Logic/Graphics/menuGraphics.h"
#include <stdio.h>

Selection_t currSelection = FOODLIST;     //the current section in the main menu

FoodItem_t foodList[MAX_FOOD_ITEMS_COUNT]; //The actual array that contains all the food items
uint8_t length = 4;     //used length of the foodList array

//these 2 are needed for the various interfaces

uint8_t flselected = 0; //selected variable for the foodlist section (index for foodList)
uint8_t afselected = 0; //selected variable for the add food section

int8_t hasExpired(FoodItem_t f)
{
    RTC_C_Calendar date = RTC_C_getCalendarTime();
    date.year -= 0x2000;     //the date is saves with only the last 2 characters
    if ((years[f.year] < date.year)    //if current year > food year
            || (years[f.year] == date.year && months[f.month] < date.month) //if current month > food month in same year
            || (years[f.year] == date.year && months[f.month] == date.month
                    && days[f.day] < date.dayOfmonth)) //if current day > food day in same month and year
        return 1;
    return 0;
}

//This function checks if food has expired, if so the red led turns on
void expiredFood()
{
    int8_t expired = 0;
    RTC_C_Calendar date = RTC_C_getCalendarTime();
    date.year -= 0x2000;
    uint8_t i;
    for (i = 0; i < length && expired == 0; ++i)
    {
        if ((years[foodList[i].year] < date.year)  //if current year > food year
                || (years[foodList[i].year] == date.year
                        && months[foodList[i].month] < date.month) //if current month > food month in same year
                || (years[foodList[i].year] == date.year
                        && months[foodList[i].month] == date.month
                        && days[foodList[i].day] < date.dayOfmonth)) //if current day > food day in same month and year
            expired = 1;
    }
    if (expired)
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);   //led turns on
    else
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);   //led turns off
}

//this function returns the index of an array value, 0 if not in range
uint8_t findElement(const uint8_t a[], const uint8_t length, uint8_t value)
{
    uint8_t i = 0;
    while (++i < length)
        if (a[i] == value)
            return i;
    return 0;
}

//This function removes the item selected by index i
void removeItem(FoodItem_t f[], uint8_t *length, uint8_t i)
{
    if (*length > 0 && i < *length)
    {
        uint8_t j;
        for (j = 0; j < *length; ++j)
        {
            if (j >= i && j < *length - 1)
                f[j] = f[j + 1];

        }
        (*length)--;
    }
}

void customDelay(uint64_t CYCLES)
{
    uint64_t j;

//this could throw a warning: Detected SW delay loop using empty loop. Recommend using a timer module instead
//but the creator has decided not to use another timer to implement this function
    for (j = 0; j < CYCLES; j++)
    {
    }
}

//returns foodItem quantity in char format

uint8_t getQuantity(FoodItem_t f)
{
    return f.quantity + 48;
}

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
    case 0x10:
        sprintf(month_string, "Oct");
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

//initializes RTC for accurate time tracking

    _RTCInit();

//initializes LED on Pin 1.0
    _ledInit();

//initializes buttons S1 and S2 (pins J4.32 and J4.33) on BoosterPack Module and Joystick button (Port4 PIN 1)
    _buttonsInit();

//initialize ADC for Joystick
    _joystickInit();

//initialize LCD
    _graphicsInit();
/* test for presentation video
//milk, 2, 22 feb 24
    foodList[0].name[0] = 13;
    foodList[0].name[1] = 9;
    foodList[0].name[2] = 12;
    foodList[0].name[3] = 11;
    foodList[0].name[4] = 0;
    foodList[0].quantity = 2;
    foodList[0].day = 21;
    foodList[0].month = 1;
    foodList[0].year = 0;
//eggs, 6, 18 feb 24
    foodList[1].name[0] = 5;
    foodList[1].name[1] = 7;
    foodList[1].name[2] = 7;
    foodList[1].name[3] = 19;
    foodList[1].name[4] = 0;
    foodList[1].quantity = 6;
    foodList[1].day = 17;
    foodList[1].month = 1;
    foodList[1].year = 0;
//chick, 4, 19 feb 24
    foodList[2].name[0] = 3;
    foodList[2].name[1] = 8;
    foodList[2].name[2] = 9;
    foodList[2].name[3] = 3;
    foodList[2].name[4] = 11;
    foodList[2].quantity = 2;
    foodList[2].day = 18;
    foodList[2].month = 1;
    foodList[2].year = 0;
//onion, 9, 8 dec 26
    foodList[3].name[0] = 15;
    foodList[3].name[1] = 14;
    foodList[3].name[2] = 9;
    foodList[3].name[3] = 15;
    foodList[3].name[4] = 14;
    foodList[3].quantity = 9;
    foodList[3].day = 25;
    foodList[3].month = 11;
    foodList[3].year = 2;
*/
    expiredFood();
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

    ADC14_toggleConversionTrigger();  //enable the ADC conversion for the analog
}

//This function draws the current selection in the main menu, based on the analog input in the y axis
void drawSelection(uint64_t y)
{
    if (y > 9800)
    {
        currSelection = (Selection_t) ((--currSelection) % 2); // Selection_t casting in order to avoid "enumerated type mixed with another type" warning
    }
    else if (y < 7000)
    {
        currSelection = (Selection_t) (++currSelection % 2); // Selection_t casting in order to avoid "enumerated type mixed with another type" warning
    }

    if (currSelection == FOODLIST)
    {
        drawSelectionFoodList();
    }

    if (currSelection == ADDFOOD)
    {
        drawSelectionAddFood();
    }
}

//This function draws the current selection in the food list menu, based on the analog input in the y axis
void drawSelectionList(uint64_t y)
{
    if (y > 9800 && flselected > 0)
    {
        flselected--;
    }
    else if (y < 7000 && flselected < length - 1)
    {
        flselected++;
    }

    enableSelection(flselected);
}

void drawSelectionData(uint64_t y, uint64_t x)
{

    if (y > 9800)
    {
        changeSelected(afselected, 1);   //goes up
    }
    else if (y < 7000)
    {
        changeSelected(afselected, -1); //goes down
    }
    else
    {

        if (x < 7200 && afselected > 0)
        {
            afselected = (uint8_t) (--afselected % ADDFOODBUTTONS); // Selection_t casting in order to avoid "enumerated type mixed with another type" warning
        }
        else if (x > 8300)
        {
            afselected = (uint8_t) (++afselected % ADDFOODBUTTONS);
        }

        enableAddFoodSelection(afselected);
    }
}

