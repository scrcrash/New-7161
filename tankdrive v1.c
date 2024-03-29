#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     IRSeeker,       sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorTL,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorBL,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorTR,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorNothing,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorBrush,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoGrip1,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servoGrip2,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

//task IR ()
//{
//	while(true)
//	{
//		if (SensorValue[IRSeeker] == 5)
//		{
//			motor[motorTL] = 0;
//			motor[motorTR] = 0;
//			motor[motorBL] = 0;
//			motor[motorBR] = 0;
//		}
//	}
//}

task baseGrip()
{
	while(true)
	{
		//reset servos
		//servo[servoHinge1] = 90;
		//servo[servoHinge2] = 90;

		servo[servoGrip1] = 0;
		servo[servoGrip2] = 180;

		//move grips to down position
		if(joy1Btn(3) == 1)
		{
			//servo[servoHinge1] = 120;
			//servo[servoHinge2] = 60;
		}

		//move grips to upright position
		if(joy1Btn(5) == 1)
		{
			//servo[servoHinge1] = 100;
			//servo[servoHinge2] = 80;
		}

		//Servos that actually grip it tighten (so it grips)
		if(joy1Btn(4) == 1)
		{
			servo[servoGrip1] = 100; //change this later
			servo[servoGrip2] = 100;
		}

		//Servos that actually grip it loosen (so it lets go)
		if(joy1Btn(3) == 1)
		{
			servo[servoGrip1] = 90; //change this later
			servo[servoGrip2] = 90;
		}
		wait1Msec(5);

	}
}

task brush()	//This is what spins so the balls come in
{
	while(true)
	{
		if(abs(joystick.joy2_y1) > 10)
		{
			motor[motorBrush] = joystick.joy2_y1;
		}
		wait1Msec(5);
	}
}

task conveyor()	//method for conveyor belt manipulator
{
	while(true)
	{
		 //conveyor belt runs forward when button pressed
		if (joy2Btn(5) == 1)
		{
			//which motor is the motor for the conveyor belt?
			motor[motorC] = 50; //what speed do we want?
		}
		if (joy2Btn(4) == 1)
		{
			motor[motorC] = -50;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();

  waitForStart();   // wait for start of tele-op phase

  startTask(baseGrip);
  startTask(brush);
  startTask(conveyor);

  while (true)
  {
  	//tank drive
		if(abs(joystick.joy1_y1) > 25 || abs(joystick.joy1_y2) > 25)
		{
			motor[motorTL] = joystick.joy1_y1 ;
			motor[motorBL] = joystick.joy1_y1 ;

			motor[motorTR] = joystick.joy1_y2 ;
			motor[motorBR] = joystick.joy1_y2 ;
		}

		else
		{
			motor[motorTL] = 0;
	    motor[motorTR] = 0;
	    motor[motorBL] = 0;
	    motor[motorBR] = 0;
	   }
	}

//encoder coding
	//nMotorEncoder[motorB] = 0;
	//nMotorEncoder[motorC] = 0;

	//nMotorEncoderTarget[motorB] = 1800;
	//nMotorEncoderTarget[motorC] = 1800;

	//motor[motorB] = 50;
	//motor[motorC] = 50;

 // wait1Msec(8000);

    // Insert code to have servos and motors respond to joystick and button values.

    // Look in the ROBOTC samples folder for programs that may be similar to what you want to perform.
    // You may be able to find "snippets" of code that are similar to the functions that you want to
    // perform.

}
