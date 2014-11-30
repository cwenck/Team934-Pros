#ifndef ROBOT_CONTROL_H_
#define ROBOT_CONTROL_H_

#include "main.h"

//////////////////////
void handleAllInput();
//////////////////////

/////////
//Drive//
/////////

enum _WheelDirection{
	same, towards, away
};

enum _Direction{
	left, right, forward, backward
};

//vars
extern const int DRIVE_THRESHOLD;

//functions
void setRightMotorSpeed(int speed, WheelDirection dir, AccessID id);
void setLeftMotorSpeed(int speed, WheelDirection dir, AccessID id);

void strafe(int speed, Direction dir, AccessID id);
void drive(int speed, Direction dir, AccessID id);

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
void setLiftPower(int speed, AccessID id);

int inchesToLiftEncoderTicks(float inches);
int feetToLiftEncoderTicks(float feet);

///////////////////////////////////
//PID Controllable Drive Funtions//
///////////////////////////////////

//negative is backward, positive is forward
void driveForwardBackward(int speed, AccessID id);

//negative is left, positive is right
//magnitude is motor power
void turnLeftRight(int speed, AccessID id);

//negative is left, positive is right
//magnitude is motor power
void strafeLeftRight(int speed, AccessID id);

#endif /* ROBOT_CONTROL_H_ */
