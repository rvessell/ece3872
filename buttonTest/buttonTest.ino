
int buttonPin = 2;
int LED = 13;
int buttonValue = 0 ;

void setup() {
   // Define pin #12 as input and activate the internal pull-up resistor
  
  pinMode(buttonPin, INPUT_PULLUP);
  
   // Define pin #13 as output, for the LED
   pinMode(LED, OUTPUT);
   Serial.begin(9600);
}

void loop(){
   // Read the value of the button
  
   buttonValue = digitalRead(buttonPin);
   
  
   if (buttonValue == LOW){
     
      //  button pushed,  LED on
     
      digitalWrite(LED,HIGH);
      Serial.print(1);
   } else {
     
      // else ,  LED off
      digitalWrite(LED, LOW);
      Serial.print(0);
   }
}
