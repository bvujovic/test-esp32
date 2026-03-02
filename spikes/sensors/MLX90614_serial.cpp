#include <Wire.h>
#include <Adafruit_MLX90614.h>

// For ESP32-C3, define I2C pins if not using defaults
#define SDA_PIN 4
#define SCL_PIN 5

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C

    if (!mlx.begin())
    {
        Serial.println("Error connecting to MLX sensor. Check wiring.");
        while (true)
            delay(2000);
    };
    Serial.println("MLX90614 Found!");
}

void loop()
{
    Serial.print("Ambient: ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject: ");
    Serial.print(mlx.readObjectTempC());
    Serial.println("*C");
    delay(2000);
}
