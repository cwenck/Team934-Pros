/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
	setTeamName("934");

	//set pin mode for jumper autonomus
//	pinMode(Digital_12, INPUT);
//	pinMode(1, INPUT);
	cortexPortsInit();

	for(SensorPort i = Digital_1; i <= Analog_8; i++){
		portSetPinMode(i, INPUT_FLOATING);
	}
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
	lcdSetup(uart1);
	speakerInit();
	songsInit();
//	QuadEncoder quad = quadEncoderInit(Digital_2, Digital_3, true);
//	liftEncoder = sensorInitFromQuadEncoder(&quad);

	//Drive Integrated Encoders
	IntegratedEncoder frontLeftWheelEncoder = integratedEncoderInit(0, false);
//	IntegratedEncoder frontRightWheelEncoder = integratedEncoderInit(1, false);
//	IntegratedEncoder backLeftWheelEncoder = integratedEncoderInit(2, false);
//	IntegratedEncoder backRightWheelEncoder = integratedEncoderInit(3, false);

	//Init Drive Motors
	frontLeftWheel = createMotorWithIME(2, false, &frontLeftWheelEncoder);
	frontRightWheel = createMotor(3, true);
	backLeftWheel = createMotor(4, false);
	backRightWheel = createMotor(5,	 true);
//
//	//Init Lift Motors


	//Init Controller Buttons
//	liftUp = controlButtonInit(5, JOY_UP);
//	liftDown = controlButtonInit(5, JOY_DOWN);
//
//	forward_backward_drive = controlStickInit(3);
//	left_right_drive = controlStickInit(4);
//	forward_backward_strafe = controlStickInit(2);
//	left_right_strafe = controlStickInit(1);

	liftUp = Btn5U;
	liftDown = Btn5D;

	forward_backward_drive = Ch3;
	left_right_drive = Ch4;
	forward_backward_strafe = Ch2;
	left_right_strafe = Ch1;
}
