#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "main.h"

////////////
//Controls//
////////////

extern unsigned char connectedJoysticks;

typedef struct {
	unsigned char btn;
	unsigned char channel;
	bool onPartnerJoystick;

} JoyInput;

//vars

//functions
int readJoystick(JoyInput button);
unsigned char getNumConnectedJoysticks();

JoyInput controlButtonInit(unsigned char channel, unsigned char btn);
JoyInput controlButtonInitOnPartnerJoystick(unsigned char channel, unsigned char btn);
JoyInput controlStickInit(unsigned char channel);
JoyInput constrolStickInitPartnerJoystick(unsigned char channel);

#endif /* JOYSTICK_H_ */
