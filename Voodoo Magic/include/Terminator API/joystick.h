#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "main.h"

////////////
//Controls//
////////////

extern unsigned char connectedJoysticks;

enum _JoyInput{
	Btn5U = 0,
	Btn6U = 1,
	Btn7U = 2,
	Btn8U = 3,
	Btn5D = 4,
	Btn6D = 5,
	Btn7D = 6,
	Btn8D = 7,
	Btn7L = 8,
	Btn8L = 9,
	Btn7R = 10,
	Btn8R = 11,
	Ch1 = 12,
	Ch2 = 13,
	Ch3 = 14,
	Ch4 = 15,
	Partner_Btn5U = 16,
	Partner_Btn6U = 17,
	Partner_Btn7U = 18,
	Partner_Btn8U = 19,
	Partner_Btn5D = 20,
	Partner_Btn6D = 21,
	Partner_Btn7D = 22,
	Partner_Btn8D = 23,
	Partner_Btn7L = 24,
	Partner_Btn8L = 25,
	Partner_Btn7R = 26,
	Partner_Btn8R = 27,
	Partner_Ch1 = 28,
	Partner_Ch2 = 29,
	Partner_Ch3 = 30,
	Partner_Ch4 = 31,
	Shift_Btn5U = 32,
	Shift_Btn6U = 33,
	Shift_Btn7U = 34,
	Shift_Btn8U = 35,
	Shift_Btn5D = 36,
	Shift_Btn6D = 37,
	Shift_Btn7D = 38,
	Shift_Btn8D = 39,
	Shift_Btn7L = 40,
	Shift_Btn8L = 41,
	Shift_Btn7R = 42,
	Shift_Btn8R = 43,
	Shift_Ch1 = 44,
	Shift_Ch2 = 45,
	Shift_Ch3 = 46,
	Shift_Ch4 = 47,
	Shift_Partner_Btn5U = 48,
	Shift_Partner_Btn6U = 49,
	Shift_Partner_Btn7U = 50,
	Shift_Partner_Btn8U = 51,
	Shift_Partner_Btn5D = 52,
	Shift_Partner_Btn6D = 53,
	Shift_Partner_Btn7D = 54,
	Shift_Partner_Btn8D = 55,
	Shift_Partner_Btn7L = 56,
	Shift_Partner_Btn8L = 57,
	Shift_Partner_Btn7R = 58,
	Shift_Partner_Btn8R = 59,
	Shift_Partner_Ch1 = 60,
	Shift_Partner_Ch2 = 61,
	Shift_Partner_Ch3 = 62,
	Shift_Partner_Ch4 = 63
};

struct _JoyInputInfo{
	unsigned char joystick;
	unsigned char channel;
	unsigned char btn;
	bool shifted;
	bool isButton;
};

//vars

//functions
int joystickRead(JoyInput input);
bool joystickIsMainShiftKeyPressed();
bool joystickIsPartnerShiftKeyPressed();
unsigned char joysticksGetNumConnected();
bool joystickIsShiftedInput(JoyInput input);
bool joystickIsInputButton(JoyInput input);
bool joystickMainSetShiftButton(JoyInput input);
bool joystickPartnerSetShiftButton(JoyInput input);
JoyInputInfo joystickGetInputInfo(JoyInput input);


#endif /* JOYSTICK_H_ */
