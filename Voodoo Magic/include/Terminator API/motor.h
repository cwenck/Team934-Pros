#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"
#include "motor_control_priorities.h"
#include "sensors.h"

//////////
//Motors//
//////////

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

void motorInit();
void motorPowerSet(Motor motor, int speed, MotorAccessController controller);
void motorArrayPowerSet(int numMotors, Motor motors[], int speed, MotorAccessController controller);

bool motorTakeControl(Motor motor, MotorAccessController controller);
bool motorArrayTakeControl(int numMotors, Motor motors[], MotorAccessController controller) ;
void motorReleaseControl(Motor motor);
void motorArrayReleaseControl(int numMotors, Motor motors[]);

bool motorCheckAccessWithID(Motor motor, AccessID id);
bool motorCheckAccessWithAccessController(Motor motor, MotorAccessController controller);
bool motorArrayCheckAccessWithID(int numMotors, Motor motors[], AccessID id);
bool motorArrayCheckAccessWithAccessController(int numMotors, Motor motors[], MotorAccessController controller);

Motor motorCreate(MotorPort port, bool reversed);
Motor motorCreateWithEncoder(MotorPort port, bool reversed, Sensor *encoder);
void motorEncoderReset(Motor motor);
int motorEncoderGet(Motor motor);
Sensor* motorEncoderGetPointer(Motor *motor);

#endif /* MOTOR_H_ */
