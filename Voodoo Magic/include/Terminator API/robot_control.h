#ifndef ROBOT_CONTROL_H_
#define ROBOT_CONTROL_H_

#include "main.h"

//////////////////////
void handleAllInput();
//////////////////////

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

int inchesToLiftEncoderTicks(float inches);
int feetToLiftEncoderTicks(float feet);

///////////////////////////////////
//PID Controllable Drive Funtions//
///////////////////////////////////

//negative is backward, positive is forward
void driveForwardBackward(int speed);

//negative is left, positive is right
//magnitude is motor power
void turnLeftRight(int speed);

//negative is left, positive is right
//magnitude is motor power
void strafeLeftRight(int speed);

#endif /* ROBOT_CONTROL_H_ */
