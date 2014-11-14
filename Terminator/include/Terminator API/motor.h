#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"

//////////
//Motors//
//////////

typedef struct {
	unsigned char port;
	SensorType encoderType;
	union {
		QuadEncoder quadEncoder;
		IntegratedEncoder ime;
	} encoder_data;
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
int motorEncoderGet(Motor motor);

#endif /* MOTOR_H_ */
