//* Tested on ESP32-S3 SuperMini. It works when Li-Ion battery is connected to 5V and GND,
//* but not on B+ and B-.

#include <Arduino.h>
#include <esp_sleep.h>

#define uS_TO_S_FACTOR 1000000ULL /* Faktor konverzije mikro-sekundi u sekunde */
#define TIME_TO_SLEEP 5           /* Koliko sekundi će ESP spavati */

// Promenljiva koja preživljava Deep Sleep
RTC_DATA_ATTR int bootCount = 0;

void setup()
{
    Serial.begin(115200);
    delay(1000); // Kratka pauza da stignete otvoriti Serial Monitor

    // Povećaj brojač i ispiši ga
    bootCount++;
    Serial.println("Buđenje br: " + String(bootCount));

    // 1. Konfiguracija izvora buđenja (Tajmer)
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("ESP32-S3 ide na spavanje na " + String(TIME_TO_SLEEP) + " sekundi.");

    // Opciono: Isključite WiFi/BT pre spavanja radi dodatne uštede
    // esp_wifi_stop();

    // 2. Ulazak u Deep Sleep
    Serial.flush();
    esp_deep_sleep_start();

    Serial.println("Ovo se nikada nece ispisati");
}

void loop()
{
    // Prazno - kod se resetuje pre nego što stigne ovde
}
