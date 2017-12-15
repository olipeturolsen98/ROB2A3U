#pragma config(Sensor, in1,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Sensor, in7,    armSensor,      sensorPotentiometer)
#pragma config(Sensor, in8,    lightSensor,    sensorReflection)
#pragma config(Sensor, dgtl6,  pushBtn,        sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           clawMotor,     tmotorServoContinuousRotation, openLoop)

int velocity = 63;

void stopMotors() {
	motor[rightMotor] = 0;
 	motor[leftMotor] = 0;

 	wait1Msec(1000);
}

void openClaw() {
	motor[clawMotor] = 60;

	wait1Msec(1000);

	clawOff();
}

void closeClaw() {
	motor[clawMotor] = -60;

	wait1Msec(1000);

	clawOff();
}

void clawOff() {
	motor[clawMotor] = 0;
}

void followLine()
{
	int threshold = 2300;

	while(true)
	{
		// RIGHT SENSOR DARK
		if(SensorValue(lineFollowerRIGHT) > threshold)
		{
			motor[leftMotor]  = velocity;
			motor[rightMotor] = 0;
		}
		// CENTER SENSOR DARK
		if(SensorValue(lineFollowerCENTER) > threshold)
		{
			motor[leftMotor]  = velocity;
			motor[rightMotor] = velocity;
		}
		// LEFT SENSOR DARK
		if(SensorValue(lineFollowerLEFT) > threshold)
		{
			motor[leftMotor]  = 0;
			motor[rightMotor] = velocity;
		}
		if(SensorValue(sonarSensor) < 12)
		{
			break;
		}
	}
}

void turnAround()
{
	motor[leftMotor] = 60;
	motor[rightMotor] = -60;
	wait1Msec(1000);
}

task LCD()
{
  clearLCDLine(0);
  clearLCDLine(1);

  bLCDBacklight = true;

  displayLCDPos(0,1);
  displayNextLCDString("LOKAVERKEFNI");

  displayLCDPos(1,1);
  displayNextLCDString("ROBOTICS");
}



task main()
{
	while (SensorValue[pushBtn] == 0) {

		StartTask(LCD);
		clawOpen();

		while(SensorValue(sonarSensor) > 9)
		{
			followLine();
		}

		stopMotors();
		clawClose();

		while(SensorValue(armSensor) < 3500)
		{
			motor[armMotor] = -30;
		}

		armOff();
		turnAround();

		while(SensorValue(sonarSensor) > 9)
		{
			followLine();
		}

		stopMotors();

		while(SensorValue(armSensor) > 250)
		{
			motor[armMotor] = 30;
		}

		armOff();
		clawOpen();
	}
}
