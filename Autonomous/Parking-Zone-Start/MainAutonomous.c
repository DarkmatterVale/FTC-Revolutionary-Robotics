#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     lightSensor,    sensorNone)
#pragma config(Sensor, S2,     SonarSensor,    sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     leftDriveMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightDriveMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)r
	//Sensors:
  		//lightSensor ( two at the front of the robot )
  		//lightSensor 2
  		//IRSensor
  		//IRSensor 2
  		//Gyroscope
  		//DistanceSensor
  		//DistanceSensor 2
  		//Compass sensor
  
//Defines
#define FORWARD_STANDARD 60
#define FORWARD_FULL 100

#define STOP 0

#define BACKWARD_STANDARD 60
#define BACKWARD_FULL 100
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Autonomous mode program for FTC Team 7983
//
//In this program, our overall goal is to have the robot score as many points as possible, in as little time as possible
//
//                                                Goals for Autonomous mode:
//                                            1. Drive robot from ramp to floor
//                                          2. Drop kickstand in center ball holder
//                                3. Load/Shoot autonomous loaded balls into center ball holders
//                                                4. Grab a goal and hold it
//                              5. Move to position we would like it to be at at end of autonomous
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

Author(s):
	- Vale Tolpegin
	
*/

//GLOBAL VARIABLES
int matValue =     0;
int surfaceValue = 0;
int rampValue =    0;
	
/*
To Do list:
	- Move manipulator 1 method needs to be overloaded

*/

void haltRobot()
{
  /*
  Rev 1.0
  This function is used to stop the robot
  
  Variables Used:
  	NONE
  
  Inputs:
  	NONE
  Outputs:
  	leftRobotMotor ( left drive motor )
  	rightRobotMotor ( right drive motor )
  	
  To Do:
  	NONE
  
  Author(s):
  	Vale Tolpegin
  */
  
  motor[ leftDriveMotor ]  = 0;
  motor[ rightDriveMotor ] = 0;
  wait1Msec( 100 );
}

void moveRobotForward( int speed )
{
  /*
  Rev 1.0
  This function will move the robot forward at a certain speed infinitesimally
  
  Variables Used:
  	speed        ---used to set power level that the motors are set
  
  Inputs:
  	Passed speed variable
  Outputs:
  	leftRobotMotor
  	rightRobotMotor
  	
  To Do:
  	NONE
  	
  Author(s):
  	Vale Tolpegin
  */
  	
  	
  motor[ leftDriveMotor ]  = 0; //stopping motors to eliminate any possible course deviations
  motor[ rightDriveMotor ] = 0;
  wait1Msec( 50 );
  
  motor[ leftDriveMotor ]  = speed; //setting the motors to the passed speed variable level power level ( in percent of highest possible speed )
  motor[ rightDriveMotor ] = speed;
}

void moveRobotForward( int speed, int encoderValue )
{
  /*
  Rev 1.0
  This function will move the robot forward at a certain speed for a certain number of encoder ticks
  
  Variables Used:
  	speed        ---used to set power level for the motors
  	encoderValue ---used as the judge for when to stop the motors
  
  Inputs:
  	Passed speed variable
  	Passed encoderValue variable
  	leftRobotMotor encoder
  	rightRobotMotor encoder
  Outputs:
  	leftRobotMotor
  	rightRobotMotor
  	
  To Do:
  	NONE
  
  Author(s):
  	Vale Tolpegin
  */
  	
  	
  motor[ leftDriveMotor ]  = 0; //stopping motors to eliminate any possible course deviations
  motor[ rightDriveMotor ] = 0;
  wait1Msec( 50 );
  
  nMotorEncoder[ leftDriveMotor ]  = 0; //resetting encoder values
  nMotorEncoder[ rightDriveMotor ] = 0;
  
  while ( nMotorEncoder[ leftDriveMotor ] <= encoderValue && nMotorEncoder[ rightDriveMotor ] <= encoderValue ) //while encoders have not moved past allowed distance
  {
    motor[ leftDriveMotor ]  = speed; //setting motors to passed speed variable power level
    motor[ rightDriveMotor ] = speed;
  }
  
  motor[ leftDriveMotor ]  = 0; //stopping motors after movement duration has occurred
  motor[ rightDriveMotor ] = 0;
}

void moveRobotBackward( int speed )
{
  /*
  Rev 1.0
  This function is used to move the robot backward at a certain speed
  
  Variables Used:
  	speed        ---used to set the power level for the motors
  
  Inputs:
  	Passed speed variable
  Outputs:
  	leftRobotMotor
  	rightRobotMotor
  	
  To Do:
  	NONE
  
  Author(s):
  	Vale Tolpegin
  */	
  
  	
  motor[ leftDriveMotor ]  = 0; //reset motors
  motor[ rightDriveMotor ] = 0;
  wait1Msec( 50 );
  
  motor[ leftDriveMotor ]  = -speed; //go backward
  motor[ rightDriveMotor ] = -speed;
}

