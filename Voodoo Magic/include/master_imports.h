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

typedef enum {
	IntegratedMotorEncoder,
	QuadratureEncoder,
	Sonar,
	Line,
	Light,
	Push_Button,
	Limit_Switch,
	Potentiometer,
	Gyroscope,
	Accelerometer,
} SensorType;

typedef enum {
	Digital_1,
	Digital_2,
	Digital_3,
	Digital_4,
	Digital_5,
	Digital_6,
	Digital_7,
	Digital_8,
	Digital_9,
	Digital_10,
	Digital_11,
	Digital_12,
	Analog_1,
	Analog_2,
	Analog_3,
	Analog_4,
	Analog_5,
	Analog_6,
	Analog_7,
	Analog_8,
	IME_1,
	IME_2,
	IME_3,
	IME_4,
	IME_5,
	IME_6,
	IME_7,
	IME_8,
} SensorPort;

typedef struct {
	SensorType type;
	SensorPort port_1;

	//Only used for Sonar and Quadrature encoders
	//order does not matter for the quadrature encoder,
	//it only reverses the direction of the rotation
	//This should be NULL if it is not one of those two sensor types.
	SensorPort port_2;
} Sensor;

//vars
extern Encoder liftEncoder;

//functions
Bumper bumperInit(unsigned char port);
bool bumperPressed(Bumper bumper);

LimitSwitch limitSwitchInit(unsigned char port);
bool limitSwitchPressed(LimitSwitch limitSwitch);

Sensor createSensor(SensorType, SensorPort port_1, SensorPort port_2);
int getSensorValue(Sensor sensor);

///////
//PID//
///////

typedef struct {
	float kp;
	float ki;
	float kd;
	float error;
	float last_error;
	float target;
	float position;
	float integral;
	float integral_min;
	float integral_max;
	float derivative;
   	// Funciton to execute that alters the speed of the motors.
	// The int argument should be the speed the motors are set to.
	void (* setMotorSpeedFunction) (int);
	Sensor sensor;
} pidController;

/////////
//Other//
/////////

//returns the main battery power in volts
float getMainBatteryPower();
//print the main batter power in volts
void printMainBatteryPower();
