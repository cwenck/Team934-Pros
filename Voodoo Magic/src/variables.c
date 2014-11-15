#include "main.h"

/////////////
//Variables//
/////////////

//Lift liftEncoder
QuadEncoder liftEncoder;

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
