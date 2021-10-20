#include <Servo.h>

#define MOTOR_PIN1 10
#define MOTOR_PIN2 11

Servo servo1;
Servo servo2;
int pos = 0;
bool motorSetup = false;

void setupMotor(){
  servo1.attach(MOTOR_PIN1);
  servo2.attach(MOTOR_PIN2);
  servo1.write(pos);
  servo2.write(pos);
}

void moveMotors(){
  if(!motorSetup){
    setupMotor();
    motorSetup = true;
  }
  Serial.println("Moving motor...");
  //need a 2ms delay
  if(pos == 0){
    for(pos = 0; pos <= 90; pos+=5){
      servo1.write(pos);
      servo2.write(pos);
      delay(2);
    }
    pos = 90;
  }else{
    for(pos = 90; pos >= 0; pos-=5){
      servo1.write(pos);
      servo2.write(pos);
      delay(2);
    }
    pos = 0;
  }
}
