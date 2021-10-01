void listen(){
  
  int count = 0;
  int16_t* peakVals = new int16_t[20];
  unsigned long* peakMils = new unsigned long[20];
  bool attack = false;
  int releaseCount = 0;
  int attackCount = 0;
  double peakVal;
  
  while(1) {
  
    peakVal = analogRead(0);
    Serial.println(peakVal);
    if (peakVal > 716 && !attack) {
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
    } else if (peakVal <= 716) {
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
      for (int i = 0; i < 19; ++i) {
        if (peakMils[i + 1] - peakMils[i] < minMils) {
          minMils = peakMils[i + 1] - peakMils[i];
        }
      }
      //bpm calculation from milliseconds
      double bpm = 60/(double)minMils * 1000 / 3;
      //enter our playback loop
      doListen = false;
      playSong();
      
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
    if (peakVal > 716 && !attack) {
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
    } else if (peakVal <= 716) {
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
