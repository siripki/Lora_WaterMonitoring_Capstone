void spiffSetup() {
  if (!SPIFFS.begin(true)) {
    debugE("SPIFFS Mount Failed");
    return;
  }
}

String readFile(const char *path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    debugE("Failed to open file for reading " + String(path));
    return String();
  }
  String fileContent;
  while (file.available()) {
    fileContent += (char)file.read();
  }
  //file.close();
  return fileContent;
}

void writeFile(const char *path, const char *fileContent) {
  File file = SPIFFS.open(path, "w");
  if (file.print(fileContent)) {
    debugP("- file written " + String(path));
  } else {
    debugE("- write failed " + String(path));
  }
  //file.close();
}

void readSettings() {
  if (readFile("/guiState.txt") == "1") {
    guiState = true;  //check guiState if it true, will automatically enter debugHandling (AP mode)
  }
  http_username = readFile("/http_username.txt");
  http_password = readFile("/http_password.txt");
  //Serial.println("username :"+http_username);
  //Serial.println("password :"+http_password);
  if (http_username == "" && http_password == "") {
    dataDefault();
    http_username = readFile("/http_username.txt");
    http_password = readFile("/http_password.txt");
    //
  }
  apSsid = readFile("/apSsid.txt");
  apPass = readFile("/apPass.txt");
  sn = readFile("/sn.txt");
  version = readFile("/version.txt");
  board = readFile("/board.txt");
  type_board = readFile("/type_board.txt");
  maintainerName = readFile("/maintainerName.txt");

  connectivityType = readFile("/connectivityType.txt").toInt();

  devAddr = readFile("/devAddr.txt");
  appSKey = readFile("/appSKey.txt");
  nwkSKey = readFile("/nwkSKey.txt");
  classTx = readFile("/classTx.txt").toInt();
  sfTx = readFile("/sfTx.txt").toInt();
  powerTx = readFile("/powerTx.txt").toInt();
  channelTx = readFile("/channelTx.txt").toInt();

  apnName = readFile("/apnName.txt");
  apnUser = readFile("/apnUser.txt");
  apnPass = readFile("/apnPass.txt");

  wifiIpMode = readFile("/wifiIpMode.txt");
  wifiSsid = readFile("/wifiSsid.txt");
  wifiPass = readFile("/wifiPass.txt");
  wifiLocalIP = readFile("/wifiLocalIP.txt");
  wifiGateway = readFile("/wifiGateway.txt");
  wifiSubnet = readFile("/wifiSubnet.txt");
  wifiDNS = readFile("/wifiDNS.txt");

  mqttBroker = readFile("/mqttBroker.txt");
  mqttPort = readFile("/mqttPort.txt");
  mqttID = readFile("/mqttID.txt");
  mqttTopic = readFile("/mqttTopic.txt");
  mqttUser = readFile("/mqttUser.txt");
  mqttPass = readFile("/mqttPass.txt");
  broker = readFile("/broker.txt");

  uplinkInterval = readFile("/uplinkInterval.txt").toInt();

  statusRelay1 = readFile("/statusRelay1.txt").toInt();

  timeTask1R1Hour = readFile("/timeTask1R1Hour.txt").toInt();
  timeTask1R1Minute = readFile("/timeTask1R1Minute.txt").toInt();
  durationTask1R1 = readFile("/durationTask1R1.txt").toInt();

  timeTask2R1Hour = readFile("/timeTask2R1Hour.txt").toInt();
  timeTask2R1Minute = readFile("/timeTask2R1Minute.txt").toInt();
  durationTask2R1 = readFile("/durationTask2R1.txt").toInt();

  timeTask3R1Hour = readFile("/timeTask3R1Hour.txt").toInt();
  timeTask3R1Minute = readFile("/timeTask3R1Minute.txt").toInt();
  durationTask3R1 = readFile("/durationTask3R1.txt").toInt();

  timeTask4R1Hour = readFile("/timeTask4R1Hour.txt").toInt();
  timeTask4R1Minute = readFile("/timeTask4R1Minute.txt").toInt();
  durationTask4R1 = readFile("/durationTask4R1.txt").toInt();

  tempThresR1 = readFile("/tempThresR1.txt").toFloat();
  humiThresR1 = readFile("/humiThresR1.txt").toFloat();
  durationSchR1 = readFile("/durationSchR1.txt").toInt();
  intervalSchR1 = readFile("/intervalSchR1.txt").toInt();

  statusSch1R1 = readFile("/statusSch1R1.txt").toInt();
  startSch1R1Hour = readFile("/startSch1R1Hour.txt").toInt();
  startSch1R1Minute = readFile("/startSch1R1Minute.txt").toInt();
  stopSch1R1Hour = readFile("/stopSch1R1Hour.txt").toInt();
  stopSch1R1Minute = readFile("/stopSch1R1Minute.txt").toInt();

  statusSch2R1 = readFile("/statusSch2R1.txt").toInt();
  startSch2R1Hour = readFile("/startSch2R1Hour.txt").toInt();
  startSch2R1Minute = readFile("/startSch2R1Minute.txt").toInt();
  stopSch2R1Hour = readFile("/stopSch2R1Hour.txt").toInt();
  stopSch2R1Minute = readFile("/stopSch2R1Minute.txt").toInt();

  statusRelay2 = readFile("/statusRelay2.txt").toInt();

  timeTask1R2Hour = readFile("/timeTask1R2Hour.txt").toInt();
  timeTask1R2Minute = readFile("/timeTask1R2Minute.txt").toInt();
  durationTask1R2 = readFile("/durationTask1R2.txt").toInt();

  timeTask2R2Hour = readFile("/timeTask2R2Hour.txt").toInt();
  timeTask2R2Minute = readFile("/timeTask2R2Minute.txt").toInt();
  durationTask2R2 = readFile("/durationTask2R2.txt").toInt();

  timeTask3R2Hour = readFile("/timeTask3R2Hour.txt").toInt();
  timeTask3R2Minute = readFile("/timeTask3R2Minute.txt").toInt();
  durationTask3R2 = readFile("/durationTask3R2.txt").toInt();

  timeTask4R2Hour = readFile("/timeTask4R2Hour.txt").toInt();
  timeTask4R2Minute = readFile("/timeTask4R2Minute.txt").toInt();
  durationTask4R2 = readFile("/durationTask4R2.txt").toInt();

  tempThresR2 = readFile("/tempThresR2.txt").toFloat();
  humiThresR2 = readFile("/humiThresR2.txt").toFloat();
  durationSchR2 = readFile("/durationSchR2.txt").toInt();
  intervalSchR2 = readFile("/intervalSchR2.txt").toInt();

  statusSch1R2 = readFile("/statusSch1R2.txt").toInt();
  startSch1R2Hour = readFile("/startSch1R2Hour.txt").toInt();
  startSch1R2Minute = readFile("/startSch1R2Minute.txt").toInt();
  stopSch1R2Hour = readFile("/stopSch1R2Hour.txt").toInt();
  stopSch1R2Minute = readFile("/stopSch1R2Minute.txt").toInt();

  statusSch2R2 = readFile("/statusSch2R2.txt").toInt();
  startSch2R2Hour = readFile("/startSch2R2Hour.txt").toInt();
  startSch2R2Minute = readFile("/startSch2R2Minute.txt").toInt();
  stopSch2R2Hour = readFile("/stopSch2R2Hour.txt").toInt();
  stopSch2R2Minute = readFile("/stopSch2R2Minute.txt").toInt();

  dateCal = readFile("/dateCal.txt");
  timeCal = readFile("/timeCal.txt");
  tempCal = readFile("/tempCal.txt").toFloat();
  humiCal = readFile("/humiCal.txt").toFloat();

  tempKey = readFile("/tempKey.txt");
  humiKey = readFile("/humiKey.txt");
}

