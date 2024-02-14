#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <stdint.h>
#include "Logic/Graphics/menuGraphics.h"
#include "Logic/Graphics/foodListGraphics.h"
#include "Logic/Graphics/addFoodGraphics.h"

#define MAX_FOOD_NAME_LENGTH 6  //5 + string terminator
#define MAX_FOOD_ITEMS_COUNT 50

extern Selection_t currSelection;

typedef struct FoodItem_t {
    char name[MAX_FOOD_NAME_LENGTH];
    uint8_t quantity;
    uint8_t day;
    uint8_t month;
    uint8_t year;
}FoodItem_t;

extern FoodItem_t foodList[MAX_FOOD_ITEMS_COUNT];
extern uint8_t flselected;
extern uint8_t afselected;

void convertMonthToString(uint8_t month, char *month_string);

void _hwInit();

void start_graphics();
void start_menu();
void activate_peripherals();
void drawSelection(uint64_t y);
void drawSelectionList(uint64_t y);
void drawSelectionData(uint64_t y, uint64_t x);

#endif
