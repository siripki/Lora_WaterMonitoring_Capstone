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
    } else {
      return request->requestAuthentication();
    }
  });

  // execute : Handle post request
  server.on("/execute", HTTP_POST, [](AsyncWebServerRequest* request) {
    if (request->authenticate(http_username.c_str(), http_password.c_str())) {
      if (request->hasParam("xCal", true) || request->hasParam("yCal", true) || request->hasParam("tempCal", true) || request->hasParam("tdsCal", true)) {
        xCal = request->getParam("xCal", true)->value().toFloat();
        yCal = request->getParam("yCal", true)->value().toFloat();
        tempCal = request->getParam("tempCal", true)->value().toFloat();
        tdsCal = request->getParam("tdsCal", true)->value().toFloat();

        writeFile("/xCal.txt", String(xCal).c_str());
        writeFile("/yCal.txt", String(yCal).c_str());
        writeFile("/tempCal.txt", String(tempCal).c_str());
        writeFile("/tdsCal.txt", String(tdsCal).c_str());
      }

      else if (request->hasParam("tempKey", true) || request->hasParam("tdsKey", true) || request->hasParam("wlKey", true)) {
        tempKey = request->getParam("tempKey", true)->value();
        tdsKey = request->getParam("tdsKey", true)->value();
        wlKey = request->getParam("wlKey", true)->value();
     

        writeFile("/tempKey.txt", tempKey.c_str());
        writeFile("/tdsKey.txt", tdsKey.c_str());
        writeFile("/wlKey.txt", wlKey.c_str());
      }

      else if (request->hasParam("connectivityType", true)) {
        connectivityType = (request->getParam("connectivityType", true)->value()).toInt();
        writeFile("/connectivityType.txt", String(connectivityType).c_str());

        devAddr = request->getParam("devAddr", true)->value();
        appSKey = request->getParam("appSKey", true)->value();
        nwkSKey = request->getParam("nwkSKey", true)->value();
        classTx = (request->getParam("class_tx", true)->value()).toInt();
        sfTx = (request->getParam("sf_tx", true)->value()).toInt();
        powerTx = (request->getParam("power_tx", true)->value()).toInt();
        channelTx = (request->getParam("channel_tx", true)->value()).toInt();

        writeFile("/devAddr.txt", devAddr.c_str());
        writeFile("/appSKey.txt", appSKey.c_str());
        writeFile("/nwkSKey.txt", nwkSKey.c_str());
        writeFile("/classTx.txt", String(classTx).c_str());
        writeFile("/sfTx.txt", String(sfTx).c_str());
        writeFile("/powerTx.txt", String(powerTx).c_str());
        writeFile("/channelTx.txt", String(channelTx).c_str());

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

        if (connectivityType == 3) {
          wifiSetup();
        }
      }

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
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  server.addHandler(&events);

  AsyncElegantOTA.begin(&server);
  server.begin();
}

void serverSentEvents() {
  //events.send("ping", NULL, millis());
  events.send(String(temp).c_str(), "temp", millis());
  events.send(String(tdsValue).c_str(), "tdsValue", millis());
  events.send(String(wlValue).c_str(), "wlValue", millis());
  events.send(String(yValue).c_str(), "yValue", millis());
}

String processor(const String& var) {
  if (var == "temp") {
    return String(temp);
  }

  else if (var == "tdsValue") {
    return String(tdsValue);
  }

  else if (var == "wlValue") {
    return String(wlValue);
  }

  else if (var == "yValue") {
    return String(yValue);
  }

  else if (var == "xCal") {
    return String(xCal);
  }

  else if (var == "yCal") {
    return String(yCal);
  }

  else if (var == "tempCal") {
    return String(tempCal);
  }

  else if (var == "tdsCal") {
    return String(tdsCal);
  }

  else if (var == "tempKey") {
    return tempKey;
  }

  else if (var == "tdsKey") {
    return tdsKey;
  }

  else if (var == "wlKey") {
    return wlKey;
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
