/*
 * lcd.h
 *
 *  Created on: Nov 15, 2014
 *      Author: guywenck
 */

#ifndef LCD_H_
#define LCD_H_

#include "main.h"

//LCD Special Character Constants
#define LCD_DOWN_TRIANGLE_ARROW 0xF5
#define LCD_LEFT_TRIANGLE_ARROW 0xF7
#define LCD_RIGHT_TRIANGLE_ARROW 0xF6

#define LCD_LEFT_DOUBLE_ARROW 0xBB
#define LCD_RIGHT_DOUBLE_ARROW 0xBC

#define LCD_UP_ARROW 0xC5
#define LCD_DOWN_ARROW 0xC6
#define LCD_RIGHT_ARROW 0xC7
#define LCD_LEFT_ARROW 0xC8

#define LCD_PI 0xED



bool lcdIsLeftButtonPressed(FILE *lcdPort);
bool lcdIsCenterButtonPressed(FILE *lcdPort);
bool lcdIsRightButtonPressed(FILE *lcdPort);
void lcdDisplayCenteredString(FILE *lcdPort, unsigned char line, const char *text);
void lcdDisplayFormattedCenteredString(FILE *lcdPort, unsigned char line, const char *formatString,...);

//Can be used in place of lcd init
//turns on the backlight and clears the display after it is initialized
void lcdSetup(FILE *lcdPort);

void lcdDisplayBatteryStatus(FILE *lcdPort);

#endif /* LCD_H_ */
