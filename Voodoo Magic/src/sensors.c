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
		break;
	case OUTPUT_OD:
		break;
	default:
		break;
	}
	return (int) PORT_INCORRECT_PIN_MODE;
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
		printf(
				"Can't write to port %d because it is not configured as an output.\n\r",
				port);
		break;
	}
}

// Init limit switch / bumpers in initializeIO()
PushButton pushButtonInit(SensorPort port, bool inverted) {
	PushButton push_button;
	push_button.port = port;
	push_button.inverted = inverted;
	portSetPinMode(port, INPUT);
	return push_button;
}

// digitalRead() returns LOW if Pressed or HIGH if released
// the function returns true if the bumper/limit switch is pressed
bool pushButtonPressed(PushButton push_button) {
	if (portRead(push_button.port) == LOW) {
		if (!push_button.inverted) {
			return true;
		} else {
			return false;
		}
	}
	if (!push_button.inverted) {
		return false;
	} else {
		return true;
	}
}

AnalogSensor analogSensorInit(SensorPort port) {
	AnalogSensor sensor;
	sensor.port = port;
	portSetPinMode(port, INPUT_ANALOG);
	return sensor;
}

int analogSensorGet(AnalogSensor sensor) {
	return portRead(sensor.port);
}

//cannnot use the analog port or port 10 for quad encoders
QuadEncoder quadEncoderInit(SensorPort topPort, SensorPort bottomPort,
		bool inverted) {
	QuadEncoder quad;
	//cannnot use the analog port or port 10 for quad encoders
	if (portIsAnalog(topPort) || portIsAnalog(bottomPort) || topPort == 10
			|| bottomPort == 10) {
		QuadEncoder *empty = NULL;
		print(
				"Cannnot use any analog port or digital port 10 for QuadEncoders.");
		return *empty;
	}
	portSetPinMode(topPort, INPUT);
	portSetPinMode(bottomPort, INPUT);
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
	float countsPerRotation = 360.f;
	return (int) (rotations * countsPerRotation);
}

//wheel diameter is in inches
int inchesToQuadEncoderCounts(float inches, int wheelDiameter) {
	float countsPerRotation = 360.f;
	float distPerRotation = wheelDiameter * M_PI;
	int counts = (inches / distPerRotation) * countsPerRotation;
	return counts;
}

int feetToQuadEncoderCounts(float feet, int wheelDiameter) {
	float countsPerRotation = 360.f;
	float inches = feet * 12.f;
	float distPerRotation = wheelDiameter * M_PI;
	int counts = (inches / distPerRotation) * countsPerRotation;
	return counts;
}

void integratedEncoderPrimaryInitialization() {
	connectedIntegratedMotorEncoders = imeInitializeAll();
}

void integratedEncoderResetAll() {
	for (int i = 0; i < connectedIntegratedMotorEncoders; i++) {
		imeReset(i);
	}
}

