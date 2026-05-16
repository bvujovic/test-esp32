//* ESP32-S3 Super Mini (PWR LED desoldered): 0.47mA in deep sleep

#include <Arduino.h>

// #define LED_PIN 48

void setup()
{
    // pinMode(LED_PIN, OUTPUT);
    // digitalWrite(LED_PIN, LOW); // turn LED OFF

    // Enable hold on this pin
    // gpio_hold_en((gpio_num_t)LED_PIN);

    // Also enable hold during deep sleep
    // gpio_deep_sleep_hold_en();

    // delay(5000);
    // gpio_pullup_dis((gpio_num_t)LED_PIN);
    // gpio_pulldown_dis((gpio_num_t)LED_PIN);
    // esp_sleep_enable_timer_wakeup(3 * 1000 * 1000);
    // esp_deep_sleep_start();

    // delayMicroseconds(200000);
    delay(4000);
    ESP.deepSleep(4000000);
}

void loop()
{
}