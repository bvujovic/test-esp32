// #include <Arduino.h>
#include <Adafruit_SHT4x.h> // adafruit/Adafruit SHT4x Library @ ^1.0.5

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        delay(100);

    Serial.println("SHT4x test");
    if (!sht4.begin())
    {
        Serial.println("Couldn't find SHT4x sensor!");
        while (1)
            delay(100);
    }

    Serial.println("Found SHT4x sensor");

    // Set precision (SHT4X_HIGH_PRECISION, SHT4X_MED_PRECISION, SHT4X_LOW_PRECISION)
    sht4.setPrecision(SHT4X_HIGH_PRECISION);

    // Set heater (SHT4X_NO_HEATER, SHT4X_HIGH_HEATER_1S, etc.)
    sht4.setHeater(SHT4X_NO_HEATER);
}

void loop()
{
    sensors_event_t humidity, temp;

    // Obtain results
    sht4.getEvent(&humidity, &temp);

    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" degrees C");

    Serial.print("Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println("% rH");

    Serial.println();
    delay(5000);
}