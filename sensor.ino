void sensorSetup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dallas.begin();
  if (!ads.begin(0x48)) {
    debugE("Problem : ADS");
    delay(1000);
    if (!ads.begin()) {  //failover
      ESP.restart();
    }
    debugE("Status  : ADS Oke");
    return;
  }
}

float getWaterLevel() {
  float duration;
  float xValue;
  for (int i = 0; i < 4; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    //pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    yValue = mafWL.addSample((duration / 2) / 29.1);
    delay(100);
  }
  debugP("yValue " + String(yValue));
  xValue = (xCal + yCal) - yValue;

  return xValue;
}

float getTemp() {
  float temporary;
  dallas.setResolution(10);
  for (int i = 0; i < 4; i++) {
    dallas.requestTemperatures();                              // Perintah konversi suhu
    temporary = mafTemp.addSample(dallas.getTempCByIndex(0));  //Membaca data suhu dari sensor #0 dan mengkonversikannya ke nilai Celsius
  }
  return temporary*tempCal;
}

float getTds() {
  int adc;
  float tds;
  for (int i = 0; i < 4; i++) {
    adc = mafTds.addSample(ads.readADC_SingleEnded(3));
  }
  tds = adc;
  return tds*tdsCal;
}

void sensorMeasurement() {
  temp = getTemp();
  debugP("temp " + String(temp));
  tdsValue = getTds();
  debugP("tdsValue " + String(tdsValue));
  wlValue = getWaterLevel();
}