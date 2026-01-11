//* Programski kôd za eksperiment: koliko naizmenične struje troši montaža 220V->5V i ESP8266 u
//* 3 slučaja-faze: veb server, diskonektovan sa mreže, deep sleep. Ovo su rezultati:
//*             ~I(mA)  ~P(mW)  W za dan    W za mesec
//* Server      2.5     550     13.2        403
//* No WiFi     1       220     5.3         162
//* Sleep       0.5     110     2.6         80
//* Realni aparati će trošiti više struje zbog dodatnih komponenti.

//* https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/
//* https://randomnerdtutorials.com/esp32-web-server-arduino-ide/

#include <Arduino.h>
typedef unsigned long ulong;

// #include <WiFiServerBasics.h>
// ESP8266WebServer server(80);
#include <WiFi.h>
#include <CredWiFi.h>
WiFiServer server(80);

const byte pinLed = 8;

void ledOn(bool on, ulong itv = 0)
{
    // digitalWrite(pinLed, !on);
    digitalWrite(pinLed, on);
    if (itv > 0)
        delay(itv);
}

void bigBlink()
{
    ledOn(false, 500);
    ledOn(true, 1000);
    ledOn(false);
}

// Konektovanje na WiFi, postavljanje IP adrese i startovanje veb servera.
void WiFiOn()
{
    ledOn(pinLed, true);
    WiFi.mode(WIFI_STA);
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    //? SetupIPAddress(55);
    // server.on("/", []()
    //           { server.send(200, "text/plain", "ESP Web server is working."); });
    server.begin();
    ledOn(pinLed, false);
}

// Diskonektovanje sa WiFi-a.
void WiFiOff()
{
    server.stop();
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    // WiFi.forceSleepBegin();
    delay(100);
}

enum Faza
{
    WebServer,
    NoWiFi,
    Sleep
} faza;

const ulong itvTrajanjeFaze = 10000;
ulong msPromenaFaze;

void setup()
{
    Serial.begin(115200);
    pinMode(pinLed, OUTPUT);
    WiFiOn();
    faza = WebServer;
    msPromenaFaze = millis();
    bigBlink();
    bigBlink();
}

void loop()
{
    delay(10);

    if (faza == WebServer)
    {
        // server.handleClient();
        if (millis() > msPromenaFaze + itvTrajanjeFaze)
        {
            bigBlink();
            Serial.println("NoWiFi");
            faza = NoWiFi;
            WiFiOff();
            msPromenaFaze = millis();
        }
    }

    if (faza == NoWiFi)
    {
        if (millis() > msPromenaFaze + itvTrajanjeFaze)
        {
            bigBlink();
            Serial.println("Sleep");
            // ESP.deepSleep(itvTrajanjeFaze * 1000);
            esp_sleep_enable_timer_wakeup(itvTrajanjeFaze * 1000);
            Serial.flush();
            esp_deep_sleep_start();
        }
    }
}
