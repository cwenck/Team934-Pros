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
//	pidControllerSetTarget(&liftPID, 7600);
//	pidStart(&liftPID);
	setLiftPower(127);
	delay(3200);
	setLiftPower(0);
	strafe(127, left);
	delay(1800);
	strafe(0, left);
}

void redCubeOnPost() {
	setLiftPower(127);
	delay(3200);
	setLiftPower(0);
	strafe(127, right);
	delay(550);
	strafe(0, right);
	drive(127, forward);
	delay(100);
	drive(0, forward);
	setLiftPower(-127);
	delay(400);
	setLiftPower(0);
}

