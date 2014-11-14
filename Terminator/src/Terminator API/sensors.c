
#include "main.h"

///////////
//Sensors//
///////////

// Init limit switch / bumpers in initializeIO()
PushButton pushButtonInit(DigitalPort port) {
	PushButton limitSwitch;
	limitSwitch.port = port;
	pinMode(limitSwitch.port, INPUT);
	return limitSwitch;
}

// digitalRead() returns LOW if Pressed or HIGH if released
// the function returns true if the bumper/limit switch is pressed
bool bumpPressed(PushButton limitSwitch) {
	if (digitalRead(limitSwitch.port) == LOW) {
		return true;
	}
	return false;
}

AnalogSensor analogSensorInit(AnalogPort port, bool inverted) {
	AnalogSensor sensor;
	sensor.port = port;
	sensor.inverted = inverted;
	return sensor;
}

int analogSensorGet(AnalogSensor sensor) {
	if (!sensor.inverted) {
		return analogRead(sensor.port);
	} else {
		return -analogRead(sensor.port);
	}
}

QuadEncoder quadEncoderInit(DigitalPort topPort, DigitalPort bottomPort, bool inverted){
	QuadEncoder quad;
	quad.encoder_data = encoderInit(topPort, bottomPort, false);
	quad.inverted = inverted;
	return quad;
}

int quadEncoderGet(QuadEncoder encoder){
	int value = encoderGet(encoder.encoder_data);
	if(encoder.inverted){
		value = - value;
	}
	return value;
}

void quadEncoderReset(QuadEncoder encoder){
	encoderReset(encoder.encoder_data);
}

IntegratedEncoder integratedEncoderInit(IMEPort port, bool inverted){
	IntegratedEncoder ime;
	ime.imeAddress = port;
	ime.inverted = inverted;
	return ime;
}
int integratedencoderGet(IntegratedEncoder encoder){
	int value;
	imeGet(encoder.imeAddress, &value);
	if(encoder.inverted){
		value = - value;
	}
	return value;
}

void integratedEncoderReset(IntegratedEncoder encoder){
	imeReset(encoder.imeAddress);
}

//sensorConfig is used to set the multiplier for the gyro sensor
//if that is set as the sensor type. otherwise it does nothing.
//Call imeInitializeAll() before calling this function
Sensor sensorInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted, int sensorConfig) {
	Sensor sensor;
	sensor.type = type;
	sensor.port_1 = port_1;
	sensor.port_2 = port_2;
	sensor.inverted = inverted;


	switch (sensor.type) {
	case IntegratedMotorEncoder:
		sensor.sensorData.ime = integratedEncoderInit(sensor.port_1.imePort, inverted);
		break;
	case QuadratureEncoder:
		sensor.sensorData.quadEncoder = quadEncoderInit(sensor.port_1.digitalPort, sensor.port_1.digitalPort, inverted);
		break;
	case Sonar:
		sensor.sensorData.sonar = ultrasonicInit(sensor.port_1.digitalPort, sensor.port_2.digitalPort);
		break;
	case Line:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1.analogPort, inverted);
		break;
	case Light:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1.analogPort, inverted);
		break;
	case Bumper:
		sensor.sensorData.pushButton = pushButtonInit(sensor.port_1.digitalPort);
		break;
	case Limit_Switch:
		sensor.sensorData.pushButton = pushButtonInit(sensor.port_1.digitalPort);
		break;
	case Potentiometer:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1.analogPort, inverted);
		break;
	case Gyroscope:
		sensor.sensorData.gyro = gyroInit(sensor.port_1.analogPort, sensorConfig);
		break;
	case Accelerometer:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1.analogPort, inverted);
		break;
	}
	return sensor;
}

//if it is a limit switch or push button a 1 is returned if it is pressed
int sensorGet(Sensor sensor) {
	int value = NULL;

	switch (sensor.type) {
	case IntegratedMotorEncoder:
		value = integratedencoderGet(sensor.sensorData.ime);
		break;
	case QuadratureEncoder:
		value = quadEncoderGet(sensor.sensorData.quadEncoder);
		break;
	case Sonar:
		value = ultrasonicGet(sensor.sensorData.sonar);
		break;
	case Line:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Light:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Bumper:
		value = bumpPressed(sensor.sensorData.pushButton);
		break;
	case Limit_Switch:
		value = bumpPressed(sensor.sensorData.pushButton);
		break;
	case Potentiometer:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Gyroscope:
		value = gyroGet(sensor.sensorData.gyro);
		break;
	case Accelerometer:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	}
	return value;
}
