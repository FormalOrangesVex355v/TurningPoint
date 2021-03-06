#pragma config(Motor,  port2,           frontRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           backRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           frontLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  port5,           backLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port6,           intakeMotor,      tmotorNormal, openLoop)
#pragma config(Motor,  port7,           cannonMotor,      tmotorNormal, openLoop)
#pragma config(Motor,  port8,           aimCannonMotor,      tmotorNormal, openLoop)
#pragma config(Motor,  port9,           liftMotor,      tmotorNormal, openLoop)
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

// Include James Pearman's Gyro Lib
// From: https://github.com/jpearman/RobotCLibs/tree/master/gyroLib
#include "gyroLib2.c"

// These are the different choices we have
typedef enum {
	kLcdDispStart = 0,

	kLcdRedFlags    = 0,
	kLcdRedCaps,
	kLcdBlueFlags,
	kLcdBlueCaps,

	kLcdDispNumber
} kLcdDispType;

// globals for tracking choices
short           autoMode = (-1);

// Display LCD choice
void lcdMenuDisplay(kLcdDispType current)
{
	//Switch case that allows the user to choose from 4 different options
	switch(current){
	case kLcdRedFlags:
		//Display first choice
		displayLCDCenteredString(0, "Red Flags");
		displayLCDCenteredString(1, "<     Enter    >");
		break;
	case kLcdRedCaps:
		//Display second choice
		displayLCDCenteredString(0, "Red Caps");
		displayLCDCenteredString(1, "<     Enter    >");
		break;
	case kLcdBlueFlags:
		//Display third choice
		displayLCDCenteredString(0, "Blue Flags");
		displayLCDCenteredString(1, "<     Enter    >");
		break;
	case kLcdBlueCaps:
		//Display fourth choice
		displayLCDCenteredString(0, "Blue Caps");
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
	kLcdDispType    mode = kLcdRedFlags;

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
			// set the autononomous mode
			autoMode = (short)mode;
			wait1Msec(1000);
			GyroInit();
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

void robotDriveStrafe(int runTime, int power) // Strafe - Not In Use
{
	motor[frontRight] = -1*power; //Full power is 127
	motor[frontLeft] = power; //Full power is 127
	motor[backRight] = power; //Full power is 127
	motor[backLeft] = -1*power; //Full power is 127
	wait1Msec(runTime);	//Run for three seconds
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
}

task autonomous()
{
	GyroReinit();
	if(autoMode==(short)kLcdRedFlags){
		displayLCDCenteredString(0, "flags");
		motor [cannonMotor] = -127;
		wait1Msec(4000);
		motor [cannonMotor] = 0;
		robotDriveStraight(2000,127);
		robotDriveStraight(2000,-127);
	}
	else if(autoMode==(short)kLcdRedCaps){
		displayLCDCenteredString(0, "caps");
		robotDriveStraight(1800,127);
		robotDriveStraight(1800,-127);
	}
	else if(autoMode==(short)kLcdBlueFlags){
		displayLCDCenteredString(0, "flags");
		motor [cannonMotor] = -127;
		wait1Msec(2000);
		motor [cannonMotor] = 0;
		robotDriveStraight(2000,127);
		robotDriveStraight(2000,-127);
	}
	else if(autoMode==(short)kLcdBlueCaps){
		displayLCDCenteredString(0, "caps");
		robotDriveStraight(1800,127);
		robotDriveStraight(1800,-127);
	}
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
	clearTimer(T1);
	while(true)
	{
		if (vexRT[Btn5U] && time1[T1] > 500){
			clearTimer(T1);
			if (stateOfIntake == 1){
				stateOfIntake = 3;
				} else {
				stateOfIntake = 1;
			} // stateOfIntake
		} // if Btn6U

		if (vexRT[Btn5D] && time1[T1] > 500){
			clearTimer(T1);
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
		wait10Msec(5);
	} // while }
}

task capLifter()
{
	while(true)
	{
		if(vexRT[Btn7U]==1){
			motor[liftMotor]=40;
		}
		else if(vexRT[Btn7D]==1){
			motor[liftMotor]=-40;
		}
		else{
			motor[liftMotor]=0;
		}
		wait10Msec(5);
	}
}

task capLifter2()
{
	while(true)
	{
		if(vexRT[Btn7U]==1){
			motor[liftMotor]=60;
		}

		wait10Msec(5);
	}
}

task aimCannon() // Aim Cannon
{
	while(true)
	{
		motor [aimCannonMotor] = 0;
		if (vexRT[Btn8U] ){ // { if Btn8U
			motor [aimCannonMotor] = 35; //
		} // if Btn6U }
		if (vexRT[Btn8D] ){ // { if Btn6D
			motor [aimCannonMotor] = -25; //
		} // if Btn8D }
		wait10Msec(5);
	} // while }
}
task ballCannon() // Ball Cannon
{
	while(true)
	{
		if (vexRT[Btn6U] ){ // { if Btn6U
			motor [cannonMotor] = -127;
		} // if Btn6U }
		else { // if not Btn6U {
			motor [cannonMotor] = 0;
		}
		wait10Msec(5);
	} // while }
}

task gyroLogger()
{
	while(true)
	{
		datalogDataGroupStart();

		datalogAddValue( 0, GyroAngleAbsGet() );
		datalogAddValue( 1, GyroAngleDegGet() );

		datalogDataGroupEnd();
		wait10Msec(5);
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
Motor Port 3        backRight           VE Motor             Front Left motor
Motor Port 5        backLeft            VX Motor             Back Right motor
Motor Port 4        frontLeft           VEXEX Motor             Back Left motor
--------------------------------------------------------------------------------------------------*/
task usercontrol()
{
	GyroReinit();
	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
	startTask (handleIntake);
	startTask (ballCannon);
	startTask (gyroLogger);
	startTask (aimCannon);
	startTask (capLifter);
	startTask (capLifter2);
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
		if(vexRT[btn7U]==0){
			if(abs(vexRT[Ch1]) > threshold)
				X2 = vexRT[Ch1];
			else
				X2 = 0;}

		//Remote Control Commands
		motor[frontRight] = Y1 - X2 - X1;
		motor[backRight] =  Y1 - X2 + X1;
		motor[frontLeft] = Y1 + X2 + X1;
		motor[backLeft] =  Y1 + X2 - X1;
		wait10Msec(5);
	}
	stopAllTasks ();
}
