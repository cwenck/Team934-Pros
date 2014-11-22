#include "main.h"

///////////
//Sensors//
///////////

CortexPort ports[21];

void cortexPortsInit() {
	speakerInit();
	CortexPort *port = ports;
	for (int i = 0; i < 21; i++) {
		port->port = i;
		if ((i >= 13) && (i <= 20)) {
			port->analogCapabilites = true;
			port->mode = INPUT_ANALOG;
		} else {
			port->analogCapabilites = false;
			port->mode = INPUT;
		}
		port++;
	}
}

CortexPort* cortexPortForSensorPort(SensorPort port) {
	return &ports[port];
}

bool portIsAnalog(SensorPort port) {
	CortexPort *cortexPort = cortexPortForSensorPort(port);
	return cortexPort->analogCapabilites;
}

void portSetPinMode(SensorPort port, unsigned char mode) {
	CortexPort *cortexPort = cortexPortForSensorPort(port);
	if ((mode == INPUT_ANALOG) && cortexPort->analogCapabilites) {
		printf("Port: %d\n\r", cortexPort->port);
		pinMode(cortexPort->port, INPUT_ANALOG);
		cortexPort->mode = INPUT_ANALOG;
	} else if (mode != INPUT_ANALOG) {
		pinMode(cortexPort->port, mode);
		cortexPort->mode = mode;
	}
}

int portRead(SensorPort port) {
	CortexPort *cortexPort = cortexPortForSensorPort(port);
	switch (cortexPort->mode) {
	case INPUT:
		if (cortexPort->analogCapabilites) {
			return (analogRead(cortexPort->port - 12) < 1000) ? 0 : 1;
		} else {
			return digitalRead(cortexPort->port);
		}
		break;
	case INPUT_ANALOG:
		return analogRead(cortexPort->port - 12);
		break;
	case INPUT_FLOATING:
		if (cortexPort->analogCapabilites) {
			return (analogRead(cortexPort->port - 12) < 1000) ? 0 : 1;
		} else {
			return digitalRead(cortexPort->port);
		}
		break;
	case OUTPUT:
		return NULL;
		break;
	case OUTPUT_OD:
		return NULL;
		break;
	default:
		return NULL;
	}
}

void portWrite(SensorPort port, bool value) {
	CortexPort *cortexPort = cortexPortForSensorPort(port);
	switch (cortexPort->mode) {
	case OUTPUT:
		digitalWrite(cortexPort->port, value);
		break;
	case OUTPUT_OD:
		digitalWrite(cortexPort->port, value);
		break;
	default:
		//Do Nothing
		break;
	}
}

// Init limit switch / bumpers in initializeIO()
PushButton pushButtonInit(SensorPort port) {
	PushButton limitSwitch;
	limitSwitch.port = port;
	portSetPinMode(port, INPUT);
	return limitSwitch;
}

// digitalRead() returns LOW if Pressed or HIGH if released
// the function returns true if the bumper/limit switch is pressed
bool bumpPressed(PushButton limitSwitch) {
	if (portRead(limitSwitch.port) == LOW) {
		return true;
	}
	return false;
}

AnalogSensor analogSensorInit(SensorPort port, bool inverted) {
	AnalogSensor sensor;
	sensor.port = port;
	sensor.inverted = inverted;
//	if (portIsAnalog(port)) {
	portSetPinMode(port, INPUT_ANALOG);
	return sensor;
//	} else {
//		return NULL;
//	}
}

int analogSensorGet(AnalogSensor sensor) {
	int value = portRead(sensor.port);
	;
	if (sensor.inverted) {
		value = -value;
	}
	return value;
}

//cannnot use the analog port or port 10 for quad encoders
QuadEncoder quadEncoderInit(SensorPort topPort, SensorPort bottomPort,
		bool inverted) {
	QuadEncoder quad;
	//cannnot use the analog port or port 10 for quad encoders
//	if(portIsAnalog(topPort) || portIsAnalog(bottomPort) || topPort == 10 || bottomPort == 10){
//		return NULL;
//	}
	quad.top = topPort;
	quad.bottom = bottomPort;
	quad.encoder_data = encoderInit(topPort, bottomPort, false);
	quad.inverted = inverted;
	return quad;
}

int quadEncoderGet(QuadEncoder encoder) {
	int value = encoderGet(encoder.encoder_data);
	if (encoder.inverted) {
		value = -value;
	}
	return value;
}

void quadEncoderReset(QuadEncoder encoder) {
	encoderReset(encoder.encoder_data);
}

