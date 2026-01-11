//* https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
//* https://cplusplus.com/reference/ctime/strftime/
//* https://cplusplus.com/reference/ctime/tm/

#include <WiFi.h>
#include "time.h"
#include <CredWiFi.h>

// const char *ssid = "REPLACE_WITH_YOUR_SSID";
// const char *password = "REPLACE_WITH_YOUR_PASSWORD";

// const char *ntpServer = "pool.ntp.org";
// const char *ntpServer = "1.rs.pool.ntp.org";
// const char *ntpServer = "time2.google.com";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

void printLocalTime();

void setup()
{
    Serial.begin(115200);

    // Connect to Wi-Fi
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");

    // Init and get the time
    configTime(3600, 0, "rs.pool.ntp.org");
    // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();

    // disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}

void loop()
{
    delay(1000);
    printLocalTime();
}

void printLocalTime()
{
    struct tm ti;
    if (!getLocalTime(&ti))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&ti, "%Y-%m-%d");
    Serial.println(&ti, "%H:%M:%S");
    // Serial.println(&ti, "%A, %B %d %Y %H:%M:%S");
    // Serial.print("Day of week: ");
    // Serial.println(&ti, "%A");
    // Serial.print("Month: ");
    // Serial.println(&ti, "%B");
    // Serial.print("Day of Month: ");
    // Serial.println(&ti, "%d");
    // Serial.print("Year: ");
    // Serial.println(&ti, "%Y");
    // Serial.print("Hour: ");
    // Serial.println(&ti, "%H");
    // Serial.print("Hour (12 hour format): ");
    // Serial.println(&ti, "%I");
    // Serial.print("Minute: ");
    // Serial.println(&ti, "%M");
    // Serial.print("Second: ");
    // Serial.println(&ti, "%S");

    // Serial.println("Time variables");
    char timeHour[3];
    strftime(timeHour, 3, "%H", &ti);
    Serial.println(timeHour);
    // char timeWeekDay[10];
    // strftime(timeWeekDay, 10, "%A", &ti);
    // Serial.println(timeWeekDay);
    Serial.println();
}
