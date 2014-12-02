#include "main.h"

bool lcdIsLeftButtonPressed(FILE *lcdPort) {
	int btns = lcdReadButtons(lcdPort);
	return (btns & LCD_BTN_LEFT) != 0;
}

bool lcdIsCenterButtonPressed(FILE *lcdPort) {
	int btns = lcdReadButtons(lcdPort);
	return (btns & LCD_BTN_CENTER) != 0;
}

bool lcdIsRightButtonPressed(FILE *lcdPort) {
	int btns = lcdReadButtons(lcdPort);
	return (btns & LCD_BTN_RIGHT) != 0;
}

void lcdDisplayCenteredString(FILE *lcdPort, unsigned char line, const char *text) {
	const unsigned char line_size = 16;
	int size = 0;
	for (const char *cursor = text; *cursor != NULL; cursor++) {
		size++;
	}
	if (size >= 16) {
		lcdSetText(lcdPort, line, text);
	} else {
		int extraSpace = line_size - size;
		int sideSpace = extraSpace / 2;
		char line_chars[16];
		char *linePointer = &line_chars[0];
		for (int i = 0; i < sideSpace; i++) {
			*linePointer = ' ';
			linePointer++;
		}

		int textSize = 0;
		for (const char *cursor = text; *cursor != NULL; cursor++) {
			*linePointer = *cursor;
			textSize++;
			linePointer++;
		}
		for(int i = textSize + sideSpace; i < 16; i ++){
			line_chars[i] = ' ';
		}
		lcdSetText(lcdPort, line, line_chars);
	}
}

void lcdDisplayFormattedCenteredString(FILE *lcdPort, unsigned char line,
		const char *formatString, ...) {
	int size = 0;
	for (const char *cursor = formatString; *cursor != NULL; cursor++) {
		size++;
	}
	char line_chars[17];

	va_list arg;

	va_start(arg, formatString);
	{
		vsnprintf(line_chars, 16, formatString, arg);
	}
	va_end(arg);
	lcdDisplayCenteredString(lcdPort, line, line_chars);
}

void lcdSetup(FILE *lcdPort){
	lcdInit(lcdPort);
	lcdClear(lcdPort);
	lcdSetBacklight(lcdPort, true);
}


void lcdDisplayBatteryStatus(FILE *lcdPort){
	lcdDisplayFormattedCenteredString(uart1, 1, "Main: %.2fV", getMainBatteryPower());
	lcdDisplayFormattedCenteredString(uart1, 2, "%c             %c", LCD_LEFT_TRIANGLE_ARROW, LCD_RIGHT_TRIANGLE_ARROW);
}
