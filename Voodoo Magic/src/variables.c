#include "main.h"

/////////////
//Variables//
/////////////

//Lift liftEncoder
Sensor liftEncoder;

Sensor backLeftEncoder;
Sensor backRightEncoder;

PIDController liftPID;
PIDController strafePID;
PIDController drivePID;

//Init Drive Motors
Motor frontLeftWheel;
Motor frontRightWheel;
Motor backLeftWheel;
Motor backRightWheel;

//Init Lift Motors
Motor topLeftLift;
Motor middleLeftLift;
Motor bottomLeftLift;
Motor topRightLift;
Motor middleRightLift;
Motor bottomRightLift;

//Init Controller Buttons
JoyInput liftUp;
JoyInput liftDown;

JoyInput forward_backward_drive;
JoyInput left_right_drive;
JoyInput forward_backward_strafe;
JoyInput left_right_strafe;

Motor liftMotors[6];
//                 = { topLeftLift, middleLeftLift, bottomLeftLift,
//		topRightLift, middleRightLift, bottomRightLift };
Motor driveMotors[4];
//= { frontLeftWheel, backLeftWheel, frontRightWheel,
//		backRightWheel };
