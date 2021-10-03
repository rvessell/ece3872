#include <math.h>
#include <stdio.h>
#define speakerPIN 5
#define OCTAVE_BUTTON 2
#define START_BUTTON 3
#define MODE_BUTTON 4
#define songLength 54

int octave = 4;
float C = 16.3516;
float D = 18.35405;
float E = 20.60172;
float F = 21.82676;
float G = 24.49971;
float A = 27.5;
float B = 30.86771;
float high_C = 32.70320;
float rest = 0;
unsigned long last_interrupt_octave = 0;
unsigned long last_interrupt_startStop = 0;
bool doPlayback = false;
bool testMode = false;
bool prevMode = HIGH;
bool currMode = false;

float notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
int gap = 100;

//interrupt driven change of the octave. On a downpress the octave will increment up to 7 then go back to 4 on the next interrupt.
void changeOctave(){
  unsigned long interrupt = millis();
  if(interrupt - last_interrupt_octave > 200){
    if(octave == 7){
      octave = 4;
    }else{
      octave++;
    }
    Serial.println(octave);
  }
  last_interrupt_octave = millis();
}

//interrupt driven change of playback state
void startStop(){
  unsigned long interrupt = millis();
  if(interrupt - last_interrupt_startStop > 200){
    doPlayback = !doPlayback;
    Serial.println(doPlayback);
  }
  last_interrupt_startStop = millis();
}

//main playback method: TODO: make this method take in milliseconds
void playSong(){
  int i_note_index = 0; 
  while(i_note_index < songLength && doPlayback){
      tone(speakerPIN, notes[i_note_index]*pow(2,octave), gap*beats[i_note_index]);
      delay(gap*beats[i_note_index]);
      i_note_index++;
  }
  if(i_note_index >= songLength) {
    i_note_index = 0;
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
}

void loop() {
  //This block reads the current button state and if it constitutes a state change, we update the testMode variable
  currMode = digitalRead(MODE_BUTTON);
  if(currMode == LOW && prevMode != LOW){
    prevMode = LOW;
    testMode = !testMode;
  }else if(currMode == HIGH){
    prevMode = HIGH;
  }
  delay(200);
  //if doPlayback is true and we're in either of the two modes, do their respective tasks
  if(!testMode && doPlayback){
    playSong();
  }else if(testMode && doPlayback){
    Serial.println("Test Listen Mode!");
    delay(1000);
  }
}
