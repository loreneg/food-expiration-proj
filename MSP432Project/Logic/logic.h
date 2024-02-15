#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <stdint.h>
#include "Logic/Graphics/menuGraphics.h"
#include "Logic/Graphics/foodListGraphics.h"
#include "Logic/Graphics/addFoodGraphics.h"

#define MAX_FOOD_NAME_LENGTH 6  //5 + string terminator
#define MAX_FOOD_ITEMS_COUNT 50
#define ADDFOODBUTTONS 9        //number of buttons in addfood

static const int8_t alphabet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-" };
static const uint8_t days[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                               0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                               0x17, 0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24,
                               0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31 };
static const uint8_t months[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                 0x09, 0x10, 0x11, 0x12 };
static const uint8_t years[] = { 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30 };

extern Selection_t currSelection;

typedef struct FoodItem_t {
    uint8_t name[MAX_FOOD_NAME_LENGTH];
    uint8_t quantity;
    uint8_t day;
    uint8_t month;
    uint8_t year;
}FoodItem_t;

extern FoodItem_t foodList[MAX_FOOD_ITEMS_COUNT];
extern uint8_t length;
extern uint8_t flselected;
extern uint8_t afselected;

uint8_t findElement(const uint8_t a[], const uint8_t length, uint8_t value);
uint8_t getQuantity(FoodItem_t f);
void customDelay(uint64_t CYCLES);
void convertMonthToString(uint8_t month, char *month_string);

void _hwInit();

void start_graphics();
void start_menu();
void activate_peripherals();
void drawSelection(uint64_t y);
void drawSelectionList(uint64_t y);
void drawSelectionData(uint64_t y, uint64_t x);

#endif
