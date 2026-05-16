//* Current on ESP32 board with battery connector (micro USB) in deep sleep: ~65uA
//* measured by SMA19 multimeter, Li-Ion battery at 4.1V
//* Board                   Deep Sleep
//* batt con (USB C)        4.4mA
//* batt con (USB micro)    0.07mA


#include <Arduino.h>
#include "esp_sleep.h"

// #define ACTIVE_LEVEL HIGH
// const gpio_num_t pinWake = GPIO_NUM_14;

void setup()
{
    // esp_sleep_enable_timer_wakeup(10 * 1000 * 1000);
    // esp_deep_sleep_start();

    // delay(4000);
    ESP.deepSleep(4000000);

    // pinMode((int)pinWake, ACTIVE_LEVEL == LOW ? INPUT_PULLUP : INPUT_PULLDOWN);
    // esp_sleep_enable_ext0_wakeup(pinWake, ACTIVE_LEVEL);
    // delay(4000);
    // esp_deep_sleep_start();
}

void loop()
{
}
