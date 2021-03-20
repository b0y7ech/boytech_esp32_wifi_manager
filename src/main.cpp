#include <Arduino.h>
#include <PcProtocol.h>
#include "sys\time.h"
#include "common.h"
#include <vector>
#include <SPI.h>
#include <CMD.h>
#include <EEPROM.h>

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#ifndef LED_BUILTIN
  #define LED_BUILTIN 2
#endif

int g_ledValue = 0;

//Wifi Manager - WIFI ssid and password
const char* ssid = "Goky T1";
const char* password = "xincamon";

String esid;
String epass = "";

//Wifi Manager - Function Decalration
bool testWifi(void);
void setupAP(void);

PcProtocol g_pcProtocol;

void printLocalTime()
{ 
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void OnSettime(uint32_t epoch)
{
    TRACE("Settime: %d\n", epoch);
    struct timeval tv;
    tv.tv_sec = epoch;  // epoch time (seconds)
    tv.tv_usec = 0;    // microseconds
    settimeofday(&tv, NULL);
    printLocalTime();
    // g_pcProtocol.replyCommand(CMD::SETTIME);
}

void OnRequestScan()
{
    TRACE("Scanning...\n");
    // g_pcProtocol.replyCommand(CMD::WIFI_SCAN, vector<>);
}


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  TRACE("Init...\n");
  pinMode(LED_BUILTIN, OUTPUT);

  g_pcProtocol.setOnSetTimeHandler(&OnSettime);
  g_pcProtocol.setOnRequestScan(&OnRequestScan);
  
  //Initialasing EEPROM
  EEPROM.begin(512); 
  delay(10);
  Serial.println("Startup");
  WiFi.begin(ssid, password);

  // Read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM Wifi password");
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
  WiFi.begin(esid.c_str(), epass.c_str());

  Serial.println("Setup done");

}

void loop() 
{
  // put your main code here, to run repeatedly:
  for (;;) // A Task shall never return or exit.
  {
    while (Serial.available())
    {
      if ((WiFi.status() == WL_CONNECTED))
      {
        for (int i = 0; i < 10; i++)
        {
          Serial.print("Connected to ");
          Serial.print(esid);
          Serial.println(" Successfully");
          delay(100);
        }
      }
    if(testWifi() == true)
    {
      setupAP();
    }
      g_pcProtocol.setChar(char(Serial.read()));
      // g_pcProtocol.replyCommand();
    }
    vTaskDelay(100);  
  }
}

bool testWifi(void)
{
  int checkWifi = 0;
  //Serial.println("Waiting for Wifi to connect");
  while ( checkWifi < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    checkWifi++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  delay(100);
  WiFi.softAP("ElectronicsInnovation", "");
}