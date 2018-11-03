#pragma config(Motor,  port2,           frontRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           backRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           frontLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  port5,           backLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port6,           intakeMotor,      tmotorNormal, openLoop)

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// These are the different choices we have
typedef enum {
	kLcdDispStart = 0,

	kLcdAuto_1    = 0,
	kLcdAuto_2,
	kLcdAuto_3,
	kLcdAuto_4,

	kLcdDispNumber
} kLcdDispType;

// globals for tracking choices
short           autoMode = (-1);

// Display LCD choice
void lcdMenuDisplay(kLcdDispType current)
{
	//Switch case that allows the user to choose from 4 different options
	switch(current){
	case kLcdAuto_1:
		//Display first choice
		displayLCDCenteredString(0, "Red Left");
		displayLCDCenteredString(1, "<     Enter    >");
		break;
	case kLcdAuto_2:
		//Display second choice
		displayLCDCenteredString(0, "Red Right");
		displayLCDCenteredString(1, "<     Enter    >");
		break;
	case kLcdAuto_3:
		//Display third choice
		displayLCDCenteredString(0, "Blue Left");
		displayLCDCenteredString(1, "<     Enter    >");
		break;
	case kLcdAuto_4:
		//Display fourth choice
		displayLCDCenteredString(0, "Blue Right");
		displayLCDCenteredString(1, "<     Enter    >");
		break;

	default:
		break;
	}
}

// Pre auton code - allow auton choice until enabled or selection is made
void pre_auton()
{
	int     i;
	int     autoTime = 1000;
	TControllerButtons    Buttons;

	// current choice
	kLcdDispType    mode = kLcdAuto_1;

	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true;

	// Initial display
	lcdMenuDisplay(mode);

	//Loop while disabled
	while( bIfiRobotDisabled )
	{
		// Select display Item
		Buttons = nLCDButtons;

		// if right or left pressed change display
		if( (Buttons == kButtonLeft) || (Buttons == kButtonRight) )
		{
			// check for button press
			if( Buttons == kButtonRight )
			{
				mode++;
				if(mode >= kLcdDispNumber)
					mode = kLcdDispStart;
			}
			if( Buttons == kButtonLeft )
			{
				mode--;
				if(mode < kLcdDispStart)
					mode = (kLcdDispNumber-1);
			}

			// update display
			lcdMenuDisplay(mode);

			// wait for release or auto repeat time
			for( i=0;i<autoTime;i+=10)
			{
				if( nLCDButtons == kButtonNone )
				{
					autoTime = 1000;
					break;
				}
				wait1Msec(10);
			}
			// shorten auto repeat for next time
			if( nLCDButtons != kButtonNone )
				autoTime = 250;
		}

		// Center button selects choice
		if( Buttons == kButtonCenter )
		{
			displayLCDCenteredString(1, "<   Selected   >");
			// set the autononomous mode (replaces choice variable from sdrobotics code)
			autoMode = (short)mode;
			wait1Msec(1000);
			return;
		}

		// don't hog cpu
		wait1Msec(25);
	}
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void robotDriveStraight(int runTime, int power)
{
	motor[frontRight] = power; //Full power is 127
	motor[frontLeft] = power; //Full power is 127
	motor[backRight] = power; //Full power is 127
	motor[backLeft] = power; //Full power is 127
	wait1Msec(runTime);	//Run for three seconds
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;


}

task autonomous()
{
	if(autoMode==1){
	displayLCDCenteredString(0, "flags");
	robotDriveStraight(2000,127);
	robotDriveStraight(2000,-127);
}else if(autoMode==2){
displayLCDCenteredString(0, "caps");
robotDriveStraight(1800,127);
robotDriveStraight(1800,-127);
}
else if(autoMode==3){
displayLCDCenteredString(0, "flags");
robotDriveStraight(2000,127);
robotDriveStraight(2000,-127);
}else if(autoMode==4){
displayLCDCenteredString(0, "caps");
robotDriveStraight(1800,127);
robotDriveStraight(1800,-127);
}

	// ..........................................................................
	// Insert user code here.
	// ..........................................................................

	// Remove this function call once you have "real" code.
	AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*
*/
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
/*
We are creating task program for our rubber band flipper
*/
int stateOfIntake = 1;
task handleIntake()
{
	ClearTimer(T1);
	while(true)
	{
		if (vexRT[Btn6U] && time1[T1] > 500){
			ClearTimer(T1);
			if (stateOfIntake == 1){
				stateOfIntake = 3;
				} else {
				stateOfIntake = 1;
			} // stateOfIntake
		} // if Btn6U

		if (vexRT[Btn6D] && time1[T1] > 500){
			ClearTimer(T1);
			if (stateOfIntake == 1){
				stateOfIntake = 2;
				}else {
				stateOfIntake = 1;
			}
		}

		if (stateOfIntake == 1){
			motor [intakeMotor] = 0;
		}
		if (stateOfIntake == 2){
			motor [intakeMotor] = -127;
		}
		if (stateOfIntake == 3){
			motor [intakeMotor] = 127;
		}
	}
}
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++
Mecanum Drive with Deadzone Thresholds
- This program allows you to remotely control a robot with mecanum wheels.
- The left joystick Y-axis controls the robot's forward and backward movement.
- The left joystick X-axis controls the robot's left and right movement.
- The right joystick X-axis controls the robot's rotation.
- This program incorportes a threshold/deadzone that allows very low Joystick values to be ignored.
This allows the robot to ignore values from the Joysticks when they fail to center at 0,
and provides a margin of error for the driver when they only want the robot to move in one axis.
[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        frontRight          VEX Motor             Front Right motor
Motor Port 3        backRight           VEX Motor             Back Right motor
Motor Port 4        frontLeft           VEX Motor             Front Left motor
Motor Port 5        backLeft            VEX Motor             Back Left motor
--------------------------------------------------------------------------------------------------*/
task usercontrol()
{
	// User control code here, inside the loop
	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
	startTask (handleIntake);
	while (true)
	{
		// This is the main execution loop for the user control program.
		// Each time through the loop your program should update motor + servo
		// values based on feedback from the joysticks.

		// ........................................................................
		// Insert user code here. This is where you use the joystick values to
		// update your motors, etc.
		// ........................................................................

		// Remove this function call once you have "real" code.
		//Create "deadzone" for Y1/Ch3
		if(abs(vexRT[Ch3]) > threshold)
			Y1 = vexRT[Ch3];
		else
			Y1 = 0;
		//Create "deadzone" for X1/Ch4
		if(abs(vexRT[Ch4]) > threshold)
			X1 = vexRT[Ch4];
		else
			X1 = 0;
		//Create "deadzone" for X2/Ch1
		if(abs(vexRT[Ch1]) > threshold)
			X2 = vexRT[Ch1];
		else
			X2 = 0;

		//Remote Control Commands
		motor[frontRight] = Y1 - X2 - X1;
		motor[backRight] =  Y1 - X2 + X1;
		motor[frontLeft] = Y1 + X2 + X1;
		motor[backLeft] =  Y1 + X2 - X1;
	}
	stopAllTasks ();
}
