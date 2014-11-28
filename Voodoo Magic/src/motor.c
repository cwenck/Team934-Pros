#include "main.h"

//////////
//Motors//
//////////

unsigned char connectedIntegratedMotorEncoders;

void motorPowerSet(Motor motor, int speed) {
	if (motor.reversed) {
		speed = -speed;
	}
	motorSet(motor.port, speed);
}

Motor motorCreate(MotorPort port, bool reversed) {
	Motor motor;
	motor.port = port;
	motor.reversed = reversed;
	motor.encoderType = NULL;
	return motor;
}

//Integrated motor encoders closest to the cortex in the chain get assigned an address of 0
//encoders futher down the line get an address that is incremented down the line
//so the next further one from the cortex would be 1 then 2 then 3 etc.
Motor motorCreateWithEncoder(MotorPort port, bool reversed, Sensor *encoder) {
	Motor motor;
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
	int value = NULL;
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
		return NULL;
		break;
	}
	return NULL;
}
