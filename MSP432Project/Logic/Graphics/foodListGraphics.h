#ifndef __FOODLISTGRAPHICS_H__
#define __FOODLISTGRAPHICS_H__

#define LINES 10        //number of lines per screen
#define HEIGHT 12       //number of pixels per line
#define WIDTHCHAR 21    //number of characters per line

void showFoodList();

void enableSelection(uint8_t i);
void initSelection();

#endif
