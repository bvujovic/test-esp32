//* Tested on ESP32-C3 SuperMini (black) /w and /wo additional wire antenna when Li-Ion battery is connected
//* directly to 5V and GND pins. It works well with electrolytic capacitor but not without.
//* It didn't work with 18650 battery at 3.5V, but at 3.9V it did.
//* Important setting: WiFi.setTxPower(WIFI_POWER_13dBm)

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <MacAddresses.h>

const byte pinLed = 8;
void ledOn(bool on) { digitalWrite(pinLed, !on); }
void ledOn(int count)
{
    for (int i = 0; i < count; i++)
    {
        ledOn(true);
        delay(200);
        ledOn(false);
        delay(200);
    }
}

uint8_t *mac = macEsp32DevIpex;
bool sendSuccess = true;

esp_now_peer_info_t peerInfo;
void OnDataSent(const uint8_t *mac, esp_now_send_status_t sendStatus)
{
    Serial.print("Last Packet Send Status: ");
    Serial.println((sendSuccess = sendStatus == ESP_NOW_SEND_SUCCESS) ? "Success" : "FAIL");
    ledOn(sendSuccess ? 1 : 3);
}

void setup()
{
    pinMode(pinLed, OUTPUT);
    // digitalWrite(pinLed, true);
    ledOn(false);
    Serial.begin(115200);
    Serial.println();
    WiFi.mode(WIFI_STA);
    WiFi.setTxPower(WIFI_POWER_13dBm); // adjust power for wifi antenna, default is max power

    // Serial.println(WiFi.macAddress());
    if (esp_now_init() != 0)
    {
        Serial.println("ESP NOW INIT FAIL");
        while (true)
            delay(100);
    }

    esp_now_register_send_cb(OnDataSent);
    memcpy(peerInfo.peer_addr, mac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        ledOn(true);
        while (true)
            delay(100);
    }
}

// B char msg[] = "Pozdrav ESP-Now";
char msg[10];
int cnt = 0;

// typedef struct struct_message
// {
//     char a[32];
//     int b;
//     float c;
//     bool d;
// } struct_message;
// struct_message myData;

void loop()
{
    // strcpy(myData.a, "THIS IS A CHAR");
    // myData.b = random(1, 20);
    // myData.c = 1.2;
    // myData.d = false;
    // esp_err_t result = esp_now_send(mac, (uint8_t *)&myData, sizeof(myData));

    // itoa(cnt++, msg, 10);
    ultoa(millis(), msg, 10);
    auto res = esp_now_send(mac, (uint8_t *)&msg, strlen(msg));
    Serial.printf("Send response: 0x%X\n", res);
    delay(6000);

    ledOn(!sendSuccess);
    delay(1000);
    ledOn(false);
}
