//* Current on ESP32 board with battery connector in deep sleep: ~65uA

#include <Arduino.h>

void setup()
{
    esp_sleep_enable_timer_wakeup(10 * 1000 * 1000);
    esp_deep_sleep_start();
}

void loop()
{
}
