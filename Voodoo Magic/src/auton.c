#include "main.h"

void strafeLeft() {
	motorArrayTakeControl(NUM_DRIVE_MOTORS, driveMotors,
			MOTOR_AUTONOMOUS_CONTROLLED);
	motorArrayTakeControl(NUM_LIFT_MOTORS, liftMotors,
			MOTOR_AUTONOMOUS_CONTROLLED);
	{
		setLiftPower(127, MOTOR_AUTONOMOUS_CONTROLLED);
		delay(500);
		setLiftPower(0, MOTOR_AUTONOMOUS_CONTROLLED);
		strafe(127, left, MOTOR_AUTONOMOUS_CONTROLLED);
		delay(750);
		strafe(0, left, MOTOR_AUTONOMOUS_CONTROLLED);
	}
	motorArrayReleaseControl(NUM_LIFT_MOTORS, liftMotors);
	motorArrayReleaseControl(NUM_DRIVE_MOTORS, driveMotors);
}

void strafeRight() {
	motorArrayTakeControl(NUM_DRIVE_MOTORS, driveMotors,
			MOTOR_AUTONOMOUS_CONTROLLED);
	motorArrayTakeControl(NUM_LIFT_MOTORS, liftMotors,
			MOTOR_AUTONOMOUS_CONTROLLED);
	{
		setLiftPower(127, MOTOR_AUTONOMOUS_CONTROLLED);
		delay(500);
		setLiftPower(0, MOTOR_AUTONOMOUS_CONTROLLED);
		strafe(127, right, MOTOR_AUTONOMOUS_CONTROLLED);
		delay(750);
		strafe(0, right, MOTOR_AUTONOMOUS_CONTROLLED);
	}
	motorArrayReleaseControl(NUM_LIFT_MOTORS, liftMotors);
	motorArrayReleaseControl(NUM_DRIVE_MOTORS, driveMotors);
}

void driveBack() {
	motorArrayTakeControl(NUM_DRIVE_MOTORS, driveMotors,
			MOTOR_AUTONOMOUS_CONTROLLED);
	motorArrayTakeControl(NUM_LIFT_MOTORS, liftMotors,
			MOTOR_AUTONOMOUS_CONTROLLED);
	{
		setLiftPower(127, MOTOR_AUTONOMOUS_CONTROLLED);
		delay(500);
		setLiftPower(0, MOTOR_AUTONOMOUS_CONTROLLED);
		drive(127, backward, MOTOR_AUTONOMOUS_CONTROLLED);
		delay(750);
		drive(0, backward, MOTOR_AUTONOMOUS_CONTROLLED);
	}
	motorArrayReleaseControl(NUM_LIFT_MOTORS, liftMotors);
	motorArrayReleaseControl(NUM_DRIVE_MOTORS, driveMotors);
}

void blueCubeOnPost() {
//	pidControllerSetTarget(&liftPID, 7600);
//	pidStart(&liftPID);
//	setLiftPower(127);
//	delay(3200);
//	setLiftPower(0);
//	strafe(127, left);
//	delay(1800);
//	strafe(0, left);
}

void redCubeOnPost() {
//	setLiftPower(127);
//	delay(3200);
//	setLiftPower(0);
//	strafe(127, right);
//	delay(550);
//	strafe(0, right);
//	drive(127, forward);
//	delay(100);
//	drive(0, forward);
//	setLiftPower(-127);
//	delay(400);
//	setLiftPower(0);
}

