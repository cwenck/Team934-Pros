/*
 * Terminator_API.h
 *
 *  Created on: Nov 12, 2014
 *      Author: guywenck
 */

#ifndef TERMINATOR_API_H_
#define TERMINATOR_API_H_

//Pin Layout
//Pin 0 is the Speaker port.
//Pins 1-12 are the standard Digital I/O.
//Pins 13-20 are the Analog I/O.
//Pins 21+22 are UART1, 23+24 are UART2, and 25+26 are the I2C port.

#include <Math.h>
#include <time.h>
#include <stdlib.h>

#include "stdio_print_header.h"

#include "typedefs.h"

#include "motor_control_priorities.h"
#include "motor.h"
#include "sensors.h"
#include "joystick.h"
#include "lcd.h"
#include "pid.h"
#include "util.h"
#include "speaker.h"
#include "variables.h"
#include "robot_control.h"
#include "auton.h"

#endif /* TERMINATOR_API_H_ */
