#include <GxEPD2_BW.h> // For Black and White panels
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ 10, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7));
GxEPD2_BW<GxEPD2_213, GxEPD2_213::HEIGHT> display(GxEPD2_213(/*CS=5*/ 5, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

void helloWorld();

void setup() {
  display.init(115200);
  helloWorld();
}

void helloWorld() {
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(10, 50);
    display.print("Hello World!");
  } while (display.nextPage());
}

void loop() {}