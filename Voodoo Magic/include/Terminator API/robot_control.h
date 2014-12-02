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
void setRightMotorSpeed(int speed, WheelDirection dir, MotorAccessController controller);
void setLeftMotorSpeed(int speed, WheelDirection dir, MotorAccessController controller);

void strafe(int speed, Direction dir, MotorAccessController controller);
void drive(int speed, Direction dir, MotorAccessController controller);

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
void setLiftPower(int speed, MotorAccessController controller);

int inchesToLiftEncoderTicks(float inches);
int feetToLiftEncoderTicks(float feet);

///////////////////////////////////
//PID Controllable Drive Funtions//
///////////////////////////////////

//negative is backward, positive is forward
void driveForwardBackward(int speed,  MotorAccessController controller);

//negative is left, positive is right
//magnitude is motor power
void turnLeftRight(int speed,  MotorAccessController controller);

//negative is left, positive is right
//magnitude is motor power
void strafeLeftRight(int speed,  MotorAccessController controller);

#endif /* ROBOT_CONTROL_H_ */
