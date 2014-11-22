#ifndef SENSORS_H_
#define SENSORS_H_

///////////
//Sensors//
///////////

#include "main.h"

typedef enum SensorType{
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

typedef enum MotorPort{
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

typedef enum IMEAddr{
	IME_1 = 0,
	IME_2 = 1,
	IME_3 = 2,
	IME_4 = 3,
	IME_5 = 4,
	IME_6 = 5,
	IME_7 = 6,
	IME_8 = 7
} IMEAddr;

typedef enum SensorPort{
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
	Digital_12 = 12,
	Analog_1 = 13,
	Analog_2 = 14,
	Analog_3 = 15,
	Analog_4 = 16,
	Analog_5 = 17,
	Analog_6 = 18,
	Analog_7 = 19,
	Analog_8 = 20
} SensorPort;

typedef struct CortexPort{
	SensorPort port;
	unsigned char mode;
	bool analogCapabilites;
} CortexPort;

typedef struct IntegratedEncoder{
	IMEAddr imeAddress;
	bool inverted;
} IntegratedEncoder;

typedef struct QuadEncoder{
	SensorPort top;
	SensorPort bottom;
	Encoder encoder_data;
	bool inverted;
} QuadEncoder;

typedef struct PushButton{
	SensorPort port;
	bool inverted;
} PushButton;

typedef struct AnalogSensor{
	SensorPort port;
} AnalogSensor;

//typedef struct {
//	DigitalPort port;
//} Jumper;

typedef struct Sensor{
	SensorType type;

	SensorPort port_1;
	//Only used for Sonar and Quadrature encoders
	//order does not matter for the quadrature encoder,
	//it only reverses the direction of the rotation
	//This should be NULL if it is not one of those two sensor types.
	SensorPort port_2;
	IMEAddr imeAddr;
	bool isAnalog;
	bool inverted;
	union {
		IntegratedEncoder ime;
		QuadEncoder quadEncoder;
		PushButton pushButton;
		Ultrasonic sonar;
		AnalogSensor analog;
	} sensorData;
} Sensor;

void cortexPortsInit();
CortexPort* cortexPortForSensorPort(SensorPort port);

bool portIsAnalog(SensorPort port);
void portSetPinMode(SensorPort port, unsigned char mode);
int portRead(SensorPort port);
void portWrite(SensorPort port, bool value);

//used for Bumpers and limit switches
PushButton pushButtonInit(SensorPort port, bool inverted);
bool pushButtonPressed(PushButton pushButton);

AnalogSensor analogSensorInit(SensorPort port);
int analogSensorGet(AnalogSensor sensor);

QuadEncoder quadEncoderInit(SensorPort topPort, SensorPort bottomPort,
		bool inverted);
int quadEncoderGet(QuadEncoder encoder);
void quadEncoderReset(QuadEncoder encoder);
int revolutionsToQuadEncoderCounts(float rotations);
//wheelDiameter is in inches
int inchesToQuadEncoderCounts(float inches, int wheelDiameter);
//wheelDiameter is in inches
int feetToQuadEncoderCounts(float feet, int wheelDiameter);

IntegratedEncoder integratedEncoderInit(IMEAddr port, bool inverted);
int integratedEncoderGet(IntegratedEncoder encoder);
void integratedEncoderReset(IntegratedEncoder encoder);
int revolutionsToIntegratedEncoderCounts(float rotations);
//wheelDiameter is in inches
int inchesToIntegratedEncoderCounts(float inches, int wheelDiameter);
//wheelDiameter is in inches
int feetToIntegratedEncoderCounts(float feet, int wheelDiameter);

Sensor sensorInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted);
Sensor sensorInitFromIntegratedEncoder(IntegratedEncoder *encoder);
Sensor sensorInitFromQuadEncoder(QuadEncoder *encoder);
int sensorGet(Sensor sensor);

#endif /* SENSORS_H_ */