//360 counts per revolution
int revolutionsToQuadEncoderCounts(float rotations) {
	const float countsPerRotation = 360.f;
	return (int) (rotations * countsPerRotation);
}

//wheel diameter is in inches
int inchesToQuadEncoderCounts(float inches, int wheelDiameter) {
	const float countsPerRotation = 360.f;
	float distPerRotation = wheelDiameter * M_PI;
	int counts = (inches / distPerRotation) * countsPerRotation;
	return counts;
}

int feetToQuadEncoderCounts(float feet, int wheelDiameter) {
	const int countsPerRotation = 360;
	float inches = feet * 12.f;
	float distPerRotation = wheelDiameter * M_PI;
	int counts = (inches / distPerRotation) * countsPerRotation;
	return counts;
}

IntegratedEncoder integratedEncoderInit(IMEAddr port, bool inverted) {
	IntegratedEncoder ime;
	ime.imeAddress = port;
	ime.inverted = inverted;
	return ime;
}
int integratedencoderGet(IntegratedEncoder encoder) {
	int value;
	imeGet(encoder.imeAddress, &value);
	if (encoder.inverted) {
		value = -value;
	}
	return value;
}

void integratedEncoderReset(IntegratedEncoder encoder) {
	imeReset(encoder.imeAddress);
}

//360 counts per revolution
int revolutionsToIntegratedEncoderCounts(float rotations) {
	const int countsPerRotation = 360.f;
	return (int) (rotations * countsPerRotation);
}

//wheel diameter is in inches
int inchesToIntegratedEncoderCounts(float inches, int wheelDiameter) {
	const int countsPerRotation = 360;
	float distPerRotation = wheelDiameter * M_PI;
	int counts = (inches / distPerRotation) * countsPerRotation;
	return counts;
}

int feetToIntegratedEncoderCounts(float feet, int wheelDiameter) {
	const int countsPerRotation = 360;
	float inches = feet * 12.f;
	float distPerRotation = wheelDiameter * M_PI;
	int counts = (inches / distPerRotation) * countsPerRotation;
	return counts;
}

//sensorConfig is used to set the multiplier for the gyro sensor
//if that is set as the sensor type. otherwise it does nothing.
//Call imeInitializeAll() before calling this function
Sensor sensorDigitalInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted, int sensorConfig) {
	Sensor sensor;
	sensor.type = type;
	sensor.port_1 = port_1;
	sensor.port_2 = port_2;
	sensor.inverted = inverted;

//	switch (sensor.type) {
//	case IntegratedMotorEncoder:
////		sensor.sensorData.ime = integratedEncoderInit(sensor.port_1.imePort,
////				inverted);
//		break;
//	case QuadratureEncoder:
//		sensor.sensorData.quadEncoder = quadEncoderInit(
//				sensor.port_1.digitalPort, sensor.port_1.digitalPort, inverted);
//		break;
//	case Sonar:
//		sensor.sensorData.sonar = ultrasonicInit(sensor.port_1.digitalPort,
//				sensor.port_2;
//		break;
//	case Line:
//		sensor.sensorData.analog = analogSensorInit(sensor.port_1.analogPort,
//				inverted);
//		break;
//	case Light:
//		sensor.sensorData.analog = analogSensorInit(sensor.port_1.analogPort,
//				inverted);
//		break;
//	case Bumper:
//		sensor.sensorData.pushButton = pushButtonInit(
//				sensor.port_1.digitalPort);
//		break;
//	case Limit_Switch:
//		sensor.sensorData.pushButton = pushButtonInit(
//				sensor.port_1.digitalPort);
//		break;
//	case Potentiometer:
//		sensor.sensorData.analog = analogSensorInit(sensor.port_1.analogPort,
//				inverted);
//		break;
//	case Gyroscope:
//		sensor.sensorData.gyro = gyroInit(sensor.port_1.analogPort,
//				sensorConfig);
//		break;
//	case Accelerometer:
//		sensor.sensorData.analog = analogSensorInit(sensor.port_1.analogPort,
//				inverted);
//		break;
//	}
	return sensor;
}

Sensor sensorInitFromIntegratedEncoder(IntegratedEncoder encoder) {
	Sensor sensor;
	sensor.type = IntegratedMotorEncoder;
	sensor.sensorData.ime = encoder;
	sensor.inverted = false;
	return sensor;
}

Sensor sensorInitFromQuadEncoder(QuadEncoder *encoder) {
	Sensor sensor;
	sensor.type = IntegratedMotorEncoder;
	sensor.sensorData.quadEncoder = *encoder;
	sensor.inverted = false;
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
