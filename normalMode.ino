void normalMode() {
  sensorMeasurement();
  sendData("{\"" + tempKey + "\":" + String(temp, 1) + ",\"" + phKey + "\":" + String(phValue, 1) + ",\"" + wlKey + "\":" + String(wlValue, 1) + "}");
}