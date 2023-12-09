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
  //type_board = readFile("/type_board.txt");
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

  xCal = readFile("/xCal.txt").toFloat();
  yCal = readFile("/yCal.txt").toFloat();
  tempCal = readFile("/tempCal.txt").toFloat();
  phCal = readFile("/phCal.txt").toFloat();

  tempKey = readFile("/tempKey.txt");
  phKey = readFile("/phKey.txt");
  wlKey = readFile("/wlKey.txt");
}

void dataDefault() {
  writeFile("/guiState.txt", "0");
  writeFile("/http_username.txt", "admin");
  writeFile("/http_password.txt", "admin");

  writeFile("/apSsid.txt", "Water Monitoring");
  writeFile("/apPass.txt", "12345678");
  writeFile("/sn.txt", "1");
  writeFile("/version.txt", "Firm 1.0 - GUI 1.1");
  writeFile("/board.txt", "Water Monitoring");
  // writeFile("/type_board.txt", "V2");
  writeFile("/maintainerName.txt", "siripki");

  writeFile("/connectivityType.txt", "1");

  writeFile("/devAddr.txt", "654310c1");
  writeFile("/appSKey.txt", "654310c1dd7a8b849dbf4e49b6d2e9a3");
  writeFile("/nwkSKey.txt", "654310c144dc0187f2f086b2ef47190a");
  writeFile("/classTx.txt", "1");
  writeFile("/sfTx.txt", "10");
  writeFile("/powerTx.txt", "20");
  writeFile("/channelTx.txt", "10");

  writeFile("/apnName.txt", "internet");
  writeFile("/apnUser.txt", "");
  writeFile("/apnPass.txt", "");

  writeFile("/wifiIpMode.txt", "DHCP");
  writeFile("/wifiSsid.txt", "Nasgor");
  writeFile("/wifiPass.txt", "ntahlahh");
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

  writeFile("/xCal.txt", "1");
  writeFile("/yCal.txt", "1");
  writeFile("/tempCal.txt", "1");
  writeFile("/phCal.txt", "1");

  writeFile("/tempKey.txt", "Tem");
  writeFile("/phKey.txt", "PH");
  writeFile("/wlKey.txt", "WL");
}