#include "main.h"

//////////
//Motors//
//////////

unsigned char connectedIntegratedMotorEncoders;

void motorPowerSet(Motor motor, int speed, AccessID id) {
	if (motorCheckAccessWithID(motor, id)) {
		if (motor.reversed) {
			speed = -speed;
		}
		motorSet(motor.port, speed);
	}
}

void motorArrayPowerSet(int numMotors, Motor motors[], int speed, AccessID id) {
	if (motorArrayCheckAccessWithID(numMotors, motors, id)) {
		for (int i = 0; i < numMotors; i++) {
			if (motors[i].reversed) {
				speed = -speed;
			}
			motorSet(motors[i].port, speed);
		}
	}
}

//timeout is the length of time to wait until the function can take control of the motor
// -1 is infinite
AccessID motorTakeControl(Motor motor) {
	if (motor.id == MOTOR_RELEASED_STATE) {
		motor.id = (AccessID) rand();
		return motor.id;
	} else {
		return MOTOR_ALREADY_TAKEN;
	}
}

AccessID motorArrayTakeControl(int numMotors, Motor motors[]) {
	AccessID id = (AccessID) rand();
	for (int i = 0; i < numMotors; i++) {
		if (motors[i].id != MOTOR_RELEASED_STATE) {
			return MOTOR_ALREADY_TAKEN;
		}
	}
	for (int i = 0; i < numMotors; i++) {
		motors[i].id = id;
	}
	return id;
}

void motorReleaseControl(Motor motor) {
	motor.id = MOTOR_RELEASED_STATE;
}

void motorArrayReleaseControl(int numMotors, Motor motors[]) {
	for (int i = 0; i < numMotors; i++) {
		motorReleaseControl(motors[i]);
	}
}

bool motorCheckAccessWithID(Motor motor, AccessID id) {
	return (id == motor.id || motor.id == MOTOR_RELEASED_STATE);
}

bool motorArrayCheckAccessWithID(int numMotors, Motor motors[], AccessID id) {
	for (int i = 0; i < numMotors; i++) {
		if (!motorCheckAccessWithID(motors[i], id)) {
			return false;
		}
	}
	return true;
}

Motor motorCreate(MotorPort port, bool reversed) {
	Motor motor;
	motor.id = MOTOR_RELEASED_STATE
	;
	motor.port = port;
	motor.reversed = reversed;
	return motor;
}

//Integrated motor encoders closest to the cortex in the chain get assigned an address of 0
//encoders futher down the line get an address that is incremented down the line
//so the next further one from the cortex would be 1 then 2 then 3 etc.
Motor motorCreateWithEncoder(MotorPort port, bool reversed, Sensor *encoder) {
	Motor motor;
	motor.id = MOTOR_RELEASED_STATE
	;
	motor.port = port;
	motor.reversed = reversed;
	switch (encoder->type) {
	case Sensor_IntegratedEncoder:
		motor.encoderType = Sensor_IntegratedEncoder;
		break;
	case Sensor_QuadEncoder:
		motor.encoderType = Sensor_QuadEncoder;
		break;
	default:
//invalid sensor
		print("Invalid encoder for use with a motor.\n\r");
		break;
	}
	motor.encoder_data = *encoder;
	return motor;
}

int motorEncoderGet(Motor motor) {
	int value = 0;
	switch (motor.encoderType) {
	case Sensor_IntegratedEncoder:
		value = sensorGet(motor.encoder_data);
		break;
	case Sensor_QuadEncoder:
		value = sensorGet(motor.encoder_data);
		break;
	default:
		print("Invalid Encoder Type!\n\r");
		break;
	}
	return value;
}

Sensor* motorEncoderGetPointer(Motor *motor) {
	switch (motor->encoderType) {
	case Sensor_QuadEncoder:
		return &(motor->encoder_data);
		break;
	default:
		print("Invalid Encoder Type!\n\r");
		return NULL ;
		break;
	}
	return NULL ;
}
