#include <math.h>
#include <stdio.h>
#define speakerPIN 5
#define BUTTON_PIN 2
#define songLength 54

int octave = 4;
float C = 16.3516*pow(2,octave);
float D = 18.35405*pow(2,octave);
float E = 20.60172*pow(2,octave);
float F = 21.82676*pow(2,octave);
float G = 24.49971*pow(2,octave);
float A = 27.5*pow(2,octave);
float B = 30.86771*pow(2,octave);
float high_C = 32.70320*pow(2,octave);
float rest = 0;

float notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
int gap = 100;



int lastButtonState;    
int currentButtonState = LOW;

void changeFrequency(int octave){
  
  notes[0,2,4,38,40,42,53] = 16.3516*pow(2,octave);
  D = 18.35405*pow(2,octave);
  E = 20.60172*pow(2,octave);
  F = 21.82676*pow(2,octave);
  G = 24.49971*pow(2,octave);
  A = 27.5*pow(2,octave);
  B = 30.86771*pow(2,octave);
  high_C = 32.70320*pow(2,octave);
  rest = 0;
  Serial.print("octave is ");
  Serial.println(octave);
  Serial.println(C);
  Serial.println(G);
  Serial.println(high_C);
  return notes;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN,INPUT);
  currentButtonState = digitalRead(BUTTON_PIN);

}

void playSong(){
  int i_note_index = 0; 
  while(i_note_index < songLength){
      lastButtonState = currentButtonState;
      currentButtonState = digitalRead(BUTTON_PIN);  
      if(lastButtonState == HIGH && currentButtonState == LOW) {
          octave++;
      if(octave == 7){
          octave = 1;
      }
      changeFrequency(octave);
  }
      tone(speakerPIN, notes[i_note_index], gap*beats[i_note_index]);
      delay(gap*beats[i_note_index]);
      i_note_index++;
  }
  if(i_note_index >= songLength) {
    i_note_index = 0;
  } 
}

void loop() {
  playSong();
}
