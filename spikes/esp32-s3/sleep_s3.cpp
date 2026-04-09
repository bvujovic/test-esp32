#include <Arduino.h>

#define LED_PIN 48

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // turn LED OFF

    // Enable hold on this pin
    // gpio_hold_en((gpio_num_t)LED_PIN);

    // Also enable hold during deep sleep
    // gpio_deep_sleep_hold_en();

    delay(1000);
    // gpio_pullup_dis((gpio_num_t)LED_PIN);
    // gpio_pulldown_dis((gpio_num_t)LED_PIN);
    esp_deep_sleep_start();
}

void loop()
{
}