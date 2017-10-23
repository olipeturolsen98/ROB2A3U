#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port2,           rightMotor,    tmotorVex269, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex269, openLoop, reversed, encoder, encoderPort, dgtl1, 1000)

void moveForward(int dist)
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;

	while(SensorValue[leftEncoder] < dist){

		if(SensorValue[rightEncoder] == SensorValue[leftEncoder]){ // If rightEncoder has counted the same amount as leftEncoder:
			// Move Forward
			motor[rightMotor] = 80;
			motor[leftMotor]  = 80;
		}
		else if(SensorValue[rightEncoder] > SensorValue[leftEncoder]){	// If rightEncoder has counted more encoder counts
			// Turn slightly right
			motor[rightMotor] = 60;
			motor[leftMotor]  = 80;
		}
		else{	// Only runs if leftEncoder has counted more encoder counts
			// Turn slightly left
			motor[rightMotor] = 80;
			motor[leftMotor]  = 60;
		}
	}
}

void moveBackwards(int dist){
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;

	while(SensorValue[leftEncoder] > dist){

		if(SensorValue[rightEncoder] == SensorValue[leftEncoder]){ // If rightEncoder has counted the same amount as leftEncoder:
			motor[rightMotor] = -80;
			motor[leftMotor]  = -80;
		}
		else if(SensorValue[rightEncoder] > SensorValue[leftEncoder]){	// If rightEncoder has counted more encoder counts
			// Turn slightly right
			motor[rightMotor] = -80;
			motor[leftMotor]  = -60;
		}
		else{	// Only runs if leftEncoder has counted more encoder counts
			// Turn slightly left
			motor[rightMotor] = -60;
			motor[leftMotor]  = -80;
		}
	}
}

void stopMotors(){
	motor[rightMotor] = 0;
  motor[leftMotor] = 0;
  wait1Msec(2000);
};

task main()
{
	int dist = 0;

	for(int i = 0; i < 5; i++){
			dist += 580;
			moveForward(dist);
			stopMotors();
			moveBackwards(dist * -1);
			stopMotors();
	}
}
