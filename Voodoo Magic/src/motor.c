#include "main.h"
#include "Terminator API/motor_control_priorities.h"

//////////
//Motors//
//////////

unsigned char connectedIntegratedMotorEncoders;

MotorAccessController MOTOR_RELEASED_STATE;
MotorAccessController MOTOR_JOYSTICK_CONTROLLED;
MotorAccessController MOTOR_PID_CONTROLLED;
MotorAccessController MOTOR_AUTONOMOUS_CONTROLLED;

void motorAccessControllerInit(MotorAccessController *controller, AccessID id,
		PriorityLevel priorityLevel) {
	controller->id = id;
	controller->priority = priorityLevel;
}

void motorAccessControllersInit() {
	motorAccessControllerInit(&MOTOR_RELEASED_STATE, 0,
			MOTOR_PRIORETY_CONTROL_RELEASED);
	motorAccessControllerInit(&MOTOR_JOYSTICK_CONTROLLED, 1,
			MOTOR_PRIORETY_CONTROL_LOWEST);
	motorAccessControllerInit(&MOTOR_PID_CONTROLLED, 2,
			MOTOR_PRIORETY_CONTROL_HIGHEST);
	motorAccessControllerInit(&MOTOR_AUTONOMOUS_CONTROLLED, 3, MOTOR_PRIORETY_CONTROL_HIGHEST);
}

void motorInit() {
	motorAccessControllersInit();
	liftMotors[0] = topLeftLift;
	liftMotors[1] = middleLeftLift;
	liftMotors[2] = bottomLeftLift;
	liftMotors[3] = topRightLift;
	liftMotors[4] = middleRightLift;
	liftMotors[5] = bottomRightLift;

	driveMotors[0] = frontRightWheel;
	driveMotors[1] = backRightWheel;
	driveMotors[2] = frontLeftWheel;
	driveMotors[3] = backLeftWheel;
}

MotorAccessController motorGetAccessControllerFromID(AccessID id) {
	switch (id) {
	case 0:
		return MOTOR_RELEASED_STATE;
	case 1:
		return MOTOR_JOYSTICK_CONTROLLED;
	case 2:
		return MOTOR_PID_CONTROLLED;
	case 3:
		return MOTOR_AUTONOMOUS_CONTROLLED;
	}
	return *((MotorAccessController *) NULL );
}

PriorityLevel motorGetPriorityLevelFromAccessControllerById(AccessID id) {
	return motorGetAccessControllerFromID(id).priority;
}

PriorityLevel motorGetPriorityLevelFromAccessController(
		MotorAccessController controller) {
	return controller.priority;
}

void motorPowerSet(Motor motor, int speed, MotorAccessController controller) {
	if (motorCheckAccessWithID(motor, controller.id)) {
		if (motor.reversed) {
			speed = -speed;
		}
		motorSet(motor.port, speed);
	}
}

void motorArrayPowerSet(int numMotors, Motor motors[], int speed,
		MotorAccessController controller) {
	if (motorArrayCheckAccessWithID(numMotors, motors, controller.id)) {
		for (int i = 0; i < numMotors; i++) {
			if (motors[i].reversed) {
				speed = -speed;
			}
//			printf("Motors[%d]\n\r", motors[i].port);
			motorSet(motors[i].port, speed);
		}
	}
}

bool motorCanBeTakenByMotorAccessController(Motor motor,
		MotorAccessController controller) {
	if (motor.id == controller.id) {
		return true;
	} else if (motorGetAccessControllerFromID(motor.id).priority
			> controller.priority) {
		return true;
	} else {
		return false;
	}
}

//returns true if control was successfully taken
bool motorTakeControl(Motor motor, MotorAccessController controller) {
	if (motorCanBeTakenByMotorAccessController(motor, controller)) {
		motor.id = controller.id;
		return true;
	} else {
		return false;
	}
}

//returns true if control was successfully taken
bool motorArrayTakeControl(int numMotors, Motor motors[],
		MotorAccessController controller) {
	for (int i = 0; i < numMotors; i++) {
		if (!motorCanBeTakenByMotorAccessController(motors[i], controller)) {
			return false;
		}
	}
	for (int i = 0; i < numMotors; i++) {
		motorTakeControl(motors[i], controller);
	}
	return true;
}

void motorReleaseControl(Motor motor) {
	motor.id = MOTOR_RELEASED_STATE.id;
}

void motorArrayReleaseControl(int numMotors, Motor motors[]) {
	for (int i = 0; i < numMotors; i++) {
		motorReleaseControl(motors[i]);
	}
}

bool motorCheckAccessWithID(Motor motor, AccessID id) {
	return (id == motor.id || motor.id == MOTOR_RELEASED_STATE.id);
}

bool motorCheckAccessWithAccessController(Motor motor,
		MotorAccessController controller) {
	return motorCheckAccessWithID(motor, controller.id);
}

bool motorArrayCheckAccessWithID(int numMotors, Motor motors[], AccessID id) {
	for (int i = 0; i < numMotors; i++) {
		if (!motorCheckAccessWithID(motors[i], id)) {
			return false;
		}
	}
	return true;
}

bool motorArrayCheckAccessWithAccessController(int numMotors, Motor motors[],
		MotorAccessController controller) {
	return motorArrayCheckAccessWithID(numMotors, motors, controller.id);
}

Motor motorCreate(MotorPort port, bool reversed) {
	Motor motor;
	motor.id = MOTOR_RELEASED_STATE.id;
	motor.port = port;
	motor.reversed = reversed;
	return motor;
}

//Integrated motor encoders closest to the cortex in the chain get assigned an address of 0
//encoders futher down the line get an address that is incremented down the line
//so the next further one from the cortex would be 1 then 2 then 3 etc.
Motor motorCreateWithEncoder(MotorPort port, bool reversed, Sensor *encoder) {
	Motor motor;
	motor.id = MOTOR_RELEASED_STATE.id;
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
