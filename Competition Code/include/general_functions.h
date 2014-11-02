/*
 * general_functions.h
 *
 *  Created on: Oct 18, 2014
 *      Author: guywenck
 */

#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_

#endif /* GENERAL_FUNCTIONS_H_ */

#include "main.h"

////////////
void handleAllInput();
///////////

//////////
//Motors//
//////////
typedef struct {
	unsigned char port;
	unsigned char imeAddress;
	bool reversed;
} Motor;

//vars
extern unsigned char connectedIntegratedMotorEncoders;

extern Motor frontLeftWheel;
extern Motor frontRightWheel;
extern Motor backLeftWheel;
extern Motor backRightWheel;

extern Motor topLeftLift;
extern Motor middleLeftLift;
extern Motor bottomLeftLift;
extern Motor topRightLift;
extern Motor middleRightLift;
extern Motor bottomRightLift;

//functions
void setMotorPower(Motor motor, int speed);

Motor createMotor(unsigned char port, bool reversed);
Motor createMotorWithIME(unsigned char port, unsigned char imeAddress, bool reversed);

/////////
//Drive//
/////////

typedef enum {
	same, towards, away
} WheelDirection;

typedef enum {
	left, right, forward, backward
} Direction;

//vars
extern const int DRIVE_THRESHOLD;

//functions
void setRightMotorSpeed(int speed, WheelDirection dir);
void setLeftMotorSpeed(int speed, WheelDirection dir);

void strafe(int speed, Direction dir);
void drive(int speed, Direction dir);

void handleDriveInput();
void handleStrafingInput();

void handleDriveOrStrafing();

////////
//Lift//
////////

//vars
extern const short liftHighPower;
extern const short liftLowPower;

//functions
void handleLiftInput();
void setLiftPower(int speed);

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

///////////
//Sensors//
///////////

typedef struct {
	unsigned char port;
} Bumper;

typedef struct {
	unsigned char port;
} LimitSwitch;

//vars
extern Encoder liftEncoder;

//functions
Bumper bumperInit(unsigned char port);
bool bumperPressed(Bumper bumper);

LimitSwitch limitSwitchInit(unsigned char port);
bool limitSwitchPressed(LimitSwitch limitSwitch);


/////////
//Other//
/////////

//returns the main battery power in volts
float getMainBatteryPower();
//print the main batter power in volts
void printMainBatteryPower();
