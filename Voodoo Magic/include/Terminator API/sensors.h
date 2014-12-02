#ifndef SENSORS_H_
#define SENSORS_H_

///////////
//Sensors//
///////////

#include "main.h"
#include "motor.h"

#define PORT_INCORRECT_PIN_MODE -1;

enum _SensorType{
	Sensor_IntegratedEncoder,	//IC2
	Sensor_QuadEncoder,			//Digital
	Sensor_Sonar,				//Digital
	Sensor_Line,				//Analog
	Sensor_Light,				//Analog
	Sensor_Bumper,				//Digital
	Sensor_LimitSwitch,			//Digital
	Sensor_Potentiometer,		//Analog
	Sensor_Gyroscope,			//Analog
	Sensor_Accelerometer		//Analog
};

enum _MotorPort{
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
};

enum _IMEAddr{
	IME_1 = 0,
	IME_2 = 1,
	IME_3 = 2,
	IME_4 = 3,
	IME_5 = 4,
	IME_6 = 5,
	IME_7 = 6,
	IME_8 = 7
};

enum _SensorPort{
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
};

struct _CortexPort{
	SensorPort port;
	unsigned char mode;
	bool analogCapabilites;
};

enum _MotorType {
	high_speed, high_torque
};

struct _IntegratedEncoder{
	IMEAddr imeAddress;
	MotorType motorType;
	bool inverted;
};

struct _QuadEncoder{
	SensorPort top;
	SensorPort bottom;
	Encoder encoder_data;
	bool inverted;
};

struct _PushButton{
	SensorPort port;
	bool inverted;
};

struct _AnalogSensor{
	SensorPort port;
};

//typedef struct {
//	DigitalPort port;
//} Jumper;

struct _Sensor{
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
};

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

void integratedEncoderPrimaryInitialization();
void integratedEncoderResetAll();
IntegratedEncoder integratedEncoderInit(IMEAddr port, MotorType motorType, bool inverted);
int integratedEncoderGet(IntegratedEncoder encoder);
void integratedEncoderReset(IntegratedEncoder encoder);
int revolutionsToIntegratedEncoderCounts(MotorType type, float rotations);
//wheelDiameter is in inches
int inchesToIntegratedEncoderCounts(MotorType type, float inches, int wheelDiameter);
//wheelDiameter is in inches
int feetToIntegratedEncoderCounts(MotorType type, float feet, int wheelDiameter);

Sensor sensorInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted);
Sensor sensorInitIntegratedEncoder(IMEAddr addr, MotorType type, bool inverted);
int sensorGet(Sensor sensor);
void sensorReset(Sensor sensor);

#endif /* SENSORS_H_ */
