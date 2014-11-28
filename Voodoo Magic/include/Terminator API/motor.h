#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"
#include "sensors.h"

//////////
//Motors//
//////////

struct _Motor {
	unsigned char port;
	SensorType encoderType;
	Sensor encoder_data;
	bool reversed;
};

//vars
extern unsigned char connectedIntegratedMotorEncoders;

//functions
void motorPowerSet(Motor motor, int speed);

Motor motorCreate(MotorPort port, bool reversed);
Motor motorCreateWithEncoder(MotorPort port, bool reversed, Sensor *encoder);
void motorEncoderReset(Motor motor);
int motorEncoderGet(Motor motor);
Sensor* motorEncoderGetPointer(Motor *motor);

#endif /* MOTOR_H_ */
