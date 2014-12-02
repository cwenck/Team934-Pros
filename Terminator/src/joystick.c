#include "main.h"

////////////
//Joystick//
////////////

unsigned char getNumConnectedJoysticks() {
	unsigned char joysticksConnected = 0;
	if (isJoystickConnected(1)) {
		joysticksConnected++;
	}
	if (isJoystickConnected(2)) {
		joysticksConnected++;
	}
	return joysticksConnected;
}

int readJoystick(JoyInput input) {
	unsigned char joy = 1;
	unsigned char channel;
	unsigned char btn;
	switch (input) {
	case Btn5U:
		channel = 5;
		btn = JOY_UP;
		break;
	case Btn6U:
		channel = 6;
		btn = JOY_UP;
		break;
	case Btn7U:
		channel = 7;
		btn = JOY_UP;
		break;
	case Btn8U:
		channel = 8;
		btn = JOY_UP;
		break;
	case Btn5D:
		channel = 5;
		btn = JOY_DOWN;
		break;
	case Btn6D:
		channel = 6;
		btn = JOY_DOWN;
		break;
	case Btn7D:
		channel = 7;
		btn = JOY_DOWN;
		break;
	case Btn8D:
		channel = 8;
		btn = JOY_DOWN;
		break;
	case Btn7L:
		channel = 7;
		btn = JOY_LEFT;
		break;
	case Btn8L:
		channel = 8;
		btn = JOY_LEFT;
		break;
	case Btn7R:
		channel = 7;
		btn = JOY_RIGHT;
		break;
	case Btn8R:
		channel = 8;
		btn = JOY_RIGHT;
		break;
	case Ch1:
		channel = 1;
		break;
	case Ch2:
		channel = 2;
		break;
	case Ch3:
		channel = 3;
		break;
	case Ch4:
		channel = 4;
		break;
	case Partner_Btn5U:
		channel = 5;
		btn = JOY_UP;
		joy = 2;
		break;
	case Partner_Btn6U:
		channel = 6;
		btn = JOY_UP;
		joy = 2;
		break;
	case Partner_Btn7U:
		channel = 7;
		btn = JOY_UP;
		joy = 2;
		break;
	case Partner_Btn8U:
		channel = 8;
		btn = JOY_UP;
		joy = 2;
		break;
	case Partner_Btn5D:
		channel = 5;
		btn = JOY_DOWN;
		joy = 2;
		break;
	case Partner_Btn6D:
		channel = 6;
		btn = JOY_DOWN;
		joy = 2;
		break;
	case Partner_Btn7D:
		channel = 7;
		btn = JOY_DOWN;
		joy = 2;
		break;
	case Partner_Btn8D:
		channel = 8;
		btn = JOY_DOWN;
		joy = 2;
		break;
	case Partner_Btn7L:
		channel = 7;
		btn = JOY_LEFT;
		joy = 2;
		break;
	case Partner_Btn8L:
		channel = 8;
		btn = JOY_LEFT;
		joy = 2;
		break;
	case Partner_Btn7R:
		channel = 7;
		btn = JOY_RIGHT;
		joy = 2;
		break;
	case Partner_Btn8R:
		channel = 8;
		btn = JOY_RIGHT;
		joy = 2;
		break;
	case Partner_Ch1:
		channel = 1;
		joy = 2;
		break;
	case Partner_Ch2:
		channel = 2;
		joy = 2;
		break;
	case Partner_Ch3:
		channel = 3;
		joy = 2;
		break;
	case Partner_Ch4:
		channel = 4;
		joy = 2;
		break;
	}
	if (channel == 1 || channel == 2 || channel == 3 || channel == 4) {
		return joystickGetAnalog(joy, channel);
	} else {
		if (joystickGetDigital(joy, channel, btn)) {
			return 1;
		} else {
			return 0;
		}
	}
}
