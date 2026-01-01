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

//* https://forum.arduino.cc/t/how-can-i-get-the-local-time-automatically-including-automatic-summer-winter-offsets/938704/3?_gl=1*xjaf9q*_up*MQ..*_ga*NjgxMjQyNjI4LjE3NjMxNjEwMTY.*_ga_NEXN8H46L5*czE3NjMxNjEwMTMkbzEkZzAkdDE3NjMxNjEwMTMkajYwJGwwJGg3MjA2NTUxODM.
//* https://forum.arduino.cc/t/using-ntp-server-to-set-time-possible-misunderstanding/1000465/10?_gl=1*1lp8v9p*_up*MQ..*_ga*NjgxMjQyNjI4LjE3NjMxNjEwMTY.*_ga_NEXN8H46L5*czE3NjMxNjEwMTMkbzEkZzAkdDE3NjMxNjEwMTMkajYwJGwwJGg3MjA2NTUxODM.
//* https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/

#include <CredWiFi.h> // WiFi credentials
// #ifndef STASSID
// #define STASSID "your-ssid"    // set your SSID
// #define STAPSK "your-password" // set your wifi password
// #endif

/* Configuration of NTP */
// choose the best fitting NTP server pool for your country
#define MY_NTP_SERVER "rs.pool.ntp.org"

// choose your time zone from this list
// https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"
// Europe/Belgrade -> CET-1CEST,M3.5.0,M10.5.0/3

/* Necessary Includes */
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

#ifdef ARDUINO_ARCH_ESP32
    // ESP32 seems to be a little more complex:
    configTime(0, 0, MY_NTP_SERVER); // 0, 0 because we will use TZ in the next line
    setenv("TZ", MY_TZ, 1);          // Set environment variable with your time zone
    tzset();
#else
    // ESP8266
    configTime(MY_TZ, MY_NTP_SERVER); // --> for the ESP8266 only
#endif

    Serial.println("Waiting for NTP time sync:");
    while (tm.tm_year < (2024 - 1900))
    {
        Serial.print(".");
        delay(1000);
        getTime();
    }
    Serial.println("Time synchronized!");
}

void loop()
{
    getTime();
    showTime();
    delay(5000); // dirty delay
}
