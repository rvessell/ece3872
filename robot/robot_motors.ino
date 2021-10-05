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

  //spin left from 0 to 180
  if(pos == 0){
    for(pos = 0; pos <= 180; pos+=5){
      servo1.write(pos);
      servo2.write(pos);
      Serial.println(pos);
    }
    pos = 180;
  }else{
    for(pos = 180; pos >= 0; pos-=5){
      servo1.write(pos);
      servo2.write(pos);
      Serial.println(pos);
    }
    pos = 0;
  }
}
