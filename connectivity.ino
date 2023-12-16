void connectivitySetup() {
  switch (connectivityType) {
    case 1:  //sendData using protocol LoRaWAN
      loraSetup();
      break;
    case 2:  //sendData using protocol MQTT via GSM
      gsmSetup();
      mqttSetup(mqttGsm);
      break;
    case 3:  //sendData using protocol MQTT via WiFi
      wifiSetup();
      mqttSetup(mqttWifi);
      break;
    case 4:  //sendData using protocol MQTT via Ethernet
      //sdsd
      break;
    case 5:  //sendData using protocol MQTT via Ethernet
      debugE("OFFLINE MODE");
      break;
    default:  //OFFLINE
      debugE("OFFLINE MODE");
      //sfdfs
      break;
  }
}

//LoRaWAN
void loraSetup() {
  if (!lora.init()) {
    debugE("Problem : Lora");
    delay(2000);
    return;
  }
  switch (classTx) {
    case 1:
      lora.setDeviceClass(CLASS_A);  // Set LoRaWAN Class change CLASS_A
      break;
    case 3:
      lora.setDeviceClass(CLASS_C);  // Set LoRaWAN Class changeCLASS_C
      break;
    default:
      lora.setDeviceClass(CLASS_A);  // Set LoRaWAN Class change CLASS_A
      break;
  }
  switch (sfTx) {
    case 7:
      lora.setDataRate(SF7BW125);
      break;
    case 8:
      lora.setDataRate(SF8BW125);
      break;
    case 9:
      lora.setDataRate(SF9BW125);
      break;
    case 10:
      lora.setDataRate(SF10BW125);
      break;
    case 11:
      lora.setDataRate(SF11BW125);
      break;
    case 12:
      lora.setDataRate(SF12BW125);
      break;
    default:
      lora.setDataRate(SF10BW125);  //default datarate
      break;
  }
  lora.setFramePortTx(5);
  switch (channelTx) {
    case 0:
      lora.setChannel(0);
      break;
    case 1:
      lora.setChannel(1);
      break;
    case 2:
      lora.setChannel(2);
      break;
    case 3:
      lora.setChannel(3);
      break;
    case 4:
      lora.setChannel(4);
      break;
    case 5:
      lora.setChannel(5);
      break;
    case 6:
      lora.setChannel(6);
      break;
    case 7:
      lora.setChannel(7);
      break;
    default:
      lora.setChannel(MULTI);
      break;
  }
  lora.setTxPower(powerTx);
  lora.setNwkSKey(nwkSKey.c_str());
  lora.setAppSKey(appSKey.c_str());
  lora.setDevAddr(devAddr.c_str());
}
void sendData_Lora(String msg, char *msgSeq) {
  //loraSetup();
  //lora.update();
  char myStr[msg.length() + 1];
  msg.toCharArray(myStr, msg.length() + 1);
  lora.sendUplink(myStr, strlen(myStr), 0);
  lora.update();
  debugE(myStr);  //debug
  debugE(msgSeq);
  debugE(" ");
  ledBlink();
  delay(3000);
}

//GSM
void gsmSetup() {
  sim800.begin(9600);
  if (!modem.waitForNetwork()) {
    debugE("Problem : Failed to connect provider");
    ESP.restart();
  }
  debugE("Status  : Connected to provider");
  //Serial.println("Signal Quality: " + String(modem.getSignalQuality()));
  if (!modem.gprsConnect(apnName.c_str(), apnUser.c_str(), apnPass.c_str())) {
    debugE("Problem : Failed to connect internet");
    ESP.restart();
  }
  debugE("Status  : Connected to internet");
}
void gsmCheck() {
  if (!modem.gprsConnect(apnName.c_str(), apnUser.c_str(), apnPass.c_str())) {
    if (!modem.waitForNetwork()) {
      debugE("Problem : Failed to connect provider");
      //modem.restart();
      ESP.restart();
    }
    debugE("Status  : Reconnected to provider");
    if (!modem.gprsConnect(apnName.c_str(), apnUser.c_str(), apnPass.c_str())) {
      debugE("Problem : Failed to connect internet");
      if (!modem.gprsConnect(apnName.c_str(), apnUser.c_str(), apnPass.c_str())) {
        ESP.restart();
      }
    }
  }
  debugE("Status  : Reconnected to internet");
}

