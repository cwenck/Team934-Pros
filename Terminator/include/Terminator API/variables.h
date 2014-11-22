#ifndef VARIABLES_H_
#define VARIABLES_H_

//Sensors
extern QuadEncoder liftEncoder;


//Motors
extern Motor frontLeftWheel;
extern Motor frontRightWheel;
extern Motor backLeftWheel;
extern Motor backRightWheel;

extern Motor frontLeftLift;
extern Motor backLeftLift;
extern Motor frontRightLift;
extern Motor backRightLift;

//Joystick
extern JoyInput liftUp;
extern JoyInput liftDown;

extern JoyInput forward_backward_drive;
extern JoyInput left_right_drive;
extern JoyInput forward_backward_strafe;
extern JoyInput left_right_strafe;

#endif /* VARIABLES_H_ */
