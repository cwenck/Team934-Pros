#include "main.h"

/////////
//Other//
/////////

int capMotorPower(int value) {
	if (value > 127) {
		return 127;
	} else if (value < -127) {
		return -127;
	} else {
		return value;
	}
}

float getMainBatteryPower() {
	return ((float) powerLevelMain()) / 1000.0f;
}

void printMainBatteyPower() {
	printf("Main Battery: %.2fV", getMainBatteryPower());
}

void executeAutonIfJumperInPort(DigitalPort port){
	pinMode(port, INPUT);
	if(!digitalRead(port)){
		autonomous();
	}
}
