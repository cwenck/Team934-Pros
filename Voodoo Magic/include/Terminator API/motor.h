#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"
#include "sensors.h"

//////////
//Motors//
//////////

#define MOTOR_RELEASED_STATE -1
#define MOTOR_ALREADY_TAKEN -2

struct _Motor {
	AccessID id;
	unsigned char port;
	SensorType encoderType;
	Sensor encoder_data;
	bool reversed;
};

//vars
extern unsigned char connectedIntegratedMotorEncoders;

//functions
void motorPowerSet(Motor motor, int speed, AccessID id);
void motorArrayPowerSet(int numMotors, Motor motors[], int speed, AccessID id);

AccessID motorTakeControl(Motor motor);
AccessID motorArrayTakeControl(int numMotors, Motor motors[]) ;
void motorReleaseControl(Motor motor);
void motorArrayReleaseControl(int numMotors, Motor motors[]);

bool motorCheckAccessWithID(Motor motor, AccessID id);
bool motorArrayCheckAccessWithID(int numMotors, Motor motors[], AccessID id);

Motor motorCreate(MotorPort port, bool reversed);
Motor motorCreateWithEncoder(MotorPort port, bool reversed, Sensor *encoder);
void motorEncoderReset(Motor motor);
int motorEncoderGet(Motor motor);
Sensor* motorEncoderGetPointer(Motor *motor);

#endif /* MOTOR_H_ */
