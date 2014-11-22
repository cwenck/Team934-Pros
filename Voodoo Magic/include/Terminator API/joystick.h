#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "main.h"

////////////
//Controls//
////////////

extern unsigned char connectedJoysticks;

typedef enum {
	Btn5U,
	Btn6U,
	Btn7U,
	Btn8U,
	Btn5D,
	Btn6D,
	Btn7D,
	Btn8D,
	Btn7L,
	Btn8L,
	Btn7R,
	Btn8R,
	Ch1,
	Ch2,
	Ch3,
	Ch4,
	Partner_Btn5U,
	Partner_Btn6U,
	Partner_Btn7U,
	Partner_Btn8U,
	Partner_Btn5D,
	Partner_Btn6D,
	Partner_Btn7D,
	Partner_Btn8D,
	Partner_Btn7L,
	Partner_Btn8L,
	Partner_Btn7R,
	Partner_Btn8R,
	Partner_Ch1,
	Partner_Ch2,
	Partner_Ch3,
	Partner_Ch4
} JoyInput;

//vars

//functions
int readJoystick(JoyInput input);
unsigned char getNumConnectedJoysticks();


#endif /* JOYSTICK_H_ */
