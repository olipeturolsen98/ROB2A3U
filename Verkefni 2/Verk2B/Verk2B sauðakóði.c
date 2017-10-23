void moveForward(int dist)
{
// Encoder = 0

  while(leftEncoder < dist){

    if(rightEncoder == leftEncoder){ 
      // Forward = 80
    }
    else if(rightEncoder > leftEncoder){  
      // rightMotor = 60;
      // leftMotor = 80;
    }
    else{ 
      // rightMotor = 80;
      // leftMotor  = 60;
    }
  }
}

void moveBackwards(int dist){
  //Encoder = 0

  while(leftEncoder > dist){

    if(rightEncoder == leftEncoder){
      // rightMotor = -80;
      // leftMotor = -80;
    }
    else if(rightEncoder > leftEncoder){
      // rightMotor = -80;
      // leftMotor  = -60;
    }
    else{
      //rightMotor = -60;
      //leftMotor  = -80;
    }
  }
}

void stopMotors(){
  //motor = 0
  // Wait 2000 Ms
};

task main()
{
  dist = 0;

  for(int i = 0; i < 5; i++){
      dist += 580;
      moveForward(dist);
      stopMotors();
      moveBackwards(dist);
      stopMotors();
  }
}