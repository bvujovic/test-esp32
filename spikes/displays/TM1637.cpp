#include <Arduino.h>
#include <TM1637Display.h> // lib_deps = smougenot/TM1637 @ 0.0.0-alpha+sha.9486982048

#define CLK 20
#define DIO 21
#define MS_DELAY 2000

TM1637Display display(CLK, DIO);

void setup()
{
    display.setBrightness(2);
    // Try manually lighting all segments
    uint8_t data[] = {0xFF, 0xFF, 0xFF, 0xFF};
    display.setSegments(data);
    delay(MS_DELAY);
    
    display.showNumberDec(42, true); // Show a number with leading zeros
    delay(MS_DELAY);
    display.showNumberDec(123, false);
    delay(MS_DELAY);
    display.showNumberHexEx(0x1A3F, 0b11100000); // Show a hex number with custom segment control
    delay(MS_DELAY);
    display.clear(); // Clear the display
    delay(MS_DELAY);
}

void loop()
{
    delay(MS_DELAY);
}