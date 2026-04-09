/*
 * ESP32-C3 Sleep/Wake on Pin Example
 * This example demonstrates how to use the GPIO wakeup feature of the ESP32-C3.
 * It configures a GPIO pin as a wakeup source and puts the device into deep sleep.
 * When the specified pin is triggered (e.g., by pressing a button), the device wakes up and prints the wakeup reason.
 * Connections:
 * - Connect a button between GPIO4 (or GPIO3) and GND. Pressing the button will trigger the wakeup.
 * - The onboard LED (connected to GPIO8) will blink to indicate wakeup events.
 * Note: Ensure that you have the latest ESP32 Arduino core installed, as older versions may have issues with GPIO wakeup on C3.
 * References: */
// https://forum.arduino.cc/t/esp32-c3-super-mini-deepsleep-doorsensor/1401895/33
// https://github.com/espressif/arduino-esp32/issues/8901
// https://forum.seeedstudio.com/t/external-wakeup-from-deep-sleep-on-xiao-esp32c3/267532
// https://hutscape.com/tutorials/external-wakeup-arduino-esp32c3

#include <Arduino.h>
#include "esp_sleep.h"
// #include "driver/gpio.h" //?

#define WAKEUP_GPIO GPIO_NUM_4 // or GPIO_NUM_3
const byte pinLed = 8;         // GPIO8 is connected to the onboard LED on ESP32-C3-DevKitM-1

void ledOn(bool on)
{
    digitalWrite(pinLed, on ? LOW : HIGH);
}
void blinkLed(int times, int delayMs)
{
    for (int i = 0; i < times; i++)
    {
        ledOn(true);
        delay(delayMs);
        ledOn(false);
        delay(delayMs);
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    pinMode(pinLed, OUTPUT);
    Serial.println("Booting...");
    // Print wakeup reason
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
    printf("Wakeup cause: %d\n", cause);
    if (cause == ESP_SLEEP_WAKEUP_GPIO)
    {
        Serial.println("Woke up from GPIO!");
        blinkLed(3, 200);
        // cooldown period to avoid multiple triggers
        esp_sleep_enable_timer_wakeup(1 * 60 * 1000000ULL);
        esp_deep_sleep_start();
    }
    else
    {
        Serial.println("Normal startup");
        blinkLed(1, 500);
    }

    // uint64_t mask = esp_sleep_get_gpio_wakeup_status();
    // Serial.printf("Wakeup GPIO mask: 0x%llX\n", mask);  // Wakeup GPIO mask: 0x10 for GPIO4

    delay(2000);

    pinMode((int)WAKEUP_GPIO, INPUT_PULLUP);                                       // Configure pin
    gpio_wakeup_enable(WAKEUP_GPIO, GPIO_INTR_LOW_LEVEL);                          // Enable GPIO wakeup (LOW level trigger in this example)
    esp_deep_sleep_enable_gpio_wakeup(1 << WAKEUP_GPIO, ESP_GPIO_WAKEUP_GPIO_LOW); // Enable wakeup source
    Serial.println("Going to sleep...");
    delay(100);
    esp_deep_sleep_start();
}

void loop() {}