//WiFi
void wifiSetup() {
  if (wifiIpMode == "static") {
    IPAddress local_IP = strToIP(wifiLocalIP);
    IPAddress gateway = strToIP(wifiGateway);
    IPAddress subnet = strToIP(wifiSubnet);
    IPAddress primaryDNS = strToIP(wifiDNS);
    WiFi.config(local_IP, gateway, subnet, primaryDNS, primaryDNS);
  }
  WiFi.setHostname((apSsid+" ["+sn+"]").c_str());
  WiFi.begin(wifiSsid.c_str(), wifiPass.c_str());
  debugE("Status  : Connecting to WiFi");
  // if (WiFi.status() == WL_CONNECTED) {
  //   debugE("Status  : Connected to WiFi");
  // }
}
IPAddress strToIP(String str) {
  IPAddress ret(getIpBlock(0, str), getIpBlock(1, str), getIpBlock(2, str), getIpBlock(3, str));
  return ret;
}
int getIpBlock(int index, String str) {
  char separator = '.';
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = str.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (str.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? str.substring(strIndex[0], strIndex[1]).toInt() : 0;
}

//AccessPoint
void apSetup() {
  if (connectivityType == 3) {
    WiFi.mode(WIFI_AP_STA);
  }
  WiFi.softAP((apSsid+" ["+sn+"]").c_str(), apPass.c_str());
}

//MQTT
void mqttSetup(PubSubClient &mqttType) {
  mqttType.setServer(mqttBroker.c_str(), mqttPort.toInt());
  debugE("Status  : MQTT Setup Finish");
  //mqttType.setCallback(callback);
}
void mqttConnect(PubSubClient &mqttType) {
  if (!mqttType.connected()) {
    debugE("Status  : Reconnecting to MQTT");
    mqttType.connect(mqttID.c_str(), mqttUser.c_str(), mqttPass.c_str());
    if (!mqttType.connected()) {
      mqttType.connect(mqttID.c_str(), mqttUser.c_str(), mqttPass.c_str());
      while (!mqttType.connected()) {
        ESP.restart();  //antisipasi kalo gabisa konek karena kuota abis
      }
    }
  }
  debugE("Status  : Reconnected to MQTT");
}
void sendData_Mqtt(String msg, PubSubClient &mqttType) {
  mqttConnect(mqttType);
  //String msg = "{\"WS\":0.0,\"Tem\":30.9,\"Hum\":72.6,\"Bar\":100.8,\"Alt\":45.3,\"RF\":896.9,\"Lux\":28726,\"B\":13.4}";
  char finalDataChar[msg.length() + 1];
  char topicChar[mqttTopic.length() + 1];
  msg.toCharArray(finalDataChar, msg.length() + 1);
  mqttTopic.toCharArray(topicChar, mqttTopic.length() + 1);
  debugE(finalDataChar);  //debug
  mqttType.publish(topicChar, finalDataChar);
}

//Final SendData
void sendData(String msg) {
  switch (connectivityType) {
    case 1:  //sendData using protocol LoRaWAN
      sendData_Lora(msg, " ");
      break;
    case 2:  //sendData using protocol MQTT via GSM
      gsmCheck();
      sendData_Mqtt(msg, mqttGsm);
      break;
    case 3:  //sendData using protocol MQTT via WiFi
      sendData_Mqtt(msg, mqttWifi);
      break;
    case 4:  //sendData using protocol MQTT via Ethernet
      //sdsd
      break;
    case 5:  //sendData using protocol MQTT via Ethernet
      debugE("OFFLINE MODE");
      break;
    default:  //LoRaWAN
      debugE("OFFLINE MODE");
      break;
  }
}