/*
 * lcd.h
 *
 *  Created on: Nov 15, 2014
 *      Author: guywenck
 */

#ifndef LCD_H_
#define LCD_H_

#include "main.h"

bool lcdIsLeftButtonPressed(FILE *lcdPort);
bool lcdIsCenterButtonPressed(FILE *lcdPort);
bool lcdIsRightButtonPressed(FILE *lcdPort);
void lcdDisplayCenteredString(FILE *lcdPort, unsigned char line, const char *text);
void lcdDisplayFormattedCenteredString(FILE *lcdPort, unsigned char line, const char *formatString,...);

#endif /* LCD_H_ */
