/*
 * motor_control_priorities.h
 *
 *  Created on: Nov 30, 2014
 *      Author: guywenck
 */

#ifndef MOTOR_CONTROL_PRIORITIES_H_
#define MOTOR_CONTROL_PRIORITIES_H_

#include "Main.h"

#define MOTOR_PRIORETY_CONTROL_RELEASED 255
#define MOTOR_PRIORETY_CONTROL_LOWEST 254
#define MOTOR_PRIORETY_CONTROL_HIGHEST 0


//every assigned access id must be unique
//priority levels can be duplicated
//controllers with the same priority level can not take control from each other

struct _MotorAccessController{
	AccessID id;
	PriorityLevel priority;
};

extern MotorAccessController MOTOR_RELEASED_STATE;
extern MotorAccessController MOTOR_JOYSTICK_CONTROLLED;
extern MotorAccessController MOTOR_PID_CONTROLLED;
extern MotorAccessController MOTOR_AUTONOMOUS_CONTROLLED;

void motorAccessControllersInit();
void motorAccessControllerInit(MotorAccessController *controller, AccessID id, PriorityLevel priorityLevel);

bool motorCanBeTakenByMotorAccessController(Motor motor,
		MotorAccessController controller);
MotorAccessController motorGetAccessControllerFromID(AccessID id);
PriorityLevel motorGetPriorityLevelFromAccessControllerById(AccessID id);
PriorityLevel motorGetPriorityLevelFromAccessController(MotorAccessController controller);
#endif /* MOTOR_CONTROL_PRIORITIES_H_ */
