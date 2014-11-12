#include "main.h"

/////////////
//Variables//
/////////////

//Lift liftEncoder
Encoder liftEncoder;

//Init Drive Motors
Motor frontLeftWheel;
Motor frontRightWheel;
Motor backLeftWheel;
Motor backRightWheel;

//Init Lift Motors
Motor frontLeftLift;
Motor backLeftLift;
Motor frontRightLift;
Motor backRightLift;

//Init Controller Buttons
JoyInput liftUp;
JoyInput liftDown;

JoyInput forward_backward_drive;
JoyInput left_right_drive;
JoyInput forward_backward_strafe;
JoyInput left_right_strafe;

void handleAllInput() {
	handleDriveOrStrafing();
	handleLiftInput();
}

////////////
//Joystick//
////////////

JoyInput createButton(unsigned char channel, unsigned char btn) {
	JoyInput button;
	button.channel = channel;
	button.btn = btn;
	button.onPartnerJoystick = false;
	return button;
}

JoyInput createButtonOnPartnerJoystick(unsigned char channel, unsigned char btn) {
	JoyInput button;
	button.channel = channel;
	button.btn = btn;
	button.onPartnerJoystick = true;
	return button;
}

JoyInput createAxis(unsigned char channel) {
	JoyInput button;
	button.channel = channel;
	button.btn = NULL;
	button.onPartnerJoystick = false;
	return button;
}

JoyInput createAxisOnPartnerJoystick(unsigned char channel) {
	JoyInput button;
	button.channel = channel;
	button.btn = NULL;
	button.onPartnerJoystick = true;
	return button;
}

unsigned char getNumConnectedJoysticks() {
	unsigned char joysticksConnected = 0;
	if (isJoystickConnected(1)) {
		joysticksConnected++;
	}
	if (isJoystickConnected(2)) {
		joysticksConnected++;
	}
	return joysticksConnected;
}

//If it is a button a 1 is returned for true and 0 for false
//otherwise a value between -127 and 127 is returned for the particular axis
int readJoystick(JoyInput button) {
	unsigned char joy = 1;
	if (button.onPartnerJoystick) {
		joy = 2;
	}
	if (button.channel == 1 || button.channel == 2 || button.channel == 3
			|| button.channel == 4) {
		return joystickGetAnalog(joy, button.channel);
	} else {
		if (joystickGetDigital(joy, button.channel, button.btn)) {
			return 1;
		} else {
			return 0;
		}
	}
}


///////////
//Sensors//
///////////

// Init limit switch / bumpers in initializeIO()
PushButton pushButtonInit(DigitalPort port) {
	PushButton limitSwitch;
	limitSwitch.port = port;
	pinMode(limitSwitch.port, INPUT);
	return limitSwitch;
}

// digitalRead() returns LOW if Pressed or HIGH if released
// the function returns true if the bumper/limit switch is pressed
bool bumpPressed(PushButton limitSwitch) {
	if (digitalRead(limitSwitch.port) == LOW) {
		return true;
	}
	return false;
}

AnalogSensor analogSensorInit(AnalogPort port, bool inverted) {
	AnalogSensor sensor;
	sensor.port = port;
	sensor.inverted = inverted;
	return sensor;
}

int analogSensorGet(AnalogSensor sensor) {
	if (!sensor.inverted) {
		return analogRead(sensor.port);
	} else {
		return -analogRead(sensor.port);
	}
}

QuadEncoder quadEncoderInit(DigitalPort topPort, DigitalPort bottomPort, bool inverted){
	QuadEncoder quad;
	quad.encoder_data = encoderInit(topPort, bottomPort, false);
	quad.inverted = inverted;
	return quad;
}

int quadEncoderGet(QuadEncoder encoder){
	int value = encoderGet(encoder.encoder_data);
	if(encoder.inverted){
		value = - value;
	}
	return value;
}

