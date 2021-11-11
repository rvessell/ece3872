#define samples 6
int thresh = 500;
double base[10];

void listen(){
  
  int count = 0;
  int16_t* peakVals = new int16_t[samples];
  unsigned long* peakMils = new unsigned long[samples];
  bool attack = false;
  int releaseCount = 0;
  int attackCount = 0;
  double peakVal;
  
  while(doPlayback) {
    peakVal = analogRead(0);
    Serial.println(peakVal);
    if (peakVal > thresh && !attack) {
      if (attackCount < 20) {
        attackCount++;
      } else {
        peakVals[count] = peakVal;
        peakMils[count] = millis();
        //Serial.println(peakMils[count]);
        count++;
        attack = true;
        attackCount = 0;
      }
    } else if (peakVal <= thresh) {
      if (releaseCount < 20) {
        releaseCount++;
      } else {
        attack = false;
        releaseCount = 0;
      }
    }
    // once we get enough samples, we measure for the shortest duration
    unsigned long minMils;
    if (count == samples - 1) {
      //Serial.println("reached 6 samples");
      minMils = 100000;
      for (int i = 0; i < samples; ++i) {
        if (peakMils[i + 1] - peakMils[i] < minMils) {
          minMils = peakMils[i + 1] - peakMils[i];
        }
      }
      //bpm calculation from milliseconds
      double bpm = 60/(double)minMils * 1000 / 3;
      Serial.print("BPM: ");
      Serial.print(bpm);
      
    }else if(count == samples){
      //enter our playback loop
      //adjust minMils by the amount of delay we have for motors, roughly 30ms
      minMils -= 50;
      Serial.println("Waiting to join in");
      delay(minMils*9);
      doListen = false;
      count = 0;
      playSong(minMils);
    }
  }
}

void testListen()
{
  int count = 0;
  int16_t* peakVals = new int16_t[4];
  unsigned long* peakMils = new unsigned long[4];
  bool attack = false;
  int releaseCount = 0;
  int attackCount = 0;
  double peakVal;
  
  while(1) {
  
    peakVal = analogRead(0);
    Serial.println(peakVal);
    if (peakVal > thresh && !attack) {
      if (attackCount < 20) {
        attackCount++;
      } else {
        peakVals[count] = peakVal;
        peakMils[count] = millis();
        //Serial.println(peakMils[count]);
        count++;
        attack = true;
        attackCount = 0;
      }
    } else if (peakVal <= thresh) {
      if (releaseCount < 20) {
        releaseCount++;
      } else {
        attack = false;
        releaseCount = 0;
      }
    }
    // once we get enough samples, we measure for the shortest duration
    if (count == 19) {
      unsigned long minMils = 100000;
      for (int i = 0; i < 4; ++i) {
        if (peakMils[i + 1] - peakMils[i] < minMils) {
          minMils = peakMils[i + 1] - peakMils[i];
        }
      }
      //bpm calculation from milliseconds
      double bpm = 60/(double)minMils * 1000;
      //display on the screen the estimated BPM or blink an LED
    }
  }  
}
