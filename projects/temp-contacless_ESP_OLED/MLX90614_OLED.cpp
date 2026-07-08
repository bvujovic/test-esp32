//* MLX90614_OLED.cpp - Example of using Adafruit MLX90614 IR temperature sensor with an OLED display
//* It reads the object and ambient temperatures and displays them on the OLED screen in a "object|ambient" format.
//* Current consumption: 24mA

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>           // lib_deps = olikraus/U8g2@^2.36.12
#include <Adafruit_MLX90614.h> // lib_deps = adafruit/Adafruit MLX90614 Library @ ^2.1.5

U8G2_SSD1306_72X40_ER_F_HW_I2C disp(U8G2_R0, U8X8_PIN_NONE, 6, 5); // rotation, reset, clock, data
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

char str[6];
int dy;

// Function to display the object and ambient temperatures on the OLED screen
void displayNums(int a, int b)
{
    a %= 100;
    b %= 100;
    sprintf(str, "%d|%d", a, b);
    auto dx = (disp.getDisplayWidth() - disp.getStrWidth(str)) / 2;
    disp.clearBuffer();
    disp.drawStr(dx, dy, str);
    disp.sendBuffer();
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    disp.setBusClock(100000);
    if (!disp.begin())
    {
        Serial.println("Failed to initialize OLED");
        while (true)
            delay(1000);
    }
    if (!mlx.begin())
    {
        Serial.println("Failed to initialize MLX90614");
        while (true)
            delay(1000);
    }
    //? mlx.emmissivity(0.95); // set emissivity to 0.95 for better accuracy with human skin
    disp.clearBuffer();
    disp.setFont(u8g2_font_logisoso24_tf);
    dy = disp.getDisplayHeight() - (disp.getDisplayHeight() - disp.getMaxCharHeight()) / 2; // use max char height for better centering
}

void loop()
{
    auto tempObject = mlx.readObjectTempC();
    auto tempAmbient = mlx.readAmbientTempC();
    displayNums((int)(tempObject + 0.5), (int)(tempAmbient + 0.5));

    delay(2000);
}