void quadEncoderReset(QuadEncoder encoder){
	encoderReset(encoder.encoder_data);
}

IntegratedEncoder integratedEncoderInit(IMEPort port, bool inverted){
	IntegratedEncoder ime;
	ime.imeAddress = port;
	ime.inverted = inverted;
	return ime;
}
int integratedencoderGet(IntegratedEncoder encoder){
	int value;
	imeGet(encoder.imeAddress, &value);
	if(encoder.inverted){
		value = - value;
	}
	return value;
}

void integratedEncoderReset(IntegratedEncoder encoder){
	imeReset(encoder.imeAddress);
}

//sensorConfig is used to set the multiplier for the gyro sensor
//if that is set as the sensor type. otherwise it does nothing.
//Call imeInitializeAll() before calling this function
Sensor sensorInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted, int sensorConfig) {
	Sensor sensor;
	sensor.type = type;
	sensor.port_1 = port_1;
	sensor.port_2 = port_2;
	sensor.inverted = inverted;


	switch (sensor.type) {
	case IntegratedMotorEncoder:
		sensor.inverted = inverted;
		break;
	case QuadratureEncoder:
		sensor.sensorData.quadEncoder = quadEncoderInit(sensor.port_1, sensor.port_2, false);
		break;
	case Sonar:
		sensor.sensorData.sonar = ultrasonicInit(sensor.port_1, sensor.port_2);
		break;
	case Line:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1, inverted);
		break;
	case Light:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1, inverted);
		break;
	case Push_Button:
		sensor.sensorData.pushButton = pushButtonInit(sensor.port_1);
		break;
	case Limit_Switch:
		sensor.sensorData.pushButton = pushButtonInit(sensor.port_1);
		break;
	case Potentiometer:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1, inverted);
		break;
	case Gyroscope:
		sensor.sensorData.gyro = gyroInit(sensor.port_1, sensorConfig);
		break;
	case Accelerometer:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1, inverted);
		break;
	}
	return sensor;
}

//if it is a limit switch or push button a 1 is returned if it is pressed
int sensorGet(Sensor sensor) {
	int value = NULL;

	switch (sensor.type) {
	case IntegratedMotorEncoder:
		value = integratedencoderGet(sensor.sensorData.ime);
		break;
	case QuadratureEncoder:
		value = quadEncoderGet(sensor.sensorData.quadEncoder);
		break;
	case Sonar:
		value = ultrasonicGet(sensor.sensorData.sonar);
		break;
	case Line:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Light:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Push_Button:
		value = bumpPressed(sensor.sensorData.pushButton);
		break;
	case Limit_Switch:
		value = bumpPressed(sensor.sensorData.pushButton);
		break;
	case Potentiometer:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Gyroscope:
		value = gyroGet(sensor.sensorData.gyro);
		break;
	case Accelerometer:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	}
	return value;
}

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
	motor.encoder_data = NULL;
	motor.encoderType = NULL;
	return motor;
}

//Integrated motor encoders closest to the cortex in the chain get assigned an address of 0
//encoders futher down the line get an address that is incremented down the line
//so the next further one from the cortex would be 1 then 2 then 3 etc.
Motor createMotorWithIME(MotorPort port, bool reversed,
		IntegratedEncoder encoder) {
	Motor motor;
	motor.port = port;
	motor.reversed = reversed;
	motor.encoder_data.ime = encoder;
	motor.encoderType = QuadratureEncoder;
	return motor;
}

