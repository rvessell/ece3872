#include <math.h>
#include <stdio.h>
#define speakerPIN 5
#define OCTAVE_BUTTON 3
#define START_BUTTON 2
#define MODE_BUTTON 0
#define songLength 54
#define ledSTARTPIN 7
#define ledOCTAVEPIN 8
#define ledMODEPIN 9


//testing 123

int octave = 4;
unsigned long last_interrupt = 0;
bool doPlayback = false;
bool doListen = false;
bool testMode = false;
bool prevMode = HIGH; 
bool currMode = false;
bool octaveLED = false;

//interrupt driven change of the octave. On a downpress the octave will increment up to 7 then go back to 4 on the next interrupt.
void changeOctave(){
  unsigned long interrupt = millis();
  if(interrupt - last_interrupt > 500){
    if(octave == 7){
      octave = 4;
    }else{
      octave++;
    }
    octaveLED = !octaveLED;  
    digitalWrite(ledOCTAVEPIN,octaveLED);     
    Serial.println(octave);
  }
  last_interrupt = interrupt;
}

//interrupt driven change of playback state
void startStop(){
  unsigned long interrupt = millis();
  if(interrupt - last_interrupt > 500){
    doPlayback = !doPlayback;
    Serial.println("doPlayback");
    digitalWrite(ledSTARTPIN, doPlayback);
  }
  last_interrupt = interrupt;

  if(!doPlayback){
    detachServos();
  }
}

//Setup serial and pins
void setup() {
  Serial.begin(115200);
  pinMode(OCTAVE_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(OCTAVE_BUTTON), changeOctave, FALLING);
  pinMode(START_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(START_BUTTON), startStop, FALLING);
  pinMode(MODE_BUTTON, INPUT_PULLUP);
  Serial.println("Waiting in idle mode");
  pinMode(ledSTARTPIN, OUTPUT);
  pinMode(ledOCTAVEPIN, OUTPUT);
  pinMode(ledMODEPIN, OUTPUT);
}

void loop() {
  //
  //This block reads the current button state and if it constitutes a state change, we update the testMode variable
  currMode = digitalRead(MODE_BUTTON);
  if(currMode == LOW && prevMode != LOW){
    prevMode = LOW;
    testMode = !testMode;
    digitalWrite(ledMODEPIN, testMode);
  }else if(currMode == HIGH){
    prevMode = HIGH;
  }
  delay(200);
  //if doPlayback is true and we're in either of the two modes, do their respective tasks
  if(!testMode && doPlayback){
    Serial.println("Listening...");
    listen();
    //playSong(100);
  }else if(testMode && doPlayback){
    Serial.println("Test Listen Mode!");
    delay(1000);
  }
}
