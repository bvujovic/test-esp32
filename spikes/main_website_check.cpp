//* Device checks https://elektrodistribucija.rs/planirana-iskljucenja-beograd/...
//* to see if there are planned power outages.

#include <Arduino.h>
#include "WiFiServerBasics.h"
#include "PlannedOutagesChecker.h"
PlannedOutagesChecker poc;
#include <CredCallMeBot.h>
#include <HTTPClient.h>

// const byte pinLed = 2; //* Ne radi LED na ovom pinu.

int sendWhatsAppMessage(String &msg)
{
    // led.on();
    //* https://www.callmebot.com/blog/free-api-whatsapp-messages/
    String url = "http://api.callmebot.com/whatsapp.php?";
    url = url + "phone=" + CMB_PHONE;
    // 💥Stan, kuhinja, sudopera:
    // VISOK NIVO VODE U SUDOPERI 💦
    // url = url + "&text=" + "%F0%9F%92%A5+Stan,+kuhinja,+sudopera:%0AVISOK+NIVO+VODE+U+SUDOPERI+%F0%9F%92%A6";
    msg.replace(' ', '+');
    msg.replace("\n", "%0A");
    url = url + "&text=" + msg;
    url = url + "&apikey=" + CMB_API_KEY;
    WiFiClient wiFiClient;
    HTTPClient client;
    client.begin(wiFiClient, url);
    int respCode = client.GET();
    if (respCode > 0)
        Serial.println(String("Response: ") + client.getString());
    client.end();
    // led.off();
    return respCode;
}

void setup()
{
    // pinMode(pinLed, OUTPUT);
    // for (size_t i = 0; i < 3; i++)
    // {
    //     digitalWrite(pinLed, 1);
    //     delay(500);
    //     digitalWrite(pinLed, 0);
    //     delay(500);
    // }

    Serial.begin(115200);
    Serial.println();
    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);
    while (!ConnectToWiFi())
    {
        Serial.println("Connecting to WiFi failed.");
        return;
    }

    //* Testing POC funcionality when memory is low.
    // Serial.println(ESP.getFreeHeap() / 1024);
    // char *ptr = (char *)malloc(15 * 1024);
    // Serial.println(ptr != NULL);
    // Serial.println(ESP.getFreeHeap() / 1024);

    poc.loadLocations("/power_outage_locations.csv", true);
    String msg;
    PocResult res = poc.check(msg);
    switch (res)
    {
    case PocError:
        msg = String("POC greška: ") + msg;
        sendWhatsAppMessage(msg);
        break;
    case PocNoOutages:
        msg = "Nema planiranih isključenja struje na zadatim lokacijama.";
        break;
    case PocOutagesFound:
        msg = String("Planirana isključenja struje na zadatim lokacijama!\n") + msg;
        sendWhatsAppMessage(msg);
        break;
    }
    Serial.println(msg);
    Serial.println("Going to sleep...");
    Serial.flush();
    
#ifdef ESP32
    esp_sleep_enable_timer_wakeup(5 * 60 * 1000000); // wake up after 5 minutes
    esp_deep_sleep_start();
#elif defined(ESP8266)
    ESP.deepSleep(0); // sleep forever
#endif
}

void loop()
{
}
