#define songLength 54

float C = 16.3516;
float D = 18.35405;
float E = 20.60172;
float F = 21.82676;
float G = 24.49971;
float A = 27.5;
float B = 30.86771;
float high_C = 32.70320;
float rest = 0;

float notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
//int gap = 100;

//main playback method: TODO: make this method take in milliseconds
void playSong(unsigned long gap){
  int i_note_index = 0; 
  while(i_note_index < songLength && doPlayback){
    //Serial.println("Playing...");
      tone(speakerPIN, notes[i_note_index]*pow(2,octave), (gap/2)*beats[i_note_index]);
      delay((gap/2)*beats[i_note_index]);
      if((i_note_index % 2) == 0){
        moveMotors();
      }
      i_note_index++;
    if(i_note_index >= songLength) {
      i_note_index = 0;
    }
  }
}
