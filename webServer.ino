void serverSetup() {
  // Serve Static File on Assets
  server.serveStatic("/assets/", SPIFFS, "/assets/");

  // Default Handler 404
  server.onNotFound([](AsyncWebServerRequest* request) {
    request->redirect("/assets/index.htm");
  });

  // Handle User Authentication
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->authenticate(http_username.c_str(), http_password.c_str())) {
      request->send(SPIFFS, "/index.html", String(), false, processor);
    } else if (request->authenticate("user", "user")) {
      request->send(SPIFFS, "/index2.html", String(), false, processor);
    } else {
      return request->requestAuthentication();
    }
  });

  // execute : Handle post request
  server.on("/execute", HTTP_POST, [](AsyncWebServerRequest* request) {
    if (request->authenticate(http_username.c_str(), http_password.c_str()) || request->authenticate("user", "user")) {
      if (request->hasParam("status_Relay1", true)) {
        statusRelay1 = request->getParam("status_Relay1", true)->value().toInt();
        timeTask1R1Hour = decodeTime(request->getParam("timeTask1R1", true)->value(), 'H');
        timeTask1R1Minute = decodeTime(request->getParam("timeTask1R1", true)->value(), 'M');
        durationTask1R1 = request->getParam("durationTask1R1", true)->value().toInt();
        timeTask2R1Hour = decodeTime(request->getParam("timeTask2R1", true)->value(), 'H');
        timeTask2R1Minute = decodeTime(request->getParam("timeTask2R1", true)->value(), 'M');
        durationTask2R1 = request->getParam("durationTask2R1", true)->value().toInt();
        timeTask3R1Hour = decodeTime(request->getParam("timeTask3R1", true)->value(), 'H');
        timeTask3R1Minute = decodeTime(request->getParam("timeTask3R1", true)->value(), 'M');
        durationTask3R1 = request->getParam("durationTask3R1", true)->value().toInt();
        timeTask4R1Hour = decodeTime(request->getParam("timeTask4R1", true)->value(), 'H');
        timeTask4R1Minute = decodeTime(request->getParam("timeTask4R1", true)->value(), 'M');
        durationTask4R1 = request->getParam("durationTask4R1", true)->value().toInt();
        tempThresR1 = request->getParam("tempThresR1", true)->value().toFloat();
        humiThresR1 = request->getParam("humiThresR1", true)->value().toFloat();
        durationSchR1 = request->getParam("durationSchR1", true)->value().toInt();
        intervalSchR1 = request->getParam("intervalSchR1", true)->value().toInt();
        statusSch1R1 = request->getParam("status_Sch1R1", true)->value().toInt();
        startSch1R1Hour = decodeTime(request->getParam("startSch1R1", true)->value(), 'H');
        startSch1R1Minute = decodeTime(request->getParam("startSch1R1", true)->value(), 'M');
        stopSch1R1Hour = decodeTime(request->getParam("stopSch1R1", true)->value(), 'H');
        stopSch1R1Minute = decodeTime(request->getParam("stopSch1R1", true)->value(), 'M');
        statusSch2R1 = request->getParam("status_Sch2R1", true)->value().toInt();
        startSch2R1Hour = decodeTime(request->getParam("startSch2R1", true)->value(), 'H');
        startSch2R1Minute = decodeTime(request->getParam("startSch2R1", true)->value(), 'M');
        stopSch2R1Hour = decodeTime(request->getParam("stopSch2R1", true)->value(), 'H');
        stopSch2R1Minute = decodeTime(request->getParam("stopSch2R1", true)->value(), 'M');

        writeFile("/statusRelay1.txt", String(statusRelay1).c_str());
        writeFile("/timeTask1R1Hour.txt", String(timeTask1R1Hour).c_str());
        writeFile("/timeTask1R1Minute.txt", String(timeTask1R1Minute).c_str());
        writeFile("/durationTask1R1.txt", String(durationTask1R1).c_str());
        writeFile("/timeTask2R1Hour.txt", String(timeTask2R1Hour).c_str());
        writeFile("/timeTask2R1Minute.txt", String(timeTask2R1Minute).c_str());
        writeFile("/durationTask2R1.txt", String(durationTask2R1).c_str());
        writeFile("/timeTask3R1Hour.txt", String(timeTask3R1Hour).c_str());
        writeFile("/timeTask3R1Minute.txt", String(timeTask3R1Minute).c_str());
        writeFile("/durationTask3R1.txt", String(durationTask3R1).c_str());
        writeFile("/timeTask4R1Hour.txt", String(timeTask4R1Hour).c_str());
        writeFile("/timeTask4R1Minute.txt", String(timeTask4R1Minute).c_str());
        writeFile("/durationTask4R1.txt", String(durationTask4R1).c_str());
        writeFile("/tempThresR1.txt", String(tempThresR1).c_str());
        writeFile("/humiThresR1.txt", String(humiThresR1).c_str());
        writeFile("/durationSchR1.txt", String(durationSchR1).c_str());
        writeFile("/intervalSchR1.txt", String(intervalSchR1).c_str());
        writeFile("/statusSch1R1.txt", String(statusSch1R1).c_str());
        writeFile("/startSch1R1Hour.txt", String(startSch1R1Hour).c_str());
        writeFile("/startSch1R1Minute.txt", String(startSch1R1Minute).c_str());
        writeFile("/stopSch1R1Hour.txt", String(stopSch1R1Hour).c_str());
        writeFile("/stopSch1R1Minute.txt", String(stopSch1R1Minute).c_str());
        writeFile("/statusSch2R1.txt", String(statusSch2R1).c_str());
        writeFile("/startSch2R1Hour.txt", String(startSch2R1Hour).c_str());
        writeFile("/startSch2R1Minute.txt", String(startSch2R1Minute).c_str());
        writeFile("/stopSch2R1Hour.txt", String(stopSch2R1Hour).c_str());
        writeFile("/stopSch2R1Minute.txt", String(stopSch2R1Minute).c_str());

        // Serial.println(timeTask1R1Hour);
        // Serial.println(timeTask1R1Minute);
        
      }

      else if (request->hasParam("status_Relay2", true)) {
        statusRelay2 = request->getParam("status_Relay2", true)->value().toInt();
        timeTask1R2Hour = decodeTime(request->getParam("timeTask1R2", true)->value(), 'H');
        timeTask1R2Minute = decodeTime(request->getParam("timeTask1R2", true)->value(), 'M');
        durationTask1R2 = request->getParam("durationTask1R2", true)->value().toInt();
        timeTask2R2Hour = decodeTime(request->getParam("timeTask2R2", true)->value(), 'H');
        timeTask2R2Minute = decodeTime(request->getParam("timeTask2R2", true)->value(), 'M');
        durationTask2R2 = request->getParam("durationTask2R2", true)->value().toInt();
        timeTask3R2Hour = decodeTime(request->getParam("timeTask3R2", true)->value(), 'H');
        timeTask3R2Minute = decodeTime(request->getParam("timeTask3R2", true)->value(), 'M');
        durationTask3R2 = request->getParam("durationTask3R2", true)->value().toInt();
        timeTask4R2Hour = decodeTime(request->getParam("timeTask4R2", true)->value(), 'H');
        timeTask4R2Minute = decodeTime(request->getParam("timeTask4R2", true)->value(), 'M');
        durationTask4R2 = request->getParam("durationTask4R2", true)->value().toInt();
        tempThresR2 = request->getParam("tempThresR2", true)->value().toFloat();
        humiThresR2 = request->getParam("humiThresR2", true)->value().toFloat();
        durationSchR2 = request->getParam("durationSchR2", true)->value().toInt();
        intervalSchR2 = request->getParam("intervalSchR2", true)->value().toInt();
        statusSch1R2 = request->getParam("status_Sch1R2", true)->value().toInt();
        startSch1R2Hour = decodeTime(request->getParam("startSch1R2", true)->value(), 'H');
        startSch1R2Minute = decodeTime(request->getParam("startSch1R2", true)->value(), 'M');
        stopSch1R2Hour = decodeTime(request->getParam("stopSch1R2", true)->value(), 'H');
        stopSch1R2Minute = decodeTime(request->getParam("stopSch1R2", true)->value(), 'M');
        statusSch2R2 = request->getParam("status_Sch2R2", true)->value().toInt();
        startSch2R2Hour = decodeTime(request->getParam("startSch2R2", true)->value(), 'H');
        startSch2R2Minute = decodeTime(request->getParam("startSch2R2", true)->value(), 'M');
        stopSch2R2Hour = decodeTime(request->getParam("stopSch2R2", true)->value(), 'H');
        stopSch2R2Minute = decodeTime(request->getParam("stopSch2R2", true)->value(), 'M');

        writeFile("/statusRelay2.txt", String(statusRelay2).c_str());
        writeFile("/timeTask1R2Hour.txt", String(timeTask1R2Hour).c_str());
        writeFile("/timeTask1R2Minute.txt", String(timeTask1R2Minute).c_str());
        writeFile("/durationTask1R2.txt", String(durationTask1R2).c_str());
        writeFile("/timeTask2R2Hour.txt", String(timeTask2R2Hour).c_str());
        writeFile("/timeTask2R2Minute.txt", String(timeTask2R2Minute).c_str());
        writeFile("/durationTask2R2.txt", String(durationTask2R2).c_str());
        writeFile("/timeTask3R2Hour.txt", String(timeTask3R2Hour).c_str());
        writeFile("/timeTask3R2Minute.txt", String(timeTask3R2Minute).c_str());
        writeFile("/durationTask3R2.txt", String(durationTask3R2).c_str());
        writeFile("/timeTask4R2Hour.txt", String(timeTask4R2Hour).c_str());
        writeFile("/timeTask4R2Minute.txt", String(timeTask4R2Minute).c_str());
        writeFile("/durationTask4R2.txt", String(durationTask4R2).c_str());
        writeFile("/tempThresR2.txt", String(tempThresR2).c_str());
        writeFile("/humiThresR2.txt", String(humiThresR2).c_str());
        writeFile("/durationSchR2.txt", String(durationSchR2).c_str());
        writeFile("/intervalSchR2.txt", String(intervalSchR2).c_str());
        writeFile("/statusSch1R2.txt", String(statusSch1R2).c_str());
        writeFile("/startSch1R2Hour.txt", String(startSch1R2Hour).c_str());
        writeFile("/startSch1R2Minute.txt", String(startSch1R2Minute).c_str());
        writeFile("/stopSch1R2Hour.txt", String(stopSch1R2Hour).c_str());
        writeFile("/stopSch1R2Minute.txt", String(stopSch1R2Minute).c_str());
        writeFile("/statusSch2R2.txt", String(statusSch2R2).c_str());
        writeFile("/startSch2R2Hour.txt", String(startSch2R2Hour).c_str());
        writeFile("/startSch2R2Minute.txt", String(startSch2R2Minute).c_str());
        writeFile("/stopSch2R2Hour.txt", String(stopSch2R2Hour).c_str());
        writeFile("/stopSch2R2Minute.txt", String(stopSch2R2Minute).c_str());
      }

      else if (request->hasParam("dateCal", true) || request->hasParam("timeCal", true)) {
        dateCal = request->getParam("dateCal", true)->value();
        timeCal = request->getParam("timeCal", true)->value();
        writeFile("/dateCal.txt", dateCal.c_str());
        writeFile("/timeCal.txt", timeCal.c_str());
        setTimeNow();
        getTimeNow();
        // events.send(String(String(day) + "/" + String(month) + "/" + String(year)).c_str(), "dateNow", millis());
        // events.send(String(String(hour) + ":" + String(minute)).c_str(), "timeNow", millis());
      }

      else if (request->hasParam("tempCal", true) || request->hasParam("humiCal", true)) {
        tempCal = request->getParam("tempCal", true)->value().toFloat();
        humiCal = request->getParam("humiCal", true)->value().toFloat();
        writeFile("/tempCal.txt", String(tempCal).c_str());
        writeFile("/humiCal.txt", String(humiCal).c_str());
      }

      else if (request->hasParam("tempKey", true) || request->hasParam("humiKey", true)) {
        tempKey = request->getParam("tempKey", true)->value();
        humiKey = request->getParam("humiKey", true)->value();
        writeFile("/tempKey.txt", tempKey.c_str());
        writeFile("/humiKey.txt", humiKey.c_str());
      }

      else if (request->hasParam("connectivityType", true)) {
        connectivityType = (request->getParam("connectivityType", true)->value()).toInt();
        writeFile("/connectivityType.txt", String(connectivityType).c_str());

        // devAddr = request->getParam("devAddr", true)->value();
        // appSKey = request->getParam("appSKey", true)->value();
        // nwkSKey = request->getParam("nwkSKey", true)->value();
        // classTx = (request->getParam("class_tx", true)->value()).toInt();
        // sfTx = (request->getParam("sf_tx", true)->value()).toInt();
        // powerTx = (request->getParam("power_tx", true)->value()).toInt();
        // channelTx = (request->getParam("channel_tx", true)->value()).toInt();

        // writeFile("/devAddr.txt", devAddr.c_str());
        // writeFile("/appSKey.txt", appSKey.c_str());
        // writeFile("/nwkSKey.txt", nwkSKey.c_str());
        // writeFile("/classTx.txt", String(classTx).c_str());
        // writeFile("/sfTx.txt", String(sfTx).c_str());
        // writeFile("/powerTx.txt", String(powerTx).c_str());
        // writeFile("/channelTx.txt", String(channelTx).c_str());

        apnName = request->getParam("apnName", true)->value();
        apnUser = request->getParam("apnUser", true)->value();
        apnPass = request->getParam("apnPass", true)->value();

        writeFile("/apnName.txt", apnName.c_str());
        writeFile("/apnUser.txt", apnUser.c_str());
        writeFile("/apnPass.txt", apnPass.c_str());

        wifiSsid = request->getParam("wifiSsid", true)->value();
        wifiPass = request->getParam("wifiPass", true)->value();
        wifiIpMode = request->getParam("wifiIpMode", true)->value();
        wifiLocalIP = request->getParam("wifiLocalIP", true)->value();
        wifiSubnet = request->getParam("wifiSubnet", true)->value();
        wifiGateway = request->getParam("wifiGateway", true)->value();
        wifiDNS = request->getParam("wifiDNS", true)->value();

        writeFile("/wifiSsid.txt", wifiSsid.c_str());
        writeFile("/wifiPass.txt", wifiPass.c_str());
        writeFile("/wifiIpMode.txt", wifiIpMode.c_str());
        writeFile("/wifiLocalIP.txt", wifiLocalIP.c_str());
        writeFile("/wifiSubnet.txt", wifiSubnet.c_str());
        writeFile("/wifiGateway.txt", wifiGateway.c_str());
        writeFile("/wifiDNS.txt", wifiDNS.c_str());

        mqttBroker = request->getParam("broker_custom_broker", true)->value();
        mqttPort = request->getParam("port_custom_broker", true)->value();
        mqttTopic = request->getParam("topic_custom_publish", true)->value();
        mqttUser = request->getParam("user_custom_broker", true)->value();
        mqttPass = request->getParam("pass_custom_broker", true)->value();
        mqttID = request->getParam("id_custom_broker", true)->value();

        writeFile("/mqttBroker.txt", mqttBroker.c_str());
        writeFile("/mqttPort.txt", mqttPort.c_str());
        writeFile("/mqttTopic.txt", mqttTopic.c_str());
        writeFile("/mqttUser.txt", mqttUser.c_str());
        writeFile("/mqttPass.txt", mqttPass.c_str());
        writeFile("/mqttID.txt", mqttID.c_str());

        // Serial.println("conntype "+String(connectivityType));
        // Serial.println("Iptype "+wifiIpMode);
        if (connectivityType == 3) {
          // writeFile("/guiState.txt", "1");
          // ESP.restart();
          wifiSetup();
        }
      }

      // else if (request->hasParam("apnName", true) or request->hasParam("apnUser", true) or request->hasParam("apnPass", true)) {
      //   apnName = request->getParam("apnName", true)->value();
      //   apnUser = request->getParam("apnUser", true)->value();
      //   apnPass = request->getParam("apnPass", true)->value();

      //   writeFile("/apnName.txt", apnName.c_str());
      //   writeFile("/apnUser.txt", apnUser.c_str());
      //   writeFile("/apnPass.txt", apnPass.c_str());

      // }

      else if (request->hasParam("uplinkInterval", true)) {
        uplinkInterval = (request->getParam("uplinkInterval", true)->value()).toInt();
        writeFile("/uplinkInterval.txt", String(uplinkInterval).c_str());
      }

      else if (request->hasParam("apSsid", true) and request->hasParam("apPass", true)) {
        apSsid = request->getParam("apSsid", true)->value();
        apPass = request->getParam("apPass", true)->value();

        writeFile("/apSsid.txt", apSsid.c_str());
        writeFile("/apSsid.txt", apSsid.c_str());

      }

      else if (request->hasParam("http_username", true) and request->hasParam("http_password", true)) {
        http_username = request->getParam("http_username", true)->value();
        http_password = request->getParam("http_password", true)->value();

        writeFile("/http_username.txt", http_username.c_str());
        writeFile("/http_password.txt", http_password.c_str());
      }


      delay(50);
      //readSettings();
      request->redirect("/");
      Serial.println("Execute OK!");
    } else {
      delay(50);
      request->send(200, "text/plain", "You don't have permission!");
      Serial.println("Execute ERROR First!");
    }
  });

  // Restart Device Process
  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", "Success Restart!");
    ESP.restart();
  });
  server.on("/restartGUI", HTTP_GET, [](AsyncWebServerRequest* request) {
    writeFile("/guiState.txt", "1");
    request->send(200, "text/plain", "Success Restart!");
    ESP.restart();
  });

  // Reset Device data
  server.on("/reset_default", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    dataDefault();
    request->send(200, "text/plain", "Success Reset!");
    ESP.restart();
  });

  // Logout Page With Authentication
  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", "Success Logout!");
  });

  // Logout Without Authentication Process
  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(401);
  });

  server.on("/egrotek-logo", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/egrotek.png", "image/png");
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient* client) {
    if (client->lastId()) {
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  AsyncElegantOTA.begin(&server);
  server.begin();
}

void serverSentEvents() {
  //events.send("ping", NULL, millis());
  events.send(String(temp).c_str(), "temp", millis());
  events.send(String(String(day) + "/" + String(month) + "/" + String(year)).c_str(), "dateNow", millis());
  events.send(codeTime(hour, minute).c_str(), "timeNow", millis());
  events.send(String(humi).c_str(), "humi", millis());
  if (WiFi.status() == WL_CONNECTED) {
    events.send(wifiSsid.c_str(), "ssid_wifi_connected", millis());
    events.send(WiFi.localIP().toString().c_str(), "ip_local_client", millis());
    events.send(String(WiFi.RSSI()).c_str(), "rssi_wifi", millis());
    events.send(String(WiFi.macAddress()).c_str(), "mac_wifi", millis());
  }
}

String processor(const String& var) {
  String hourStr;
  String minuteStr;
  if (var == "temp") {
    return String(temp);
  }

  else if (var == "dateNow") {
    return String(day) + "/" + String(month) + "/" + String(year);
  }

  else if (var == "timeNow") {
    return codeTime(hour, minute);
  }

  else if (var == "humi") {
    return String(humi);
  }

  else if (var == "status_Relay1") {
    return String(statusRelay1);
  }

  else if (var == "tempThresR1") {
    return String(tempThresR1);
  }

  else if (var == "humiThresR1") {
    return String(humiThresR1);
  }

  else if (var == "timeTask1R1") {
    // return String(timeTask1R1Hour) + ":" + String(timeTask1R1Minute);
    return codeTime(timeTask1R1Hour, timeTask1R1Minute);
  }

  else if (var == "durationTask1R1") {
    return String(durationTask1R1);
  }

  else if (var == "timeTask2R1") {
    // return String(timeTask2R1Hour) + ":" + String(timeTask2R1Minute);
    return codeTime(timeTask2R1Hour, timeTask2R1Minute);
  }

  else if (var == "durationTask2R1") {
    return String(durationTask2R1);
  }

  else if (var == "timeTask3R1") {
    // return String(timeTask3R1Hour) + ":" + String(timeTask3R1Minute);
    return codeTime(timeTask3R1Hour, timeTask3R1Minute);
  }

  else if (var == "durationTask3R1") {
    return String(durationTask3R1);
  }

  else if (var == "timeTask4R1") {
    // return String(timeTask4R1Hour) + ":" + String(timeTask4R1Minute);
    return codeTime(timeTask4R1Hour, timeTask4R1Minute);
  }

  else if (var == "durationTask4R1") {
    return String(durationTask4R1);
  }

  else if (var == "durationSchR1") {
    return String(durationSchR1);
  }

  else if (var == "intervalSchR1") {
    return String(intervalSchR1);
  }

  else if (var == "status_Sch1R1") {
    return String(statusSch1R1);
  }

  else if (var == "startSch1R1") {
    // return String(startSch1R1Hour) + ":" + String(startSch1R1Minute);
    return codeTime(startSch1R1Hour, startSch1R1Minute);
  }

  else if (var == "stopSch1R1") {
    // return String(stopSch1R1Hour) + ":" + String(stopSch1R1Minute);
    return codeTime(stopSch1R1Hour, stopSch1R1Minute);
  }

  else if (var == "status_Sch2R1") {
    return String(statusSch2R1);
  }

  else if (var == "startSch2R1") {
    // return String(startSch2R1Hour) + ":" + String(startSch2R1Minute);
    return codeTime(startSch2R1Hour, startSch2R1Minute);
  }

  else if (var == "stopSch2R1") {
    // return String(stopSch2R1Hour) + ":" + String(stopSch2R1Minute);
    return codeTime(stopSch2R1Hour, stopSch2R1Minute);
  }

  else if (var == "status_Relay2") {
    return String(statusRelay2);
  }

  else if (var == "tempThresR2") {
    return String(tempThresR2);
  }

  else if (var == "humiThresR2") {
    return String(humiThresR2);
  }

  else if (var == "timeTask1R2") {
    // return String(timeTask1R2Hour) + ":" + String(timeTask1R2Minute);
    return codeTime(timeTask1R2Hour, timeTask1R2Minute);
  }

  else if (var == "durationTask1R2") {
    return String(durationTask1R2);
  }

  else if (var == "timeTask2R2") {
    // return String(timeTask2R2Hour) + ":" + String(timeTask2R2Minute);
    return codeTime(timeTask2R2Hour, timeTask2R2Minute);
  }

  else if (var == "durationTask2R2") {
    return String(durationTask2R2);
  }

  else if (var == "timeTask3R2") {
    // return String(timeTask3R2Hour) + ":" + String(timeTask3R2Minute);
    return codeTime(timeTask3R2Hour, timeTask3R2Minute);
  }

  else if (var == "durationTask3R2") {
    return String(durationTask3R2);
  }

  else if (var == "timeTask4R2") {
    // return String(timeTask4R2Hour) + ":" + String(timeTask4R2Minute);
    return codeTime(timeTask4R2Hour, timeTask4R2Minute);
  }

  else if (var == "durationTask4R2") {
    return String(durationTask4R2);
  }

  else if (var == "durationSchR2") {
    return String(durationSchR2);
  }

  else if (var == "intervalSchR2") {
    return String(intervalSchR2);
  }

  else if (var == "status_Sch1R2") {
    return String(statusSch1R2);
  }

  else if (var == "startSch1R2") {
    // return String(startSch1R2Hour) + ":" + String(startSch1R2Minute);
    return codeTime(startSch1R2Hour, startSch1R2Minute);
  }

  else if (var == "stopSch1R2") {
    // return String(stopSch1R2Hour) + ":" + String(stopSch1R2Minute);
    return codeTime(stopSch1R2Hour, stopSch1R2Minute);
  }

  else if (var == "status_Sch2R2") {
    return String(statusSch2R2);
  }

  else if (var == "startSch2R2") {
    // return String(startSch2R2Hour) + ":" + String(startSch2R2Minute);
    return codeTime(startSch2R2Hour, startSch2R2Minute);
  }

  else if (var == "stopSch2R2") {
    // return String(stopSch2R2Hour) + ":" + String(stopSch2R2Minute);
    return codeTime(stopSch2R2Hour, stopSch2R2Minute);
  }

  else if (var == "dateCal") {
    return dateCal;
  }

  else if (var == "timeCal") {
    return timeCal;
  }

  else if (var == "tempCal") {
    return String(tempCal);
  }

  else if (var == "humiCal") {
    return String(humiCal);
  }

  else if (var == "tempKey") {
    return tempKey;
  }

  else if (var == "humiKey") {
    return humiKey;
  }

  else if (var == "connectivityType") {
    return String(connectivityType);
  }

  else if (var == "devAddr") {
    return devAddr;
  }

  else if (var == "appSKey") {
    return appSKey;
  }

  else if (var == "nwkSKey") {
    return nwkSKey;
  }

  else if (var == "class_tx") {
    return String(classTx);
  }

  else if (var == "sf_tx") {
    return String(sfTx);
  }

  else if (var == "power_tx") {
    return String(powerTx);
  }

  else if (var == "channel_tx") {
    return String(channelTx);
  }

  else if (var == "apnName") {
    return apnName;
  }

  else if (var == "apnUser") {
    return apnUser;
  }

  else if (var == "apnPass") {
    return apnPass;
  }

  else if (var == "ip_local_client") {
    if (WiFi.status() != WL_CONNECTED) {
      return "--";
    } else {
      return WiFi.localIP().toString();
    }
  }

  else if (var == "ssid_wifi_connected") {
    if (WiFi.status() != WL_CONNECTED) {
      return "--";
    } else {
      return wifiSsid;
    }
  }

  else if (var == "rssi_wifi") {
    if (WiFi.status() != WL_CONNECTED) {
      return "--";
    } else {
      return String(WiFi.RSSI());
    }
  }

  else if (var == "mac_wifi") {
    if (WiFi.status() != WL_CONNECTED) {
      return "--";
    } else {
      return String(WiFi.macAddress());
    }
  }

  else if (var == "wifiSsid") {
    return wifiSsid;
  }

  else if (var == "wifiPass") {
    return wifiPass;
  }

  else if (var == "wifiIpMode") {
    return wifiIpMode;
  }

  else if (var == "wifiLocalIP") {
    return wifiLocalIP;
  }

  else if (var == "wifiSubnet") {
    return wifiSubnet;
  }

  else if (var == "wifiGateway") {
    return wifiGateway;
  }

  else if (var == "wifiDNS") {
    return wifiDNS;
  }

  else if (var == "broker_custom_broker") {
    return mqttBroker;
  }

  else if (var == "port_custom_broker") {
    return mqttPort;
  }

  else if (var == "topic_custom_publish") {
    return mqttTopic;
  }

  else if (var == "user_custom_broker") {
    return mqttUser;
  }

  else if (var == "pass_custom_broker") {
    return mqttPass;
  }

  else if (var == "id_custom_broker") {
    return mqttID;
  }

  else if (var == "broker") {
    return broker;
  }

  else if (var == "uplinkInterval") {
    return String(uplinkInterval);
  }

  else if (var == "http_username") {
    return http_username;
  }

  else if (var == "http_password") {
    return http_password;
  }

  else if (var == "sn") {
    return sn;
  }

  else if (var == "version") {
    return version;
  }

  else if (var == "board") {
    return board;
  }

  else if (var == "type_board") {
    return type_board;
  }

  else if (var == "maintainerName") {
    return maintainerName;
  }

  else if (var == "apSsid") {
    return apSsid;
  }

  else if (var == "apPass") {
    return apPass;
  }

  else {
    return String();
  }
}
