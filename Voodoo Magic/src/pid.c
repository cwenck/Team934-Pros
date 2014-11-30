#include "main.h"

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

void pidControllerSetTolerance(PIDController *controller, float tolerance){
	controller->error_tolerance = tolerance;
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
	AccessID id = motorArrayTakeControl(pid.numMotors, pid.motors);
	pid.target_reached = false;
	while (!pid.target_reached) {
		pid.last_error = pid.error;
		pid.sensor_reading = sensorGet(pid.sensor);
		pid.error = pid.sensor_target - pid.sensor_reading;

		lcdDisplayFormattedCenteredString(uart1, 1, "Err: %.2f\n\r", pid.error);

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
		pid.setMotorSpeedFunction(pid.motor_speed, id);
		delay(20);
	}
	pid.setMotorSpeedFunction(0);
}
