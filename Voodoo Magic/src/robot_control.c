#include "main.h"

////////////////////////////
////////////////////////////
void handleAllInput() {
	handleDriveOrStrafing();
	handleLiftInput();
}
////////////////////////////
////////////////////////////

////////
//Lift//
////////

const short liftHighPower = 127;
const short liftLowPower = 80;

void setLiftPower(int speed, MotorAccessController controller) {
	motorArrayPowerSet(NUM_LIFT_MOTORS, liftMotors, speed, controller);
}

void handleLiftInput() {
	motorArrayTakeControl(NUM_LIFT_MOTORS, liftMotors,
			MOTOR_JOYSTICK_CONTROLLED);
	{
		if (joystickRead(liftUp) == 1) {
			setLiftPower(liftHighPower, MOTOR_JOYSTICK_CONTROLLED);
		} else if (joystickRead(liftDown) == 1) {
			setLiftPower(-liftHighPower, MOTOR_JOYSTICK_CONTROLLED);
		} else {
			setLiftPower(0, MOTOR_JOYSTICK_CONTROLLED);
		}
	}
	motorArrayReleaseControl(NUM_LIFT_MOTORS, liftMotors);
}

/////////
//Drive//
/////////

const int DRIVE_THRESHOLD = 10;

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setRightMotorSpeed(int speed, WheelDirection dir,
		MotorAccessController controller) {
	if (dir == same) {
		motorPowerSet(frontRightWheel, speed, controller);
		motorPowerSet(backRightWheel, speed, controller);
	} else if (dir == towards) {
		speed = abs(speed);
		motorPowerSet(frontRightWheel, -speed, controller);
		motorPowerSet(backRightWheel, speed, controller);
	} else if (dir == away) {
		speed = abs(speed);
		motorPowerSet(frontRightWheel, speed, controller);
		motorPowerSet(backRightWheel, -speed, controller);
	}
}

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setLeftMotorSpeed(int speed, WheelDirection dir,
		MotorAccessController controller) {
	if (dir == same) {
		motorPowerSet(frontLeftWheel, speed, controller);
		motorPowerSet(backLeftWheel, speed, controller);
	} else if (dir == towards) {
		speed = abs(speed);
		motorPowerSet(frontLeftWheel, -speed, controller);
		motorPowerSet(backLeftWheel, speed, controller);
	} else if (dir == away) {
		speed = abs(speed);
		motorPowerSet(frontLeftWheel, speed, controller);
		motorPowerSet(backLeftWheel, -speed, controller);
	}
}

/*
 * Strafe left and right at a particular speed
 * or move forawrd or backward
 */
void strafe(int speed, Direction dir, MotorAccessController controller) {
	speed = abs(speed);
	if (dir == left) {
		setLeftMotorSpeed(speed, towards, controller);
		setRightMotorSpeed(speed, away, controller);
	} else if (dir == right) {
		setLeftMotorSpeed(speed, away, controller);
		setRightMotorSpeed(speed, towards, controller);
	} else if (dir == forward) {
		setLeftMotorSpeed(speed, same, controller);
		setRightMotorSpeed(speed, same, controller);
	} else if (dir == backward) {
		setLeftMotorSpeed(-speed, same, controller);
		setRightMotorSpeed(-speed, same, controller);
	}
}

/*
 * Drive forward or backward or turn left or turn right at a particular speed
 */

void drive(int speed, Direction dir, MotorAccessController controller) {
	motorArrayTakeControl(NUM_DRIVE_MOTORS, driveMotors, controller);
	speed = abs(speed);
	if (dir == left) {
		setLeftMotorSpeed(-speed, same, controller);
		setRightMotorSpeed(speed, same, controller);
	} else if (dir == right) {
		setLeftMotorSpeed(speed, same, controller);
		setRightMotorSpeed(-speed, same, controller);
	} else if (dir == forward) {
		setLeftMotorSpeed(speed, same, controller);
		setRightMotorSpeed(speed, same, controller);
	} else if (dir == backward) {
		setLeftMotorSpeed(-speed, same, controller);
		setRightMotorSpeed(-speed, same, controller);
	}
	motorArrayReleaseControl(NUM_DRIVE_MOTORS, driveMotors);
}

