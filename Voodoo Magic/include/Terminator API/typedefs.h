/*
 * typedefs.h
 *
 *  Created on: Nov 27, 2014
 *      Author: cwenck
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include "Main.h"

//Ports
typedef enum _IMEAddr IMEAddr;
typedef enum _MotorPort MotorPort;
typedef enum _SensorPort SensorPort;
typedef struct _CortexPort CortexPort;

//Sensors
typedef enum _SensorType SensorType;
typedef struct _QuadEncoder QuadEncoder;
typedef struct _PushButton PushButton;
typedef struct _AnalogSensor AnalogSensor;
typedef struct _Sensor Sensor;
typedef struct _IntegratedEncoder IntegratedEncoder;

//Motors
typedef struct _Motor Motor;
typedef enum _MotorType MotorType;
typedef struct _MotorAccessController MotorAccessController;

//Joystick
typedef enum _JoyInput JoyInput;
typedef struct _JoyInputInfo JoyInputInfo;

//PID
typedef struct _PIDController PIDController;

//Robot Control
typedef enum _WheelDirection WheelDirection;
typedef enum _Direction Direction;


//General Types
typedef unsigned short AccessID;
typedef unsigned char PriorityLevel;

#endif /* TYPEDEFS_H_ */
