void normalMode() {
  sensorMeasurement();
  sendData("{\"" + tempKey + "\":" + String(temp, 1) + ",\"" + tdsKey + "\":" + String(tdsValue, 1) + ",\"" + wlKey + "\":" + String(wlValue, 1) + "}");
}