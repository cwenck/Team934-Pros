/*
 * util.h
 *
 *  Created on: Nov 12, 2014
 *      Author: guywenck
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "main.h"

/////////
//Other//
/////////

int capMotorPower(int value);

//returns the main battery power in volts
float getMainBatteryPower();
//print the main batter power in volts
void printMainBatteryPower();

void executeAutonIfJumperInPort(DigitalPort port);

#endif /* UTIL_H_ */
