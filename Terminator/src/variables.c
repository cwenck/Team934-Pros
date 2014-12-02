#include "main.h"

/////////////
//Variables//
/////////////

//Lift liftEncoder
Sensor liftEncoder;

PIDController liftPID;
PIDController strafePID;
PIDController drivePID;

//Init Drive Motors
Motor frontLeftWheel;
Motor frontRightWheel;
Motor backLeftWheel;
Motor backRightWheel;

//Init Lift Motors

//Init Controller Buttons
JoyInput liftUp;
JoyInput liftDown;

JoyInput forward_backward_drive;
JoyInput left_right_drive;
JoyInput forward_backward_strafe;
JoyInput left_right_strafe;
