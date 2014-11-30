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

void setLiftPower(int speed, AccessID id) {
	Motor motors[6] = { topLeftLift, middleLeftLift, bottomLeftLift,
			topRightLift, middleRightLift, bottomRightLift };
	motorArrayPowerSet(6, motors, speed, id);
}

void handleLiftInput() {
	if (joystickRead(liftUp) == 1) {
		setLiftPower(liftHighPower, MOTOR_RELEASED_STATE);
	} else if (joystickRead(liftDown) == 1) {
		setLiftPower(-liftHighPower, MOTOR_RELEASED_STATE);
	} else {
		setLiftPower(0, MOTOR_RELEASED_STATE);
	}
}

/////////
//Drive//
/////////

const int DRIVE_THRESHOLD = 10;

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setRightMotorSpeed(int speed, WheelDirection dir, AccessID id) {
	if (dir == same) {
		motorPowerSet(frontRightWheel, speed, id);
		motorPowerSet(backRightWheel, speed, id);
	} else if (dir == towards) {
		speed = abs(speed);
		motorPowerSet(frontRightWheel, -speed, id);
		motorPowerSet(backRightWheel, speed, id);
	} else if (dir == away) {
		speed = abs(speed);
		motorPowerSet(frontRightWheel, speed, id);
		motorPowerSet(backRightWheel, -speed, id);
	}
}

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setLeftMotorSpeed(int speed, WheelDirection dir, AccessID id) {
	if (dir == same) {
		motorPowerSet(frontLeftWheel, speed, id);
		motorPowerSet(backLeftWheel, speed, id);
	} else if (dir == towards) {
		speed = abs(speed);
		motorPowerSet(frontLeftWheel, -speed, id);
		motorPowerSet(backLeftWheel, speed, id);
	} else if (dir == away) {
		speed = abs(speed);
		motorPowerSet(frontLeftWheel, speed, id);
		motorPowerSet(backLeftWheel, -speed, id);
	}
}

/*
 * Strafe left and right at a particular speed
 * or move forawrd or backward
 */
void strafe(int speed, Direction dir, AccessID id) {
	speed = abs(speed);
	if (dir == left) {
		setLeftMotorSpeed(speed, towards, id);
		setRightMotorSpeed(speed, away, id);
	} else if (dir == right) {
		setLeftMotorSpeed(speed, away, id);
		setRightMotorSpeed(speed, towards, id);
	} else if (dir == forward) {
		setLeftMotorSpeed(speed, same, id);
		setRightMotorSpeed(speed, same, id);
	} else if (dir == backward) {
		setLeftMotorSpeed(-speed, same, id);
		setRightMotorSpeed(-speed, same, id);
	}
}

/*
 * Drive forward or backward or turn left or turn right at a particular speed
 */

void drive(int speed, Direction dir, AccessID id) {
	speed = abs(speed);
	if (dir == left) {
		setLeftMotorSpeed(-speed, same, id);
		setRightMotorSpeed(speed, same, id);
	} else if (dir == right) {
		setLeftMotorSpeed(speed, same, id);
		setRightMotorSpeed(-speed, same, id);
	} else if (dir == forward) {
		setLeftMotorSpeed(speed, same, id);
		setRightMotorSpeed(speed, same, id);
	} else if (dir == backward) {
		setLeftMotorSpeed(-speed, same, id);
		setRightMotorSpeed(-speed, same, id);
	}
}

void handleDriveInput() {
	int y = joystickRead(forward_backward_drive);
	int x = joystickRead(left_right_drive);

	if (abs(y) > abs(x)) {
		setLeftMotorSpeed(y, same, MOTOR_RELEASED_STATE);
		setRightMotorSpeed(y, same, MOTOR_RELEASED_STATE);
	} else if (abs(x) >= abs(y)) {
		setLeftMotorSpeed(x, same, MOTOR_RELEASED_STATE);
		setRightMotorSpeed(-x, same, MOTOR_RELEASED_STATE);
	}
}

void handleStrafingInput() {
	if (abs(
			joystickRead(forward_backward_strafe)
					> abs(joystickRead(left_right_strafe)))) {
		if (joystickRead(forward_backward_strafe) > 0) {
			strafe(joystickRead(forward_backward_strafe), forward, MOTOR_RELEASED_STATE);
		} else {
			strafe(joystickRead(forward_backward_strafe), backward, MOTOR_RELEASED_STATE);
		}
	} else {
		if (joystickRead(left_right_strafe) > 0) {
			strafe(joystickRead(left_right_strafe), right, MOTOR_RELEASED_STATE);
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

void driveForwardBackward(int speed, AccessID id) {
	if (speed >= 0) {
		drive(speed, forward, id);
	} else {
		drive(speed, backward, id);
	}
}

void turnLeftRight(int speed, AccessID id) {
	if (speed >= 0) {
		drive(speed, right, id);
	} else {
		drive(speed, left, id);
	}
}

void strafeLeftRight(int speed, AccessID id) {
	if (speed >= 0) {
		strafe(speed, right, id);
	} else {
		strafe(speed, left, id);
	}
}