void dataDefault() {
  writeFile("/guiState.txt", "0");
  writeFile("/http_username.txt", "admin");
  writeFile("/http_password.txt", "admin");

  writeFile("/apSsid.txt", "Penyiram Otomatis");
  writeFile("/apPass.txt", "12345678");
  //writeFile("/sn.txt", "0");
  //writeFile("/version.txt", "Firm 3.0 - GUI 2.5");
  writeFile("/board.txt", "WC-2200-V3-Panel");
  writeFile("/type_board.txt", "V2");
  //writeFile("/maintainerName.txt", "siripki");

  writeFile("/connectivityType.txt", "5");

  writeFile("/devAddr.txt", "654310c1");
  writeFile("/appSKey.txt", "654310c1dd7a8b849dbf4e49b6d2e9a3");
  writeFile("/nwkSKey.txt", "654310c144dc0187f2f086b2ef47190a");
  writeFile("/classTx.txt", "1");
  writeFile("/sfTx.txt", "10");
  writeFile("/powerTx.txt", "20");
  writeFile("/channelTx.txt", "1");

  writeFile("/apnName.txt", "internet");
  writeFile("/apnUser.txt", "");
  writeFile("/apnPass.txt", "");

  writeFile("/wifiIpMode.txt", "DHCP");
  writeFile("/wifiSsid.txt", "Egrotek");
  writeFile("/wifiPass.txt", "jamurtiram");
  writeFile("/wifiLocalIP.txt", "");
  writeFile("/wifiGateway.txt", "");
  writeFile("/wifiSubnet.txt", "");
  writeFile("/wifiDNS.txt", "");

  writeFile("/mqttBroker.txt", "iot.egrotek.id");
  writeFile("/mqttPort.txt", "1883");
  writeFile("/mqttID.txt", "DEVKLgxBTJGAqhQBJEcv0");
  writeFile("/mqttTopic.txt", "egrotek/pub/APPRNNUlQ2l3lVrt3Z7Zm/DEVKLgxBTJGAqhQBJEcv0");
  writeFile("/mqttUser.txt", "MnyEemqrgSrF8VTMWO");
  writeFile("/mqttPass.txt", "ccQXonHZGnZS1USggc");
  writeFile("/broker.txt", "custom");

  writeFile("/uplinkInterval.txt", "1");  //in minute

  // Menulis nilai untuk Relay 1
  writeFile("/statusRelay1.txt", "0");

  writeFile("/timeTask1R1Hour.txt", "00");
  writeFile("/timeTask1R1Minute.txt", "00");
  writeFile("/durationTask1R1.txt", "0");

  writeFile("/timeTask2R1Hour.txt", "00");
  writeFile("/timeTask2R1Minute.txt", "00");
  writeFile("/durationTask2R1.txt", "0");

  writeFile("/timeTask3R1Hour.txt", "00");
  writeFile("/timeTask3R1Minute.txt", "00");
  writeFile("/durationTask3R1.txt", "0");

  writeFile("/timeTask4R1Hour.txt", "00");
  writeFile("/timeTask4R1Minute.txt", "00");
  writeFile("/durationTask4R1.txt", "0");

  writeFile("/tempThresR1.txt", "27.0");  // Contoh nilai suhu dalam format float
  writeFile("/humiThresR1.txt", "60.0");  // Contoh nilai kelembaban dalam format float
  writeFile("/durationSchR1.txt", "0");
  writeFile("/intervalSchR1.txt", "0");

  writeFile("/statusSch1R1.txt", "0");
  writeFile("/startSch1R1Hour.txt", "00");
  writeFile("/startSch1R1Minute.txt", "00");
  writeFile("/stopSch1R1Hour.txt", "00");
  writeFile("/stopSch1R1Minute.txt", "00");

  writeFile("/statusSch2R1.txt", "0");
  writeFile("/startSch2R1Hour.txt", "00");
  writeFile("/startSch2R1Minute.txt", "00");
  writeFile("/stopSch2R1Hour.txt", "00");
  writeFile("/stopSch2R1Minute.txt", "00");

  // Menulis nilai untuk Relay 2
  writeFile("/statusRelay2.txt", "0");

  writeFile("/timeTask1R2Hour.txt", "00");
  writeFile("/timeTask1R2Minute.txt", "00");
  writeFile("/durationTask1R2.txt", "0");

  writeFile("/timeTask2R2Hour.txt", "00");
  writeFile("/timeTask2R2Minute.txt", "00");
  writeFile("/durationTask2R2.txt", "0");

  writeFile("/timeTask3R2Hour.txt", "00");
  writeFile("/timeTask3R2Minute.txt", "00");
  writeFile("/durationTask3R2.txt", "0");

  writeFile("/timeTask4R2Hour.txt", "00");
  writeFile("/timeTask4R2Minute.txt", "00");
  writeFile("/durationTask4R2.txt", "0");

  writeFile("/tempThresR2.txt", "27.0");  // Contoh nilai suhu dalam format float
  writeFile("/humiThresR2.txt", "60.0");  // Contoh nilai kelembaban dalam format float
  writeFile("/durationSchR2.txt", "0");
  writeFile("/intervalSchR2.txt", "0");

  writeFile("/statusSch1R2.txt", "0");
  writeFile("/startSch1R2Hour.txt", "00");
  writeFile("/startSch1R2Minute.txt", "00");
  writeFile("/stopSch1R2Hour.txt", "00");
  writeFile("/stopSch1R2Minute.txt", "00");

  writeFile("/statusSch2R2.txt", "0");
  writeFile("/startSch2R2Hour.txt", "00");
  writeFile("/startSch2R2minute.txt", "00");
  writeFile("/stopSch2R2Hour.txt", "00");
  writeFile("/stopSch2R2Minute.txt", "00");

  writeFile("/dateCal.txt", "2023-11-11");
  writeFile("/timeCal.txt", "11:11");
  writeFile("/tempCal.txt", "1");
  writeFile("/humiCal.txt", "1");

  writeFile("/tempKey.txt", "Temperature");
  writeFile("/humiKey.txt", "Humidity");

  dateCal = readFile("/dateCal.txt");
  timeCal = readFile("/timeCal.txt");
  setTimeNow();
}