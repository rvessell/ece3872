#include "arduinoFFT.h"

/*************************************************

 * Public Constants

 *************************************************/


#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047

#define DATA_SIZE 128
#define FS 8000
#define BPM 120
#define timeSig .75

arduinoFFT FFT = arduinoFFT();

unsigned int period;
unsigned long ms;

double vReal[DATA_SIZE];
double vImag[DATA_SIZE];

int rowC4[]={
  NOTE_C4,NOTE_C4,NOTE_C4,NOTE_D4,NOTE_E4,
  NOTE_E4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,
  NOTE_C5,NOTE_C5,NOTE_C5,NOTE_G4,NOTE_G4,
  NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_C4,
  NOTE_C4,NOTE_C4,NOTE_G4,NOTE_F4,NOTE_E4,
  NOTE_D4,NOTE_C4
};

int rowC5[]={
  NOTE_C5,NOTE_C5,NOTE_C5,NOTE_D5,NOTE_E5,
  NOTE_E5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,
  NOTE_C6,NOTE_C6,NOTE_C6,NOTE_G5,NOTE_G5,
  NOTE_G5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_C5,
  NOTE_C5,NOTE_C5,NOTE_G5,NOTE_F5,NOTE_E5,
  NOTE_D5,NOTE_C5
};

double tempoDur[]={
  1,1,.66,.33,1,.66,.33,.66,.33,2,
  .33,.33,.33,.33,.33,.33,.33,.33,
  .33,.33,.33,.33,.66,.33,.66,.33,2
};

void playMusic(){
  for(int i = 0; i < 27; ++i){
    tone(13,rowC5[i],(1000*timeSig*tempoDur[i])/(BPM/60));
    //delay(1000*timeSig*tempoDur[i]/(BPM/60));
  }
}

void setup(void)
{
  Serial.begin(115200);
  period = round(1000000*(1.0/FS));

}

void loop(void)
{
//  for(int i = 0; i < DATA_SIZE; ++i){
//    ms = micros();
//    vReal[i] = analogRead(0);
//    vImag[i] = 0;
//    while(micros() < ms+period){
//    
//    }
//  }
//  
//  
//  FFT.Windowing(vReal, DATA_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
//  FFT.Compute(vReal, vImag, DATA_SIZE, FFT_FORWARD);
//  FFT.ComplexToMagnitude(vReal, vImag, DATA_SIZE);
//
//  double peak = FFT.MajorPeak(vReal, DATA_SIZE, FS);
//  Serial.println(peak);

  playMusic();
  
}
