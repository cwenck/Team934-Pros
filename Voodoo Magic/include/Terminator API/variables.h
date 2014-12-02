#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "main.h"

#define NUM_LIFT_MOTORS 6
#define NUM_DRIVE_MOTORS 4

//Sensors
extern Sensor liftEncoder;

extern Sensor backLeftEncoder;
extern Sensor backRightEncoder;

extern PIDController liftPID;
extern PIDController strafePID;
extern PIDController drivePID;

//Motors
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

//Joystick
extern JoyInput liftUp;
extern JoyInput liftDown;

extern JoyInput forward_backward_drive;
extern JoyInput left_right_drive;
extern JoyInput forward_backward_strafe;
extern JoyInput left_right_strafe;

extern Motor liftMotors[6];
extern Motor driveMotors[4];

#endif /* VARIABLES_H_ */
