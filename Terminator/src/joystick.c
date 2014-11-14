#include "main.h"

////////////
//Joystick//
////////////

JoyInput createButton(unsigned char channel, unsigned char btn) {
	JoyInput button;
	button.channel = channel;
	button.btn = btn;
	button.onPartnerJoystick = false;
	return button;
}

JoyInput createButtonOnPartnerJoystick(unsigned char channel, unsigned char btn) {
	JoyInput button;
	button.channel = channel;
	button.btn = btn;
	button.onPartnerJoystick = true;
	return button;
}

JoyInput createAxis(unsigned char channel) {
	JoyInput button;
	button.channel = channel;
	button.btn = NULL;
	button.onPartnerJoystick = false;
	return button;
}

JoyInput createAxisOnPartnerJoystick(unsigned char channel) {
	JoyInput button;
	button.channel = channel;
	button.btn = NULL;
	button.onPartnerJoystick = true;
	return button;
}

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

//If it is a button a 1 is returned for true and 0 for false
//otherwise a value between -127 and 127 is returned for the particular axis
int readJoystick(JoyInput button) {
	unsigned char joy = 1;
	if (button.onPartnerJoystick) {
		joy = 2;
	}
	if (button.channel == 1 || button.channel == 2 || button.channel == 3
			|| button.channel == 4) {
		return joystickGetAnalog(joy, button.channel);
	} else {
		if (joystickGetDigital(joy, button.channel, button.btn)) {
			return 1;
		} else {
			return 0;
		}
	}
}
