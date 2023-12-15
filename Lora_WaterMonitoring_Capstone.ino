#define debugMode 1 //debugMode 1 enable common print serial, 0 only print error
#if debugMode == 1
#define debugP(x) Serial.println(x) //printSerial
#define debugE(y) Serial.println(y) //printError
#else
#define debugP(x)
#define debugE(y) Serial.println(y)
#endif

byte guiButton = 13;
byte ledPin = 14;

//Ultrasonic Parameter
byte trigPin = 32;
byte echoPin = 33;

//DallasTemp Parameter
#include <OneWire.h>
#include <DallasTemperature.h>
#define dallasPin 25
OneWire oneWire(dallasPin);
DallasTemperature dallas(&oneWire);

//ADS Parameter
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

//Lora Parameter
#include <lorawan.h>
const sRFM_pins RFM_pins = {
  .CS = 5,
  .RST = 4,
  .DIO0 = 26,
  .DIO1 = 27,
};

//WebServer and WiFi Parameter
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
DNSServer dnsServer;
AsyncWebServer server(80);           //GUI server
AsyncEventSource events("/events");  // Create an SSE Event Source on /events
WiFiClient wifiClient;               //ini objek untuk mqtt client

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}
  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }
  void handleRequest(AsyncWebServerRequest *request) {
    request->redirect("http://192.168.4.1/");
  }
};

//GSM Parameter
#define TINY_GSM_MODEM_SIM800
#include <SoftwareSerial.h>
#include <TinyGsmClient.h>
SoftwareSerial sim800(16, 17);  //define sim800 serial pin RxTx : TsimRsim
TinyGsm modem(sim800);
TinyGsmClient gsmClient(modem);

//MQTT Parameter
#include <PubSubClient.h>
PubSubClient mqttWifi(wifiClient);
PubSubClient mqttGsm(gsmClient);

//SPIFFS
#include "SPIFFS.h"
#include "FS.h"

//MAF 
#include "MovingAverage.h"
MovingAverage mafWL(4);
MovingAverage mafTemp(4);
MovingAverage mafTds(4);

//Global Variabel
bool guiMode = false;
bool guiState = false;
String http_username;
String http_password;
String apSsid;
String apPass;
String sn;
String version;
String board;
String type_board;
String maintainerName;

int connectivityType;
String devAddr;
String appSKey;
String nwkSKey;
int classTx;
int sfTx;
int powerTx;
int channelTx;

String apnName;
String apnUser;
String apnPass;

String wifiIpMode;
String wifiSsid;
String wifiPass;
String wifiLocalIP;
String wifiGateway;
String wifiSubnet;
String wifiDNS;

String mqttBroker;
String mqttPort;
String mqttID;
String mqttTopic;
String mqttUser;
String mqttPass;
String broker;

uint8_t uplinkInterval;

float temp;
float tdsValue;
float wlValue;
float yValue;

float xCal;
float yCal;
float tempCal;
float tdsCal;

String tempKey;
String tdsKey;
String wlKey;


void setup() {
  Serial.begin(115200);
  spiffSetup();
  readSettings();
  sensorSetup();
  pinMode(ledPin, OUTPUT);
  pinMode(guiButton, INPUT_PULLUP);
  if (digitalRead(guiButton) == LOW || guiState == true) {
    if (guiState == true){
      writeFile("/guiState.txt", "0"); //switch it to false for next reading
    }
    debugE("Entering AP Mode...");
    guiMode = true;
    guiHandling();
  }
  connectivitySetup();
  normalMode();
  goToSleep();
}

void loop() {
}
