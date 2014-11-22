#ifndef SENSORS_H_
#define SENSORS_H_

///////////
//Sensors//
///////////

#include "main.h"

typedef enum {
	IntegratedMotorEncoder,	//IC2
	QuadratureEncoder,		//Digital
	Sonar,					//Digital
	Line,					//Analog
	Light,					//Analog
	Bumper,					//Digital
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
} IMEAddr;

typedef union {
	AnalogPort analogPort;
	DigitalPort digitalPort;
	IMEAddr imePort;
} SensorPort;

typedef struct {
	unsigned char imeAddress;
	bool inverted;
} IntegratedEncoder;

typedef struct {
	Encoder encoder_data;
	bool inverted;
} QuadEncoder;

typedef struct {
	unsigned char port;
} PushButton;

typedef struct {
	unsigned char port;
	bool inverted;
} AnalogSensor;

//typedef struct {
//	DigitalPort port;
//} Jumper;

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

//used for Bumpers and limit switches
PushButton pushButtonInit(DigitalPort port);
bool pushButtonPressed(PushButton pushButton);

AnalogSensor analogSensorInit(AnalogPort port, bool inverted);
int analogSensorGet(AnalogSensor sensor);


QuadEncoder quadEncoderInit(DigitalPort topPort, DigitalPort bottomPort, bool inverted);
int quadEncoderGet(QuadEncoder encoder);
void quadEncoderReset(QuadEncoder encoder);
int revolutionsToQuadEncoderCounts(float rotations);
//wheelDiameter is in inches
int inchesToQuadEncoderCounts(float inches, int wheelDiameter);
//wheelDiameter is in inches
int feetToQuadEncoderCounts(float feet, int wheelDiameter);


IntegratedEncoder integratedEncoderInit(IMEAddr port, bool inverted);
int integratedencoderGet(IntegratedEncoder encoder);
void integratedEncoderReset(IntegratedEncoder encoder);
int revolutionsToIntegratedEncoderCounts(float rotations);
//wheelDiameter is in inches
int inchesToIntegratedEncoderCounts(float inches, int wheelDiameter);
//wheelDiameter is in inches
int feetToIntegratedEncoderCounts(float feet, int wheelDiameter);


Sensor sensorInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted, int sensorConfig);
//void sensorInit(Sensor sensor, bool inverted, int sensorConfig);
int sensorGet(Sensor sensor);

#endif /* SENSORS_H_ */
