/*
 * joystick.h
 *
 *  Created on: Nov 12, 2014
 *      Author: guywenck
 */

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
extern JoyInput liftUp;
extern JoyInput liftDown;

extern JoyInput forward_backward_drive;
extern JoyInput left_right_drive;
extern JoyInput forward_backward_strafe;
extern JoyInput left_right_strafe;

//functions
int readJoystick(JoyInput button);
unsigned char getNumConnectedJoysticks();

JoyInput createButton(unsigned char channel, unsigned char btn);
JoyInput createButtonOnPartnerJoystick(unsigned char channel, unsigned char btn);
JoyInput createAxis(unsigned char channel);
JoyInput createAxisOnPartnerJoystick(unsigned char channel);

#endif /* JOYSTICK_H_ */
