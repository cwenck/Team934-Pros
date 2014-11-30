#include "main.h"

////////////
//Joystick//
////////////

JoyInput mainShiftBtn = -1;
JoyInput partnerShiftBtn = -1;

bool joystickIsShiftedInput(JoyInput input) {
	if (input >= Shift_Btn5U && input <= Shift_Partner_Ch4) {
		return true;
	}
	return false;
}

bool joystickIsInputButton(JoyInput input) {
	return ((input >= Btn5U && input <= Btn8R)
			|| (input >= Partner_Btn5U && input <= Partner_Btn8R)
			|| (input >= Shift_Btn5U && input <= Shift_Btn8R)
			|| (input >= Shift_Partner_Btn5U && input <= Shift_Partner_Btn8R));
}

bool joystickMainSetShiftButton(JoyInput input) {
	JoyInputInfo in = joystickGetInputInfo(input);
	if (in.isButton && in.joystick == 1 && !in.shifted) {
		mainShiftBtn = input;
		return true;
	}
	return false;
}

bool joystickPartnerSetShiftButton(JoyInput input) {
	JoyInputInfo in = joystickGetInputInfo(input);
	if (in.isButton && in.joystick == 2 && !in.shifted) {
		partnerShiftBtn = input;
		return true;
	}
	return false;
}

unsigned char joysticksGetNumConnected() {
	unsigned char joysticksConnected = 0;
	if (isJoystickConnected(1)) {
		joysticksConnected++;
	}
	if (isJoystickConnected(2)) {
		joysticksConnected++;
	}
	return joysticksConnected;
}

bool joystickIsMainShiftKeyPressed() {
	JoyInputInfo in = joystickGetInputInfo(mainShiftBtn);
	if (mainShiftBtn == -1) {
		return false;
	}
	return joystickGetDigital(1, in.channel, in.btn);
}

bool joystickIsPartnerShiftKeyPressed() {
	JoyInputInfo in = joystickGetInputInfo(partnerShiftBtn);
	if (partnerShiftBtn == -1) {
		return false;
	}
	return joystickGetDigital(2, in.channel, in.btn);
}