void handleDriveInput() {
	int y = joystickRead(forward_backward_drive);
	int x = joystickRead(left_right_drive);

	motorArrayTakeControl(NUM_DRIVE_MOTORS, driveMotors, MOTOR_JOYSTICK_CONTROLLED);

	if (abs(y) > abs(x)) {
		setLeftMotorSpeed(y, same, MOTOR_RELEASED_STATE);
		setRightMotorSpeed(y, same, MOTOR_RELEASED_STATE);
	} else if (abs(x) >= abs(y)) {
		setLeftMotorSpeed(x, same, MOTOR_RELEASED_STATE);
		setRightMotorSpeed(-x, same, MOTOR_RELEASED_STATE);
	}

	motorArrayReleaseControl(NUM_DRIVE_MOTORS, driveMotors);
}

void handleStrafingInput() {
	if (abs(
			joystickRead(forward_backward_strafe)
					> abs(joystickRead(left_right_strafe)))) {
		if (joystickRead(forward_backward_strafe) > 0) {
			strafe(joystickRead(forward_backward_strafe), forward,
					MOTOR_RELEASED_STATE);
		} else {
			strafe(joystickRead(forward_backward_strafe), backward,
					MOTOR_RELEASED_STATE);
		}
	} else {
		if (joystickRead(left_right_strafe) > 0) {
			strafe(joystickRead(left_right_strafe), right,
					MOTOR_RELEASED_STATE);
		} else {
			strafe(joystickRead(left_right_strafe), left, MOTOR_RELEASED_STATE);
		}
	}
}

//Decides whether to drive or strafe
void handleDriveOrStrafing() {
	if (abs(joystickRead(forward_backward_drive)) <= DRIVE_THRESHOLD
			&& abs(joystickRead(left_right_drive)) <= DRIVE_THRESHOLD) {
		handleStrafingInput();
	} else if (abs(joystickRead(forward_backward_drive)) > DRIVE_THRESHOLD
			|| abs(joystickRead(left_right_drive)) > DRIVE_THRESHOLD) {
		handleDriveInput();
	}
}

//Lift Distance to encoder Ticks
float liftEncoderTicksPerInch = 88;
float ticksTillIntakeUncompressed = 220;
float maxLiftEncoderTicks = 3700;
int inchesToLiftEncoderTicks(float inches) {
	int value = sensorGet(liftEncoder);
	int ticks = 0;

	if (value > ticksTillIntakeUncompressed) {
		ticks = ticksTillIntakeUncompressed
				+ (int) (inches * liftEncoderTicksPerInch);
	} else {
		ticks = ticksTillIntakeUncompressed
				+ (int) (inches * liftEncoderTicksPerInch);
	}

	if (ticks > maxLiftEncoderTicks) {
		ticks = maxLiftEncoderTicks;
	}

	return ticks;
}
int feetToLiftEncoderTicks(float feet) {
	int value = sensorGet(liftEncoder);
	int ticks = 0;

	if (value > ticksTillIntakeUncompressed) {
		ticks = ticksTillIntakeUncompressed
				+ (int) (feet * liftEncoderTicksPerInch * 12);
	} else {
		ticks = ticksTillIntakeUncompressed
				+ (int) (feet * liftEncoderTicksPerInch * 12);
	}

	if (ticks > maxLiftEncoderTicks) {
		ticks = maxLiftEncoderTicks;
	}

	return ticks;
}

///////////////////////////////////
//PID Controllable Drive Funtions//
///////////////////////////////////

void driveForwardBackward(int speed, MotorAccessController controller) {
	if (speed >= 0) {
		drive(speed, forward, controller);
	} else {
		drive(speed, backward, controller);
	}
}

void turnLeftRight(int speed, MotorAccessController controller) {
	if (speed >= 0) {
		drive(speed, right, controller);
	} else {
		drive(speed, left, controller);
	}
}

void strafeLeftRight(int speed, MotorAccessController controller) {
	if (speed >= 0) {
		strafe(speed, right, controller);
	} else {
		strafe(speed, left, controller);
	}
}
