// This is a simple example of using the ESP32-C3 with an OLED display and two MQ gas sensors
// (MQ2 and MQ135). If needed, add graph for latest values 
// (e.g. display values, btn click - graph for MQ2, btn click - graph for MQ135)

#include <Arduino.h>
#include <U8g2lib.h> // lib_deps = olikraus/U8g2@^2.36.12

U8G2_SSD1306_72X40_ER_F_HW_I2C disp(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/6, /* data=*/5);
char str[6];
int dx, dy;

void displayNums(int a, int b)
{
  a %= 100;
  b %= 100;
  sprintf(str, "%02d|%02d", a, b);
  auto dx = (disp.getDisplayWidth() - disp.getStrWidth(str)) / 2;
  disp.clearBuffer();
  disp.drawStr(dx, dy, str);
  disp.sendBuffer();
  // Serial.println(str);
}

// On the ESP32-C3, GPIO 0, 1, 2, 3, 4, and 5 can be used as ADC1 channels.
// 5 is used for the OLED display, so we will use GPIO 4 and GPIO 2 for the MQ2 and MQ135 sensors respectively.
const byte pinMQ2 = 4;
const byte pinMQ135 = 2;

ulong msPrev = 0;
const ulong interval = 5000;

void setup()
{
  disp.begin();
  // disp.clearBuffer(); // clear the internal memory
  // disp.setDisplayRotation(U8G2_R2);   // Rotate display 180 degrees (upside down)
  disp.setFont(u8g2_font_logisoso24_tf);
  dy = disp.getDisplayHeight() - (disp.getDisplayHeight() - disp.getMaxCharHeight()) / 2; // 30 is the size of the font - change IN
  Serial.begin(115200);
}

int i = -1;

void loop()
{
  auto ms = millis();
  if (ms - msPrev >= interval || msPrev == 0) // Check if 5 seconds have passed
  {
    msPrev = ms;

    auto rawMQ2 = analogRead(pinMQ2);
    auto rawMQ135 = analogRead(pinMQ135);
    auto valMQ2 = map(rawMQ2, 0, 4095, 0, 99);     // Map the raw value to a percentage
    auto valMQ135 = map(rawMQ135, 0, 4095, 0, 99); // Map the raw value to a percentage
    displayNums(valMQ2, valMQ135);
    /*
        // Convert the analog readings to voltage (Optional)
        // 3.3V is the reference voltage, and 4095 is the max 12-bit ADC value
        float voltage1 = (rawMQ2 * 3.3) / 4095.0;
        float voltage2 = (rawMQ135 * 3.3) / 4095.0;

        // Print the results to the Serial Monitor
        Serial.println("--- Sensor Readings ---");
        Serial.print("Sensor 1 (GPIO ");
        Serial.print(pinMQ2);
        Serial.print("): Raw = ");
        Serial.print(rawMQ2);
        Serial.print(" | Voltage = ");
        Serial.print(voltage1);
        Serial.println("V");

        Serial.print("Sensor 2 (GPIO ");
        Serial.print(pinMQ135);
        Serial.print("): Raw = ");
        Serial.print(rawMQ135);
        Serial.print(" | Voltage = ");
        Serial.print(voltage2);
        Serial.println("V");
        Serial.println();
        */
  }

  //   disp.clearDisplay();
  //   disp.setPowerSave(1);
}