JoyInputInfo joystickGetInputInfo(JoyInput input) {
	JoyInputInfo info;

	info.joystick = 1;
	info.shifted = joystickIsShiftedInput(input);
	info.isButton = joystickIsInputButton(input);

	switch (input) {
	case Btn5U:
		info.channel = 5;
		info.btn = JOY_UP;
		break;
	case Btn6U:
		info.channel = 6;
		info.btn = JOY_UP;
		break;
	case Btn7U:
		info.channel = 7;
		info.btn = JOY_UP;
		break;
	case Btn8U:
		info.channel = 8;
		info.btn = JOY_UP;
		break;
	case Btn5D:
		info.channel = 5;
		info.btn = JOY_DOWN;
		break;
	case Btn6D:
		info.channel = 6;
		info.btn = JOY_DOWN;
		break;
	case Btn7D:
		info.channel = 7;
		info.btn = JOY_DOWN;
		break;
	case Btn8D:
		info.channel = 8;
		info.btn = JOY_DOWN;
		break;
	case Btn7L:
		info.channel = 7;
		info.btn = JOY_LEFT;
		break;
	case Btn8L:
		info.channel = 8;
		info.btn = JOY_LEFT;
		break;
	case Btn7R:
		info.channel = 7;
		info.btn = JOY_RIGHT;
		break;
	case Btn8R:
		info.channel = 8;
		info.btn = JOY_RIGHT;
		break;
	case Ch1:
		info.channel = 1;
		break;
	case Ch2:
		info.channel = 2;
		break;
	case Ch3:
		info.channel = 3;
		break;
	case Ch4:
		info.channel = 4;
		break;
	case Partner_Btn5U:
		info.channel = 5;
		info.btn = JOY_UP;
		info.joystick = 2;
		break;
	case Partner_Btn6U:
		info.channel = 6;
		info.btn = JOY_UP;
		info.joystick = 2;
		break;
	case Partner_Btn7U:
		info.channel = 7;
		info.btn = JOY_UP;
		info.joystick = 2;
		break;
	case Partner_Btn8U:
		info.channel = 8;
		info.btn = JOY_UP;
		info.joystick = 2;
		break;
	case Partner_Btn5D:
		info.channel = 5;
		info.btn = JOY_DOWN;
		info.joystick = 2;
		break;
	case Partner_Btn6D:
		info.channel = 6;
		info.btn = JOY_DOWN;
		info.joystick = 2;
		break;
	case Partner_Btn7D:
		info.channel = 7;
		info.btn = JOY_DOWN;
		info.joystick = 2;
		break;
	case Partner_Btn8D:
		info.channel = 8;
		info.btn = JOY_DOWN;
		info.joystick = 2;
		break;
	case Partner_Btn7L:
		info.channel = 7;
		info.btn = JOY_LEFT;
		info.joystick = 2;
		break;
	case Partner_Btn8L:
		info.channel = 8;
		info.btn = JOY_LEFT;
		info.joystick = 2;
		break;
	case Partner_Btn7R:
		info.channel = 7;
		info.btn = JOY_RIGHT;
		info.joystick = 2;
		break;
	case Partner_Btn8R:
		info.channel = 8;
		info.btn = JOY_RIGHT;
		info.joystick = 2;
		break;
	case Partner_Ch1:
		info.channel = 1;
		info.joystick = 2;
		break;
	case Partner_Ch2:
		info.channel = 2;
		info.joystick = 2;
		break;
	case Partner_Ch3:
		info.channel = 3;
		info.joystick = 2;
		break;
	case Partner_Ch4:
		info.channel = 4;
		info.joystick = 2;
		break;
	case Shift_Btn5U:
		info.channel = 5;
		info.btn = JOY_UP;
		break;
	case Shift_Btn6U:
		info.channel = 6;
		info.btn = JOY_UP;
		break;
	case Shift_Btn7U:
		info.channel = 7;
		info.btn = JOY_UP;
		break;
	case Shift_Btn8U:
		info.channel = 8;
		info.btn = JOY_UP;
		break;
	case Shift_Btn5D:
		info.channel = 5;
		info.btn = JOY_DOWN;
		break;
	case Shift_Btn6D:
		info.channel = 6;
		info.btn = JOY_DOWN;
		break;
	case Shift_Btn7D:
		info.channel = 7;
		info.btn = JOY_DOWN;
		break;
	case Shift_Btn8D:
		info.channel = 8;
		info.btn = JOY_DOWN;
		break;
	case Shift_Btn7L:
		info.channel = 7;
		info.btn = JOY_LEFT;
		break;
	case Shift_Btn8L:
		info.channel = 8;
		info.btn = JOY_LEFT;
		break;
	case Shift_Btn7R:
		info.channel = 7;
		info.btn = JOY_RIGHT;
		break;
	case Shift_Btn8R:
		info.channel = 8;
		info.btn = JOY_RIGHT;
		break;
	case Shift_Ch1:
		info.channel = 1;
		break;
	case Shift_Ch2:
		info.channel = 2;
		break;
	case Shift_Ch3:
		info.channel = 3;
		break;
	case Shift_Ch4:
		info.channel = 4;
		break;
	case Shift_Partner_Btn5U:
		info.channel = 5;
		info.btn = JOY_UP;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn6U:
		info.channel = 6;
		info.btn = JOY_UP;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn7U:
		info.channel = 7;
		info.btn = JOY_UP;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn8U:
		info.channel = 8;
		info.btn = JOY_UP;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn5D:
		info.channel = 5;
		info.btn = JOY_DOWN;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn6D:
		info.channel = 6;
		info.btn = JOY_DOWN;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn7D:
		info.channel = 7;
		info.btn = JOY_DOWN;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn8D:
		info.channel = 8;
		info.btn = JOY_DOWN;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn7L:
		info.channel = 7;
		info.btn = JOY_LEFT;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn8L:
		info.channel = 8;
		info.btn = JOY_LEFT;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn7R:
		info.channel = 7;
		info.btn = JOY_RIGHT;
		info.joystick = 2;
		break;
	case Shift_Partner_Btn8R:
		info.channel = 8;
		info.btn = JOY_RIGHT;
		info.joystick = 2;
		break;
	case Shift_Partner_Ch1:
		info.channel = 1;
		info.joystick = 2;
		break;
	case Shift_Partner_Ch2:
		info.channel = 2;
		info.joystick = 2;
		break;
	case Shift_Partner_Ch3:
		info.channel = 3;
		info.joystick = 2;
		break;
	case Shift_Partner_Ch4:
		info.channel = 4;
		info.joystick = 2;
		break;
	}
	return info;
}

int joystickRead(JoyInput input) {

	JoyInputInfo in = joystickGetInputInfo(input);

	if (in.joystick == 1) {
		if (in.shifted && joystickIsMainShiftKeyPressed()) {
			if (in.channel == 1 || in.channel == 2 || in.channel == 3
					|| in.channel == 4) {
				return joystickGetAnalog(in.joystick, in.channel);
			} else {
				if (joystickGetDigital(in.joystick, in.channel, in.btn)) {
					return 1;
				} else {
					return 0;
				}
			}
		} else if (!in.shifted && !joystickIsMainShiftKeyPressed()) {
			if (in.channel == 1 || in.channel == 2 || in.channel == 3
					|| in.channel == 4) {
				return joystickGetAnalog(in.joystick, in.channel);
			} else {
				if (joystickGetDigital(in.joystick, in.channel, in.btn)) {
					return 1;
				} else {
					return 0;
				}
			}
		} else {
			return 0;
		}
	} else {
		if (in.shifted && joystickIsMainShiftKeyPressed()) {
			if (in.channel == 1 || in.channel == 2 || in.channel == 3
					|| in.channel == 4) {
				return joystickGetAnalog(in.joystick, in.channel);
			} else {
				if (joystickGetDigital(in.joystick, in.channel, in.btn)) {
					return 1;
				} else {
					return 0;
				}
			}
		} else if (!in.shifted && !joystickIsMainShiftKeyPressed()) {
			if (in.channel == 1 || in.channel == 2 || in.channel == 3
					|| in.channel == 4) {
				return joystickGetAnalog(in.joystick, in.channel);
			} else {
				if (joystickGetDigital(in.joystick, in.channel, in.btn)) {
					return 1;
				} else {
					return 0;
				}
			}
		} else {
			return 0;
		}
	}
}
