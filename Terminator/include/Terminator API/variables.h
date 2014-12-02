#ifndef VARIABLES_H_
#define VARIABLES_H_

//Sensors
extern Sensor liftEncoder;

extern PIDController liftPID;
extern PIDController strafePID;
extern PIDController drivePID;

//Motors
extern Motor frontLeftWheel;
extern Motor frontRightWheel;
extern Motor backLeftWheel;
extern Motor backRightWheel;

//Joystick
extern JoyInput liftUp;
extern JoyInput liftDown;

extern JoyInput forward_backward_drive;
extern JoyInput left_right_drive;
extern JoyInput forward_backward_strafe;
extern JoyInput left_right_strafe;

#endif /* VARIABLES_H_ */
