/*
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

//* My NodeMCU's MAC address: 84:F3:EB:77:04:BA
uint8_t mac[] = {0x84, 0xF3, 0xEB, 0x77, 0x04, 0xBA};
esp_now_peer_info_t peerInfo;
bool shouldSend = false;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    Serial.print("Bytes received: ");
    Serial.println(len);
    shouldSend = true;
}

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_send_cb(OnDataSent);
    memcpy(peerInfo.peer_addr, mac, 6);
    peerInfo.channel = 1;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

// char msg[] = "ESP32-Now 2way";
char msg[10] = "6666";
// ulong msLastSent = 0;

void loop()
{
    if (shouldSend)
    {
        sprintf(msg, "%u", millis());
        auto res = esp_now_send(mac, (uint8_t *)&msg, strlen(msg));
        Serial.printf("Send res: 0x%X\n", res);
        shouldSend = false;
    }
    // if (millis() >= msLastSent + 6000)
    // {
    //     auto res = esp_now_send(mac, (uint8_t *)&msg, strlen(msg));
    //     Serial.printf("Send res: 0x%X\n", res);
    //     msLastSent = millis();
    // }
}
