#include "main.h"

void strafeLeft() {
	setLiftPower(127);
	delay(500);
	setLiftPower(0);
	strafe(127, left);
	delay(750);
	strafe(0, left);
}

void strafeRight() {
	setLiftPower(127);
	delay(500);
	setLiftPower(0);
	strafe(127, right);
	delay(750);
	strafe(0, right);
}

void driveBack() {
	setLiftPower(127);
	delay(500);
	setLiftPower(0);
	drive(127, backward);
	delay(750);
	drive(0, backward);
}

void blueCubeOnPost() {
	pidControllerSetTarget(&liftPID, inchesToLiftEncoderTicks(24.5));
	pidStartAsFuntion(&liftPID);
	strafe(127, left);
	delay(800);
	strafe(0, left);
	drive(127, forward);
	delay(500);
	drive(0, forward);
	pidControllerSetTarget(&liftPID, inchesToLiftEncoderTicks(19.75));
	pidStartAsFuntion(&liftPID);
	drive(127, backward);
	delay(500);
	drive(0, backward);

}

void redCubeOnPost() {
	pidControllerSetTarget(&liftPID, inchesToLiftEncoderTicks(24.5));
	pidStartAsFuntion(&liftPID);
	strafe(127, right);
	delay(800);
	strafe(0, right);
	drive(127, forward);
	delay(500);
	drive(0, forward);
	pidControllerSetTarget(&liftPID, inchesToLiftEncoderTicks(19.75));
	pidStartAsFuntion(&liftPID);
	drive(127, backward);
	delay(500);
	drive(0, backward);
}

