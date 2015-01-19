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

void setLiftPower(int speed) {
//	speed = -    speed;
	motorPowerSet(topLeftLift, speed);
	motorPowerSet(middleLeftLift, speed);
	motorPowerSet(bottomLeftLift, speed);
	motorPowerSet(topRightLift, speed);
	motorPowerSet(middleRightLift, speed);
	motorPowerSet(bottomRightLift, speed);
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
		motorPowerSet(frontRightWheel, speed);
		motorPowerSet(backRightWheel, speed);
	} else if (dir == towards) {
		speed = abs(speed);
		motorPowerSet(frontRightWheel, -speed);
		motorPowerSet(backRightWheel, speed);
	} else if (dir == away) {
		speed = abs(speed);
		motorPowerSet(frontRightWheel, speed);
		motorPowerSet(backRightWheel, -speed);
	}
}

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setLeftMotorSpeed(int speed, WheelDirection dir) {
	if (dir == same) {
		motorPowerSet(frontLeftWheel, speed);
		motorPowerSet(backLeftWheel, speed);
	} else if (dir == towards) {
		speed = abs(speed);
		motorPowerSet(frontLeftWheel, -speed);
		motorPowerSet(backLeftWheel, speed);
	} else if (dir == away) {
		speed = abs(speed);
		motorPowerSet(frontLeftWheel, speed);
		motorPowerSet(backLeftWheel, -speed);
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
		handleStrafingInput();
	} else {
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
		ticks = ticksTillIntakeUncompressed + (int) (inches * liftEncoderTicksPerInch);
	} else {
		ticks = ticksTillIntakeUncompressed + (int) (inches * liftEncoderTicksPerInch);
	}

	if(ticks > maxLiftEncoderTicks){
		ticks = maxLiftEncoderTicks;
	}

	return ticks;
}
int feetToLiftEncoderTicks(float feet) {
	int value = sensorGet(liftEncoder);
	int ticks = 0;
	
	if (value > ticksTillIntakeUncompressed) {
		ticks =  ticksTillIntakeUncompressed + (int) (feet * liftEncoderTicksPerInch * 12);
	} else {
		ticks =  ticksTillIntakeUncompressed + (int) (feet * liftEncoderTicksPerInch * 12);
	}

	if(ticks > maxLiftEncoderTicks){
		ticks = maxLiftEncoderTicks;
	}

	return ticks;
}

///////////////////////////////////
//PID Controllable Drive Funtions//
///////////////////////////////////

void driveForwardBackward(int speed) {
	if (speed >= 0) {
		drive(speed, forward);
	} else {
		drive(speed, backward);
	}
}

void turnLeftRight(int speed) {
	if (speed >= 0) {
		drive(speed, right);
	} else {
		drive(speed, left);
	}
}

void strafeLeftRight(int speed) {
	if (speed >= 0) {
		strafe(speed, right);
	} else {
		strafe(speed, left);
	}
}
