/*
 * pid.h
 *
 *  Created on: Nov 12, 2014
 *      Author: guywenck
 */


#ifndef PID_H_
#define PID_H_

#include "main.h"

///////
//PID//
///////

struct _PIDController{
	float kp;
	float ki;
	float kd;
	int p_speed;
	int i_speed;
	int d_speed;
	int motor_speed;
	//number of checks passed to
	//see if the target has been reached
	int num_checks_passed;
	bool target_reached;
	bool shouldTerminate;
	float error_tolerance;
	float error;
	float last_error;
	float sensor_target;
	float sensor_reading;
	float integral;
	bool ignoreIntegralBounds;
	//how samll the error needs to be
	// for the integral to be calculated
	float integral_range;
	float integral_min;
	float integral_max;
	float derivative;
	Sensor sensor;
	void (*setMotorSpeedFunction)(int, MotorAccessController);
	int numMotors;
	Motor motors[];
};

PIDController pidControllerInit(float kp, float ki, float kd,
		void (*setMotorSpeedFunction)(int, MotorAccessController), Sensor sensor);
void pidControllerSetTarget(PIDController *controller, float target);
void pidControllerSetTolerance(PIDController *controller, float tolerance);
void pidSetIntegralRange(PIDController *controller, float integralRange);
//set the minimum and maximum absolute values of the inegral component of the motor speed
void pidControllerSetIntegralSpeedBounds(PIDController *controller,
		float integral_min, float integral_max);
void pidStart(PIDController *controller);
void pidTask(void *ignore);

#endif /* PID_H_ */
