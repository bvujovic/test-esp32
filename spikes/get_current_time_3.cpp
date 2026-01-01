/*
NTP TZ DST - bare minimum
NetWork Time Protocol - Time Zone - Daylight Saving Time

Our target for this MINI sketch is:
- get the SNTP request running
- set the timezone
- (implicit) respect daylight saving time
- how to "read" time to be printed to Serial.Monitor

This example is a stripped down version of the NTP-TZ-DST (v2) from the ESP8266
and contains some #precompiler defines to make it working for
- ESP32 core 1.0.5, 1.0.6, 2.0.2  https://werner.rothschopf.net/microcontroller/202103_arduino_esp32_ntp_en.htm
- ESP8266 core 2.7.4, 3.0.2       https://werner.rothschopf.net/202011_arduino_esp8266_ntp_en.htm

by noiasca
2021-03-28 https://werner.rothschopf.net/microcontroller/202103_arduino_esp32_ntp_en.htm
*/

#define SECOND (1000UL)

#include <CredWiFi.h> // WiFi credentials

#define MY_NTP_SERVER "rs.pool.ntp.org"

// https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"
// Europe/Belgrade -> CET-1CEST,M3.5.0,M10.5.0/3

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h> // we need wifi to get internet access
#endif
#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#endif
#include <time.h> // for time() ctime()

/* Globals */
time_t now;   // this are the seconds since Epoch (1970) - UTC
struct tm tm; // the structure tm holds time information in a more convenient way *

void getTime()
{
    time(&now);             // read the current time
    localtime_r(&now, &tm); // update the structure tm with the current time
}

void showTime()
{
    Serial.print(&tm, "%Y-%m-%d");
    Serial.println(&tm, " %H:%M:%S");

    // Serial.print("year:");
    // Serial.print(tm.tm_year + 1900); // years since 1900
    // Serial.print("\tmonth:");
    // Serial.print(tm.tm_mon + 1); // January = 0 (!)
    // Serial.print("\tday:");
    // Serial.print(tm.tm_mday); // day of month
    // Serial.print("\thour:");
    // Serial.print(tm.tm_hour); // hours since midnight 0-23
    // Serial.print("\tmin:");
    // Serial.print(tm.tm_min); // minutes after the hour 0-59
    // Serial.print("\tsec:");
    // Serial.print(tm.tm_sec); // seconds after the minute 0-61*
    // Serial.print("\twday");
    // Serial.print(tm.tm_wday); // days since Sunday 0-6
    // if (tm.tm_isdst == 1)     // Daylight Saving Time flag
    //     Serial.print("\tDST");
    // else
    //     Serial.print("\tstandard");
    // Serial.println();
}

#include "esp_sntp.h"

ulong msLastTimeSync = 0;
// callback function to show when NTP was synchronized
void cbSyncTime(struct timeval *tv)
{
    Serial.println(F(" *** NTP time synched! *** "));
    msLastTimeSync = millis();
    // Serial.println(msLastTimeSync);
}

#include <CredWiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h> // lib_deps = esphome/ESPAsyncWebServer-esphome @ ^3.3.0
AsyncWebServer server(80);

char line[30];
const byte lastIpNumber = 88; // last byte of IP address for static IP assignment
void wifiConfig(bool isStaticIP)
{
    if (isStaticIP)
    {
        IPAddress ipa(192, 168, 0, lastIpNumber);
        IPAddress gateway(192, 168, 0, 254);
        IPAddress subnet(255, 255, 255, 0);
        WiFi.config(ipa, gateway, subnet);
    }
    else
        WiFi.config(IPAddress(), IPAddress(), IPAddress());
}

void startWebServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello, this is a minimal NTP TZ DST example!"); });

    server.on("/time", HTTP_GET, [](AsyncWebServerRequest *request)
              {                  
        getLocalTime(&tm);
        strftime(line, sizeof(line), "%Y-%m-%d %H:%M:%S\n", &tm);
                  request->send(200, "text/plain", line); });

    // server.on("/time", HTTP_GET, [](AsyncWebServerRequest *request)
    //           {
    //               getTime();
    //               String timeString = String();
    //               timeString += String(tm.tm_year + 1900) + "-";
    //               timeString += String(tm.tm_mon + 1) + "-";
    //               timeString += String(tm.tm_mday) + " ";
    //               timeString += String(tm.tm_hour) + ":";
    //               timeString += String(tm.tm_min) + ":";
    //               timeString += String(tm.tm_sec);
    //               request->send(200, "text/plain", timeString); });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *req)
              {
                  req->send(200, "text/plain", "Reset started");
                  //   wifiConfig(false);
                  //   Serial.println(WiFi.localIP());

                //   Serial.println("getTime");
                //   server.end();
                //   delay(1000);
                //   wifiConfig(false);
                //   delay(1000);
                //   isTimeSet = false;
                //   msLastGetTime = 0;
                //   Serial.println(WiFi.localIP()[3]);
                //   configTime(3600, 0, "rs.pool.ntp.org");

                  //   wifiConfig(true);

                    ESP.restart(); });

    server.begin();
}

void setup()
{
    Serial.begin(115200);
    Serial.println("\nNTP TZ DST - bare minimum");

    // start network
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    // sntp_set_sync_interval(1 * 60 * SECOND); // sync every minute
    sntp_set_sync_interval(7 * 24 * 60 * 60 * SECOND); // sync every week
    sntp_set_time_sync_notification_cb(cbSyncTime);
#ifdef ARDUINO_ARCH_ESP32
    configTime(0, 0, MY_NTP_SERVER); // 0, 0 because we will use TZ in the next line
    setenv("TZ", MY_TZ, 1);          // Set environment variable with your time zone
    tzset();
#else
    // ESP8266
    configTime(MY_TZ, MY_NTP_SERVER); // --> for the ESP8266 only
#endif

    Serial.println("Waiting for NTP time sync:");
    // while (tm.tm_year < (2024 - 1900))
    // {
    //     Serial.print(".");
    //     delay(SECOND);
    //     getTime();
    // }
    // 

    // TODO wait for msLastTimeSync to be set in cbSyncTime, not fixed 20 times with delay
    while (msLastTimeSync == 0)
    {
        delay(200);
    }
    // for (size_t i = 0; i < 20; i++)
    // {
    //     Serial.println(msLastTimeSync);
    //     delay(500);
    // }
    Serial.println("Time synchronized!");
    Serial.println(msLastTimeSync);

    wifiConfig(true);
    startWebServer();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

ulong msLastShowTime = 0;
int secLastShow = -1;

void loop()
{
    // if (millis() > msLastShowTime + 5 * SECOND)
    // {
    //     getTime();
    //     showTime();
    //     msLastShowTime = millis();
    // }
    delay(100);
}
