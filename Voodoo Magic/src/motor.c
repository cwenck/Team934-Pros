#include "main.h"

//////////
//Motors//
//////////

void setMotorPower(Motor motor, int speed) {
	if (motor.reversed) {
		speed = -speed;
	}
	motorSet(motor.port, speed);
}

Motor createMotor(MotorPort port, bool reversed) {
	Motor motor;
	motor.port = port;
	motor.reversed = reversed;
	motor.encoderType = NULL;
	return motor;
}

//Integrated motor encoders closest to the cortex in the chain get assigned an address of 0
//encoders futher down the line get an address that is incremented down the line
//so the next further one from the cortex would be 1 then 2 then 3 etc.
Motor createMotorWithIME(MotorPort port, bool reversed,
		IntegratedEncoder *encoder) {
	Motor motor;
	motor.port = port;
	motor.reversed = reversed;
	motor.encoder_data.ime = *encoder;
	motor.encoderType = QuadratureEncoder;
	return motor;
}

Motor createMotorWithEncoder(MotorPort port, bool reversed,
		QuadEncoder *encoder) {
	Motor motor;
	motor.port = port;
	motor.reversed = reversed;
	motor.encoder_data.quadEncoder = *encoder;
	motor.encoderType = QuadratureEncoder;
	return motor;
}

void resetMotorEncoder(Motor motor) {
	switch (motor.encoderType) {
	case IntegratedMotorEncoder:
		integratedEncoderReset(motor.encoder_data.ime);
		break;
	case QuadratureEncoder:
		quadEncoderReset(motor.encoder_data.quadEncoder);
		break;
	default:
		print("Invalid Encoder Type!\n\r");
		break;
	}
}

int motorEncoderGet(Motor motor) {
	int value = NULL;
	switch (motor.encoderType) {
	case IntegratedMotorEncoder:
		value = integratedEncoderGet(motor.encoder_data.ime);
		break;
	case QuadratureEncoder:
		value = quadEncoderGet(motor.encoder_data.quadEncoder);
		break;
	default:
		print("Invalid Encoder Type!\n\r");
		break;
	}
	return value;
}

QuadEncoder* motorQuadEncoderGetPointer(Motor *motor) {
	switch (motor->encoderType) {
	case QuadratureEncoder:
		return &(motor->encoder_data.quadEncoder);
		break;
	default:
		print("Invalid Encoder Type!\n\r");
		return NULL;
		break;
	}
	return NULL;
}

IntegratedEncoder* motorIntegratedEncoderGetPointer(Motor *motor) {
	switch (motor->encoderType) {
	case IntegratedMotorEncoder:
		return &(motor->encoder_data.ime);
		break;
	default:
		print("Invalid Encoder Type!\n\r");
		return NULL;
		break;
	}
	return NULL;
}

//DRIVE_THRESHOLD
