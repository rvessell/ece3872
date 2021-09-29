bool doListen = true;
bool doPlayback = false;

void setup() {
  Serial.begin(115200);
}

void loop() {
  //TODO: This loop needs to be updated with the controlling logic from the UI buttons
  while(doListen){
    listen();
  }
}
