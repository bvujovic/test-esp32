#include <GxEPD2_BW.h> // lib_deps = zinggjm/GxEPD2 @ ^1.6.9
#include <SPI.h>

// Pin definitions
// #define CS 5
// #define DC 17
// #define RST 16
// #define BUSY 4
#define CS 10
#define DC 2
#define RST 3
#define BUSY 4
    
// Display (example: 2.13", 250x122, b/w display)
GxEPD2_BW<GxEPD2_213, GxEPD2_213::HEIGHT> display(GxEPD2_213(CS, DC, RST, BUSY));

void setup()
{
    SPI.begin(6, -1, 7, CS); // SCK=5, MISO unused, MOSI=7, CS=10
    Serial.begin(115200);
    delay(1000); // Allow time for serial monitor to connect
    Serial.println("Initializing ePaper display...");
    display.init();

    Serial.println("ePaper display initialized.");
    display.setRotation(0);
    display.setTextColor(GxEPD_BLACK);

    auto cnt = 1;
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(10, 50);
        display.setTextSize(2);
        display.print("Hello ESP32!");
        Serial.println(cnt++);
    } while (display.nextPage());
    Serial.println("Display update complete.");
}

void loop() {}
