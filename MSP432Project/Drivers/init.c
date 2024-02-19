/*
 * init.c
 *
 *  Created on: Jan 25, 2024
 *      Author: MACHCREATOR
 */
#include "Drivers/init.h"
#include "Logic/Graphics/graphicsContext.h"

#include "Drivers/Lcd/Crystalfontz128x128_ST7735.h"
//#include "Drivers/Graphics/images_definitions.h"
//#include "Drivers/Graphics/menu_graphics.h"

void _lowPowerInit()
{
    //P1
    GPIO_setAsOutputPin(GPIO_PORT_P1, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, PIN_ALL16);

    //P2
    GPIO_setAsOutputPin(GPIO_PORT_P2, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, PIN_ALL16);

    //P7
    GPIO_setAsOutputPin(GPIO_PORT_P7, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_P7, PIN_ALL16);

    //P8
    GPIO_setAsOutputPin(GPIO_PORT_P8, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, PIN_ALL16);

    //P9
    GPIO_setAsOutputPin(GPIO_PORT_P9, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, PIN_ALL16);

    //P10
    GPIO_setAsOutputPin(GPIO_PORT_P10, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_P10, PIN_ALL16);

    //PJ
    GPIO_setAsOutputPin(GPIO_PORT_PJ, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PJ, PIN_ALL16);
}

void _PCM_Flash_WDT_Init()
{
    // Stop watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    /* Set the core voltage level to VCORE1 */
    PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set 2 flash wait states for Flash bank 0 and 1*/
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
}

void _RTCInit()
{

    const RTC_C_Calendar currentTime = { 0x50, 0x59, 0x12, 0x06, 0x19, 0x02,
                                         0x2024 };

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
                                                GPIO_PIN0 | GPIO_PIN1,
                                                GPIO_PRIMARY_MODULE_FUNCTION);

    CS_setExternalClockSourceFrequency(32000, 48000000);
    /* Starting LFXT in non-bypass mode without a timeout. */
    CS_startLFXT(CS_LFXT_DRIVE3);
    /* Initializing RTC with current time */
    RTC_C_initCalendar(&currentTime, RTC_C_FORMAT_BCD);
    /* Sets interrupt for each midnight */
    RTC_C_setCalendarEvent(RTC_C_CALENDAREVENT_MIDNIGHT);
    /* Sets interrupt flags for calendar registers ready to read and event */
    RTC_C_clearInterruptFlag(RTC_C_TIME_EVENT_INTERRUPT);
    RTC_C_enableInterrupt(RTC_C_TIME_EVENT_INTERRUPT);
    //Start Clock
    RTC_C_startClock();

    //Enable interrupt
    Interrupt_enableInterrupt(INT_RTC_C);
}

void _ledInit()
{
    /* Configuring P1.0 as output */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void _buttonsInit()
{
    //Button S1
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);

    //Button S2
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5);
    GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);

    //Joystick button
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN1);

    //enable interrupts for Port3 and Port5 and Port4
    Interrupt_enableInterrupt(INT_PORT5);
    Interrupt_enableInterrupt(INT_PORT3);
    Interrupt_enableInterrupt(INT_PORT4);
}

//Enables joystick functionality with ADC
void _joystickInit()
{
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4,
                                               GPIO_TERTIARY_MODULE_FUNCTION);

    /* Initializing ADC (ADCOSC/64/8) */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8,
                     0);

    /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM1 (A15, A9)  with repeat)
     * with internal 2.5v reference */
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
    ADC14_configureConversionMemory(ADC_MEM0,
    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

    ADC14_configureConversionMemory(ADC_MEM1,
    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

    /* Enabling the interrupt when a conversion on channel 1 (end of sequence)
     *  is complete and enabling conversions */
    ADC14_enableInterrupt(ADC_INT1);

    /* Enabling Interrupts */
    Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableMaster();

    /* Setting up the sample timer to automatically step through the sequence
     * convert.
     */
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /* Triggering the start of the sample */
    ADC14_enableConversion();
}

//NOTE that ADC14_configureMultiSequenceMode(ADC_MEMx, ADC_MEMy, true); will "overwrite" a previous function of same type, so in order to have both
//Joystick and accelerometer working together you need to put ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM4, true); so that both memory location are properly configured

void _graphicsInit()
{
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&g_sContext, 0x00001733);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);
}
