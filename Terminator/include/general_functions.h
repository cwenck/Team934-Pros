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

///////////
//Sensors//
///////////

typedef enum {
	IntegratedMotorEncoder,	//IC2
	QuadratureEncoder,		//Digital
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
	Motor_1 = 1,
	Motor_2 = 2,
	Motor_3 = 3,
	Motor_4 = 4,
	Motor_5 = 5,
	Motor_6 = 6,
	Motor_7 = 7,
	Motor_8 = 8,
	Motor_9 = 9,
	Motor_10 = 10
} MotorPort;

typedef enum {
	Digital_1 = 1,
	Digital_2 = 2,
	Digital_3 = 3,
	Digital_4 = 4,
	Digital_5 = 5,
	Digital_6 = 6,
	Digital_7 = 7,
	Digital_8 = 8,
	Digital_9 = 9,
	Digital_10 = 10,
	Digital_11 = 11,
	Digital_12 = 12
} DigitalPort;

typedef enum {
	Analog_1 = 1,
	Analog_2 = 2,
	Analog_3 = 3,
	Analog_4 = 4,
	Analog_5 = 5,
	Analog_6 = 6,
	Analog_7 = 7,
	Analog_8 = 8
} AnalogPort;

typedef enum {
	IME_1 = 0,
	IME_2 = 1,
	IME_3 = 2,
	IME_4 = 3,
	IME_5 = 4,
	IME_6 = 5,
	IME_7 = 6,
	IME_8 = 7
} IMEPort;

typedef union {
	AnalogPort analogPort;
	DigitalPort digitalPort;
	IMEPort imePort;
} SensorPort;

typedef struct {
	unsigned char imeAddress;
	bool inverted;
} IntegratedEncoder;

typedef struct {
	unsigned char top_port;
	unsigned char bottom_port;
	bool inverted;
} QuadEncoder;

typedef struct {
	unsigned char port;
} PushButton;

typedef struct {
	unsigned char port;
	bool inverted;
} AnalogSensor;

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
		IntegratedEncoder ime;
		QuadEncoder quadEncoder;
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

AnalogSensor analogSensorInit(unsigned char port, bool inverted);
int analogSensorRead(AnalogSensor sensor);

QuadEncoder quadEncoderInit(DigitalPort topPort, DigitalPort bottomPort, bool inverted);
int quadencoderRead(QuadEncoder encoder);

IntegratedEncoder integratedEncoderInit(IMEPort port, bool inverted);
int integratedencoderRead(IntegratedEncoder encoder);

Sensor sensorInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted, int sensorConfig);
//void sensorInit(Sensor sensor, bool inverted, int sensorConfig);
int sensorGet(Sensor sensor);

//////////
//Motors//
//////////

typedef struct {
	unsigned char port;
	SensorType encoderType;
	union {
		QuadEncoder quadEncoder;
		IntegratedEncoder ime;
	} encoder;
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

Motor createMotor(MotorPort port, bool reversed);
Motor createMotorWithIME(MotorPort port, bool reversed, IntegratedEncoder encoder);
Motor createMotorWithEncoder(MotorPort port, bool reversed, QuadEncoder encoder);
void resetMotorEncoder(Motor motor);
int readMotorEncoder(Motor motor);
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
void pidControllerSetIntegralSpeedBounds(PIDController *controller,
		float integral_min, float integral_max);
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
