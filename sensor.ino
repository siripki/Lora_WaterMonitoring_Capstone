void sensorOn() {
  digitalWrite(mosfetPin, 1);
  delay(10);
}
void sensorOff() {
  digitalWrite(mosfetPin, 0);
  delay(10);
}

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
  sensorOn();
  float temporary;
  dallas.setResolution(10);
  for (int i = 0; i < 4; i++) {
    dallas.requestTemperatures();
    temporary = mafTemp.addSample(dallas.getTempCByIndex(0));
  }
  sensorOff();
  return temporary * tempCal;
}

float getTds() {
  int R1 = 1000;
  int Ra = 25;  //Resistance of powering Pins
  int adc;
  float Vin = 3.31;
  float K = 2.88;
  float TempCoef = 0.019;
  float PPMconversion = 0.5;
  float R2;
  float volt;
  float ppm;
  float EC;
  float EC25;
  R1 = R1 + Ra;
  digitalWrite(tdsPin, 1);
  adc = ads.readADC_SingleEnded(3);
  adc = ads.readADC_SingleEnded(3);
  digitalWrite(tdsPin, 0);

  volt = ads.computeVolts(adc);
  debugP("volt : "+String(volt));
  R2 = (volt * R1) / (Vin - volt);
  R2 = R2 - Ra;  //acounting for Digital Pin Resitance
  debugP("R2 : "+String(R2));
  EC = 1000 / (R2 * K);

  //*************Compensating For Temperaure********************//
  EC25 = EC / (1 + TempCoef * (temp - 25.0));
  ppm = (EC25) * (PPMconversion * 1000);
  if (ppm < 0) ppm = 0;

  return ppm * tdsCal;
}

void sensorMeasurement() {
  temp = getTemp();
  tdsValue = getTds();
  wlValue = getWaterLevel();
  debugP("Temp : " + String(temp));
  debugP("TDS  : " + String(tdsValue));
  debugP("Wl   : " + String(wlValue));
}