void guiHandling(){
  ledBlink();
  unsigned long prevButtonMillis = millis();
  bool resetFlag = false;
  while (digitalRead(guiButton) == LOW){
    if (millis()-prevButtonMillis >= 3000){ //perform reset if debugbutton still low over 3second
      resetFlag = true;
      debugE("Reset to default...");
      ledBlink();
      prevButtonMillis = millis();
    }
  }
  if (resetFlag == true) {
    resetFlag = false;
    dataDefault();
    ESP.restart();
  }
  guiSetup();
  while (guiMode == true) {
    guiLoop();
  }
}

void guiSetup() {
  apSetup();
  serverSetup();
  ledOn();
}

void guiLoop() {
  static unsigned long lastMeasurement = 0;
  if (millis() - lastMeasurement > 10000) {
    sensorMeasurement();
    serverSentEvents();
    debugP("FreeRam : "+String(ESP.getFreeHeap()/1000));
    lastMeasurement = millis();
  }
}
