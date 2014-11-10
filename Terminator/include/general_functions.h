/*
 * general_functions.h
 *
 *  Created on: Oct 18, 2014
 *      Author: guywenck
 */

#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_

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

extern Motor frontLeftLift;
extern Motor backLeftLift;
extern Motor frontRightLift;
extern Motor backRightLift;

//functions
void setMotorPower(Motor motor, int speed);

Motor createMotor(unsigned char port, bool reversed);
Motor createMotorWithIME(unsigned char port, unsigned char imeAddress,
		bool reversed);

void resetMotorIME(Motor motor);
int readMotorIME(Motor motor);
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
} PushButton;

typedef struct {
	unsigned char port;
	bool inverted;
} AnalogSensor;

typedef enum {
	IntegratedMotorEncoder,	//IC2
	QuadratureEncoder,		//?
	Sonar,					//Digital
	Line,					//Analog
	Light,					//Analog
	Push_Button,			//Digital
	Limit_Switch,			//Digital
	Potentiometer,			//Analog
	Gyroscope,				//Analog
	Accelerometer			//Analog
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
	bool inverted;
	union {
		Encoder encoder;
		PushButton pushButton;
		Ultrasonic sonar;
		AnalogSensor analog;
		Gyro gyro;
	} sensorData;
} Sensor;

//vars
extern Encoder liftEncoder;

//functions

//used for Bumpers and limit switches
PushButton pushButtonInit(unsigned char port);
bool pushButtonPressed(PushButton pushButton);

int portDecode(SensorPort port);

AnalogSensor analogSensorInit(int port, bool inverted);
int analogSensorRead(AnalogSensor sensor);

Sensor sensorInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted, int sensorConfig);
//void sensorInit(Sensor sensor, bool inverted, int sensorConfig);
int sensorGet(Sensor sensor);

///////
//PID//
///////

typedef struct {
	float kp;
	float ki;
	float kd;
	int p_speed;
	int i_speed;
	int d_speed;
	int motor_speed;
	//number of checks passed to
	//see if the target has been reached
	int num_checks_passed;
	bool target_reached;
	float error_tolerance;
	float error;
	float last_error;
	float sensor_target;
	float sensor_reading;
	float integral;
	bool ignoreIntegralBounds;
	//how samll the error needs to be
	// for the integral to be calculated
	float integral_range;
	float integral_min;
	float integral_max;
	float derivative;
	void (*setMotorSpeedFunction)(int);
	Sensor sensor;
} PIDController;

PIDController pidControllerInit(float kp, float ki, float kd,
		void (*setMotorSpeedFunction)(int), Sensor sensor);
void pidControllerSetTarget(PIDController *controller, float target);
void pidSetIntegralRange(PIDController *controller, float integralRange);
void pidControllerSetIntegralSpeedBounds(PIDController *controller, float integral_min, float integral_max);
void pidStart(PIDController *controller);
void pidTask(void *ignore);

/////////
//Other//
/////////

int capMotorPower(int value);

//returns the main battery power in volts
float getMainBatteryPower();
//print the main batter power in volts
void printMainBatteryPower();

#endif /*GENERAL_FUNCTIONS_H_*/