Motor createMotorWithEncoder(MotorPort port, bool reversed,
		QuadEncoder encoder) {
	Motor motor;
	motor.port = port;
	motor.reversed = reversed;
	motor.encoder_data.quadEncoder = encoder;
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
	int value;
	switch (motor.encoderType) {
	case IntegratedMotorEncoder:
		value = integratedencoderGet(motor.encoder_data.ime);
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

////////
//Lift//
////////

const short liftHighPower = 127;
const short liftLowPower = 80;

void setLiftPower(int speed) {
	setMotorPower(frontLeftLift, speed);
	setMotorPower(backLeftLift, speed);
	setMotorPower(frontRightLift, speed);
	setMotorPower(backRightLift, speed);
}

void handleLiftInput() {
	if (readJoystick(liftUp) == 1) {
		setLiftPower(liftHighPower);
	} else if (readJoystick(liftDown) == 1) {
		setLiftPower(-liftHighPower);
	} else {
		setLiftPower(0);
	}
}

/////////
//Drive//
/////////

const int DRIVE_THRESHOLD = 5;

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setRightMotorSpeed(int speed, WheelDirection dir) {
	if (dir == same) {
		setMotorPower(frontRightWheel, speed);
		setMotorPower(backRightWheel, speed);
	} else if (dir == towards) {
		speed = abs(speed);
		setMotorPower(frontRightWheel, -speed);
		setMotorPower(backRightWheel, speed);
	} else if (dir == away) {
		speed = abs(speed);
		setMotorPower(frontRightWheel, speed);
		setMotorPower(backRightWheel, -speed);
	}
}

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setLeftMotorSpeed(int speed, WheelDirection dir) {
	if (dir == same) {
		setMotorPower(frontLeftWheel, speed);
		setMotorPower(backLeftWheel, speed);
	} else if (dir == towards) {
		speed = abs(speed);
		setMotorPower(frontLeftWheel, -speed);
		setMotorPower(backLeftWheel, speed);
	} else if (dir == away) {
		speed = abs(speed);
		setMotorPower(frontLeftWheel, speed);
		setMotorPower(backLeftWheel, -speed);
	}
}

/*
 * Strafe left and right at a particular speed
 * or move forawrd or backward
 */
void strafe(int speed, Direction dir) {
	speed = abs(speed);
	if (dir == left) {
		setLeftMotorSpeed(speed, towards);
		setRightMotorSpeed(speed, away);
	} else if (dir == right) {
		setLeftMotorSpeed(speed, away);
		setRightMotorSpeed(speed, towards);
	} else if (dir == forward) {
		setLeftMotorSpeed(speed, same);
		setRightMotorSpeed(speed, same);
	} else if (dir == backward) {
		setLeftMotorSpeed(-speed, same);
		setRightMotorSpeed(-speed, same);
	}
}

/*
 * Drive forward or backward or turn left or turn right at a particular speed
 */

void drive(int speed, Direction dir) {
	speed = abs(speed);
	if (dir == left) {
		setLeftMotorSpeed(-speed, same);
		setRightMotorSpeed(speed, same);
	} else if (dir == right) {
		setLeftMotorSpeed(speed, same);
		setRightMotorSpeed(-speed, same);
	} else if (dir == forward) {
		setLeftMotorSpeed(speed, same);
		setRightMotorSpeed(speed, same);
	} else if (dir == backward) {
		setLeftMotorSpeed(-speed, same);
		setRightMotorSpeed(-speed, same);
	}
}

void handleDriveInput() {
	int y = readJoystick(forward_backward_drive);
	int x = readJoystick(left_right_drive);

	if (abs(y) > abs(x)) {
		setLeftMotorSpeed(y, same);
		setRightMotorSpeed(y, same);
	} else if (abs(x) >= abs(y)) {
		setLeftMotorSpeed(x, same);
		setRightMotorSpeed(-x, same);
	}
}

void handleStrafingInput() {
	if (abs(
			readJoystick(forward_backward_strafe)
					> abs(readJoystick(left_right_strafe)))) {
		if (readJoystick(forward_backward_strafe) > 0) {
			strafe(readJoystick(forward_backward_strafe), forward);
		} else {
			strafe(readJoystick(forward_backward_strafe), backward);
		}
	} else {
		if (readJoystick(left_right_strafe) > 0) {
			strafe(readJoystick(left_right_strafe), right);
		} else {
			strafe(readJoystick(left_right_strafe), left);
		}
	}
}

//Decides whether to drive or strafe
void handleDriveOrStrafing() {
	if (abs(readJoystick(forward_backward_drive)) <= DRIVE_THRESHOLD
			&& abs(readJoystick(left_right_drive)) <= DRIVE_THRESHOLD) {
		handleDriveInput();
	} else {
		handleStrafingInput();
	}
}

///////
//PID//
///////

PIDController pidControllerInit(float kp, float ki, float kd,
		void (*setMotorSpeedFunction)(int), Sensor sensor) {
	PIDController pid;
	pid.kp = kp;
	pid.ki = ki;
	pid.kd = kd;
	pid.setMotorSpeedFunction = setMotorSpeedFunction;
	pid.ignoreIntegralBounds = true;
	pid.sensor = sensor;
	pid.integral_range = 1000;
	pidControllerSetIntegralSpeedBounds(&pid, 0, 127);
	return pid;
}

void pidControllerSetTarget(PIDController *controller, float target) {
	controller->sensor_target = target;
}

void pidIgnoreIntegralBounds(PIDController *controller) {
	controller->ignoreIntegralBounds = true;
}

void pidSetIntegralRange(PIDController *controller, float integralRange) {
	controller->integral_range = integralRange;
}

void pidControllerSetIntegralSpeedBounds(PIDController *controller,
		float integral_min, float integral_max) {
	controller->integral_min = integral_min / controller->ki;
	controller->integral_max = integral_max / controller->ki;
	controller->ignoreIntegralBounds = false;
}

void pidStart(PIDController *controller) {
	taskCreate(pidTask, TASK_DEFAULT_STACK_SIZE, controller,
			TASK_PRIORITY_DEFAULT);
}

void pidTask(void *controller) {
	PIDController pid = *((PIDController *) controller);
	pid.target_reached = false;
	while (!pid.target_reached) {
		pid.last_error = pid.error;
		pid.sensor_reading = sensorGet(pid.sensor);
		pid.error = pid.sensor_target - pid.sensor_reading;
		if (abs(pid.error) < pid.integral_range) {
			pid.integral += pid.error;
		} else {
			pid.integral = 0;
		}
		pid.derivative = pid.error - pid.last_error;

		if (!pid.ignoreIntegralBounds) {
			if (abs(pid.integral) > pid.integral_max) {
				if (pid.integral > 0) {
					pid.integral = pid.integral_max;
				} else {
					pid.integral = -pid.integral_max;
				}
			} else if (abs(pid.integral) < pid.integral_min) {
				if (pid.integral > 0) {
					pid.integral = pid.integral_min;
				} else {
					pid.integral = -pid.integral_min;
				}
			}
		}

		if (abs(pid.error) <= abs(pid.error_tolerance)) {
			pid.integral = 0;
			pid.num_checks_passed++;
			if (pid.num_checks_passed > 3) {
				pid.target_reached = true;
			}
		} else {
			pid.num_checks_passed = 0;
			pid.target_reached = false;
		}
		printf("Err: %.2f -- ISpd: %d -- I: %.2f\n\r", pid.error, pid.i_speed,
				pid.integral);
		pid.p_speed = pid.error * pid.kp;
		pid.i_speed = pid.integral * pid.ki;
		pid.d_speed = pid.derivative * pid.kd;
		pid.motor_speed = pid.p_speed + pid.i_speed + pid.d_speed;
		pid.setMotorSpeedFunction(pid.motor_speed);
		delay(20);
	}
}

/////////
//Other//
/////////

int capMotorPower(int value) {
	if (value > 127) {
		return 127;
	} else if (value < -127) {
		return -127;
	} else {
		return value;
	}
}

float getMainBatteryPower() {
	return ((float) powerLevelMain()) / 1000.0f;
}

void printMainBatteyPower() {
	printf("Main Battery: %.2fV", getMainBatteryPower());
}
