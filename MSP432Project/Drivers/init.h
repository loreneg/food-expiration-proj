#ifndef __INIT_H__
#define __INIT_H__

/* Timers periods (CCR0 values) */
#define TIMER_PERIOD3    0x05DC   //1500 to hex
#define TIMER_PERIOD2   0x03E8   //1000 to hex

void _lowPowerInit();

// stops watchdog timer and initializes some flash memory features (e.g. Voltage)
void _PCM_Flash_WDT_Init();

// initializes the RTC for accurate time tracking and date checking
void _RTCInit();

// initializes pin on Port 1 Pin 0 as output pin to use the connected LED
void _ledInit();

// initializes Buttons on TI J4.32 and J4.33 and Joystick input button
void _buttonsInit();

//initialize Analog to Digital Converter for Joystick and enables its interrupts
void _joystickInit();

//generic initialization of ADC14, to be used in conjunction with _adcInit() and/or _joystickInit()
void _adcInit();

//initialize Liquid Crystal Display
void _graphicsInit();

#endif