IntegratedEncoder integratedEncoderInit(IMEAddr port, MotorType type,
		bool inverted) {
	IntegratedEncoder ime;
	ime.imeAddress = port;
	ime.motorType = type;
	ime.inverted = inverted;
	return ime;
}
int integratedEncoderGet(IntegratedEncoder encoder) {
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
int revolutionsToIntegratedEncoderCounts(MotorType type, float rotations) {
	float countsPerRotation = 0;
	if (type == high_torque) {
		countsPerRotation = 627.2f;
	} else if (type == high_speed) {
		countsPerRotation = 392.f;
	}
	return (int) (rotations * countsPerRotation);
}

//wheel diameter is in inches
int inchesToIntegratedEncoderCounts(MotorType type, float inches,
		int wheelDiameter) {
	float countsPerRotation = 0;
	if (type == high_torque) {
		countsPerRotation = 627.2f;
	} else if (type == high_speed) {
		countsPerRotation = 392.f;
	}
	float distPerRotation = wheelDiameter * M_PI;
	int counts = (inches / distPerRotation) * countsPerRotation;
	return counts;
}

int feetToIntegratedEncoderCounts(MotorType type, float feet, int wheelDiameter) {
	float countsPerRotation = 0;
	if (type == high_torque) {
		countsPerRotation = 627.2f;
	} else if (type == high_speed) {
		countsPerRotation = 392.f;
	}
	float inches = feet * 12.f;
	float distPerRotation = wheelDiameter * M_PI;
	int counts = (inches / distPerRotation) * countsPerRotation;
	return counts;
}

//sensorConfig is used to set the multiplier for the gyro sensor
//if that is set as the sensor type. otherwise it does nothing.
//Call imeInitializeAll() before calling this function
Sensor sensorInit(SensorType type, SensorPort port_1, SensorPort port_2,
		bool inverted) {
	Sensor sensor;
	Sensor *empty = NULL;
	sensor.type = type;
	if (sensor.port_1 >= Analog_1 && sensor.port_1 <= Analog_8
			&& (type != Sensor_Bumper && type != Sensor_LimitSwitch)) {
		sensor.isAnalog = true;
	} else {
		sensor.isAnalog = false;
	}
	sensor.port_1 = port_1;
	sensor.port_2 = port_2;
	sensor.inverted = inverted;
	if (sensor.isAnalog) {
		sensor.inverted = false;
	}

	switch (sensor.type) {
	case Sensor_QuadEncoder:
		sensor.sensorData.quadEncoder = quadEncoderInit(sensor.port_1,
				sensor.port_2, inverted);
		break;
	case Sensor_Sonar:
		sensor.sensorData.sonar = ultrasonicInit(sensor.port_1, sensor.port_2);
		break;
	case Sensor_Line:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1);
		break;
	case Sensor_Light:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1);
		break;
	case Sensor_Bumper:
		sensor.sensorData.pushButton = pushButtonInit(sensor.port_1, inverted);
		break;
	case Sensor_LimitSwitch:
		sensor.sensorData.pushButton = pushButtonInit(sensor.port_1, inverted);
		break;
	case Sensor_Potentiometer:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1);
		break;
	case Sensor_Gyroscope:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1);
		break;
	case Sensor_Accelerometer:
		sensor.sensorData.analog = analogSensorInit(sensor.port_1);
		break;
	default:
		print("Invalid Sensor Type\n\r");
		return *empty;
	}
	return sensor;
}

Sensor sensorInitIntegratedEncoder(IMEAddr addr, MotorType type, bool inverted) {
	Sensor sensor;
	sensor.type = Sensor_IntegratedEncoder;
	sensor.sensorData.ime = integratedEncoderInit(addr, type, inverted);
	sensor.inverted = inverted;
	return sensor;
}

//if it is a limit switch or push button a 1 is returned if it is pressed
int sensorGet(Sensor sensor) {
	int value = 0;

	switch (sensor.type) {
	case Sensor_IntegratedEncoder:
		value = integratedEncoderGet(sensor.sensorData.ime);
		break;
	case Sensor_QuadEncoder:
		value = quadEncoderGet(sensor.sensorData.quadEncoder);
		break;
	case Sensor_Sonar:
		value = ultrasonicGet(sensor.sensorData.sonar);
		break;
	case Sensor_Line:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Sensor_Light:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Sensor_Bumper:
		value = pushButtonPressed(sensor.sensorData.pushButton);
		break;
	case Sensor_LimitSwitch:
		value = pushButtonPressed(sensor.sensorData.pushButton);
		break;
	case Sensor_Potentiometer:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Sensor_Gyroscope:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	case Sensor_Accelerometer:
		value = analogSensorGet(sensor.sensorData.analog);
		break;
	}
	return value;
}

void sensorReset(Sensor sensor) {
	switch (sensor.type) {
	case Sensor_QuadEncoder:
		quadEncoderReset(sensor.sensorData.quadEncoder);
		break;
	case Sensor_IntegratedEncoder:
		integratedEncoderReset(sensor.sensorData.ime);
		break;
	default:
		break;
	}
}
