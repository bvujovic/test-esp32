/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-date-time-ntp-client-server-arduino/
*/

#include <WiFi.h>
#include "time.h"
#include "CredWiFi.h"

void printLocalTime();

void setup()
{
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");

    // Init and get the time
    configTime(3600, 3600, "rs.pool.ntp.org");
    printLocalTime();
    WiFi.disconnect(true);
    // WiFi.mode(WIFI_OFF);
}

void loop()
{
    delay(1000);
    printLocalTime();
}

char fileName[15];

void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    // strftime(fileName, sizeof(fileName), "%Y_%m_%d", &timeinfo);
    // Serial.println(fileName);
    // strftime(fileName, 15, "%H:%M:%S", &timeinfo);
    // Serial.println(fileName);

    Serial.println(&timeinfo, "%A, %m %d %Y %H:%M:%S");
    // Serial.print("Day of week: ");
    // Serial.println(&timeinfo, "%A");
    // Serial.print("Month: ");
    // Serial.println(&timeinfo, "%B");
    // Serial.print("Day of Month: ");
    // Serial.println(&timeinfo, "%d");
    // Serial.print("Year: ");
    // Serial.println(&timeinfo, "%Y");
    // Serial.print("Hour: ");
    // Serial.println(&timeinfo, "%H");
    // Serial.print("Hour (12 hour format): ");
    // Serial.println(&timeinfo, "%I");
    // Serial.print("Minute: ");
    // Serial.println(&timeinfo, "%M");
    // Serial.print("Second: ");
    // Serial.println(&timeinfo, "%S");

    // Serial.println("Time variables");
    // char timeHour[3];
    // strftime(timeHour, 3, "%H", &timeinfo);
    // Serial.println(timeHour);
    // char timeWeekDay[10];
    // strftime(timeWeekDay, 10, "%A", &timeinfo);
    // Serial.println(timeWeekDay);
    // Serial.println();
}