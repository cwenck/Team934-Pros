#include "main.h"

void strafeLeft(){
	setLiftPower(127);
	delay(500);
	setLiftPower(0);
	strafe(127, left);
	delay(750);
	strafe(0, left);
}

void strafeRight(){
	setLiftPower(127);
	delay(500);
	setLiftPower(0);
	strafe(127, right);
	delay(750);
	strafe(0, right);
}

void driveBack(){
	setLiftPower(127);
	delay(500);
	setLiftPower(0);
	drive(127, backward);
	delay(750);
	drive(0, backward);
}