void moveRobotBackward( int speed, int encoderValue )
{
  /*
  Rev 1.0
  This function is used for moving the robot backward at a certain speed for a certain number of encoder ticks
  
  Variables Used:
  	speed        ---used to set the power level for the motors
  	encoderValue ---used as the judge for when to stop the motors
  
  Inputs:
  	Passed speed variable
  	Passed encoderValue variable
  	leftRobotMotor encoder
  	rightRobotMotor encoder
  Outputs:
  	leftRobotMotor
  	RightRobotMotor
  
  To Do:
  	NONE
  
  Author(s):
  	Vale Tolpegin
  */
  	
  	
  motor[ leftDriveMotor ]  = 0; //reset motors
  motor[ rightDriveMotor ] = 0;
  wait1Msec( 50 );
  
  nMotorEncoder[ leftDriveMotor ]  = 0; //reset motor encoders
  nMotorEncoder[ rightDriveMotor ] = 0;
  
  while ( nMotorEncoder[ leftDriveMotor ] <= encoderValue && nMotorEncoder[ rightDriveMotor ] <= encoderValue ) //while encoders havent gone pase what is allowed
  {
    motor[ leftDriveMotor ]  = -speed; //go backward
    motor[ rightDriveMotor ] = -speed;
  }
  
  motor[ leftDriveMotor ]  = 0; //stop motors
  motor[ rightDriveMotor ] = 0;
}

void moveRobotLeft( int speed )
{
  /*
  Rev 1.0
  This function is used for turning the robot left at the passed speed variable infinitesimally
  
  Inputs:
  	Passed speed variable
  Outputs:
  	leftRobotMotor
  	RightRobotMotor
  
  To Do:
  	NONE
  
  Author(s):
  	Vale Tolpegin
  */	
  	
  	
  motor[ leftDriveMotor ]  = 0; //stopping motors to eliminate course deviations
  motor[ rightDriveMotor ] = 0;
  wait1Msec( 50 );
  
  motor[ leftDriveMotor ]  = -speed; //setting motors to speed variable. Since I want to turn left, making the left motor the negative of the value for the second motor
  motor[rightDriveMotor ] = speed;
}

void moveRobotLeft( int speed, int encoderValue )
{
  /*
  Rev 1.0
  This function is used for turning the robot left at a passed speed value for a certain number of encoder ticks
  
  Inputs:
  	Passed speed variable
  	Passed encoderValue variable
  	leftRobotMotor encoder
  	rightRobotMotor encoder
  Outputs:
  	leftRobotMotor
  	rightRobotMotor
  
  To Do:
  	NONE
  	
  Author(s):
  	Vale Tolpegin
  */
  
  
  motor[ leftDriveMotor ]  = 0; //stopping motors to prevent course deviations
  motor[ rightDriveMotor ] = 0;
  wait1Msec( 50 );
  
  nMotorEncoder[ leftDriveMotor ]  = 0; //resetting encoder values
  nMotorEncoder[ rightDriveMotor ] = 0;
  
  while ( nMotorEncoder[ leftDriveMotor ] <= encoderValue && nMotorEncoder[ rightDriveMotor ] <= encoderValue ) //while encoders have not moved past allowed distance
  {
    motor[ leftDriveMotor ]  = -speed; //setting motors to passed speed variable power level
    motor[ rightDriveMotor ] = speed;
  }
  
  motor[ leftDriveMotor ]  = 0; //stopping motors after the robots have moved for the set amount of time
  motor[ rightDriveMotor ] = 0;
}

void moveRobotRight( int speed )
{
  /*
  Rev 1.1
  This function is used for turning the robot to the right at a certain speed infinitesimally
  
  Inputs:
  	Passed speed variable
  Outputs:
  	leftRobotMotor
  	rightRobotMotor
  
  To Do:
  	NONE
  	
  Author(s):
  	Vale Tolpegin
  */
  
  
  motor[leftDriveMotor] = 0; //reset motors
  motor[rightDriveMotor] = 0;
  wait1Msec( 50 );
  
  motor[ leftDriveMotor ]  = speed; //turn right
  motor[ rightDriveMotor ] = -speed;
}

void moveRobotRight( int speed, int encoderValue )
{
  /*
  Rev 1.0
  This function is used for turning the robot to the right at a certain speed for a certain number of encoder ticks
  
  Inputs:
  	Passed speed variable
  	Passed encoderValue variable
  	leftRobotMotor encoder
  	rightRobotMotor encoder
  	
  Outputs:
  	leftRobotMotor
  	rightRobotMotor
  
  To Do:
  	NONE
  	
  Author(s):
  	Vale Tolpegin
  */
  
  
  motor[ leftDriveMotor]   = 0; //resetting motors
  motor[ rightDriveMotor ] = 0;
  wait1Msec( 50 );
  
  nMotorEncoder[ leftDriveMotor ]  = 0; //resetting robot motor encoders
  nMotorEncoder[ rightDriveMotor ] = 0;
  
  while ( nMotorEncoder[ leftDriveMotor ] <= encoderValue && nMotorEncoder[ rightDriveMotor ] <= encoderValue ) //move while encoder ticks is less than the wanted amount
  {
    motor[ leftDriveMotor ]  = speed; //turn right
    motor[ rightDriveMotor ] = -speed;
  }
  
  motor[ leftDriveMotor ]  = 0; //once done, stop motors
  motor[ rightDriveMotor ] = 0;
}

task main()
{
	//Add main code here
}
