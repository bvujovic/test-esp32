// #include <Arduino.h>
// void setup(){ }
// void loop() { delay(1000); }


//* https://techtutorialsx.com/2021/01/04/esp32-soft-ap-and-station-modes/
#include <WiFi.h>
#include "CredWiFi.h" // define WIFI_SSID and WIFI_PASS
const char *wifi_network_ssid = WIFI_SSID;
const char *wifi_network_password = WIFI_PASS;

const char *soft_ap_ssid = "MyESP32AP";
const char *soft_ap_password = "testpassword";

void setup()
{

    Serial.begin(115200);

    WiFi.mode(WIFI_MODE_APSTA);

    WiFi.softAP(soft_ap_ssid, soft_ap_password);
    WiFi.begin(wifi_network_ssid, wifi_network_password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }

    Serial.print("ESP32 IP as soft AP: ");
    Serial.println(WiFi.softAPIP());

    Serial.print("ESP32 IP on the WiFi network: ");
    Serial.println(WiFi.localIP());
}

void loop() {}

// /*
//   OUTPUT: Creating your own hotspot on esp32 wifi+ble module as well as
//           connect to your home router or mobile hotspot.
//           BOTH ACCESS POINT + STATION ACTIVATED
//   Author: Ankit Rana (Futechiot)
//   Board Used: esp32 development board, LolinD32,WEMOS LOLIN32, ESP32 MH-ET live Minikit
//   Website: www.futechiot.com
//   GitHub: https://github.com/futechiot
//   --> Download and Open this Application in Laptop
//   --> Scan for networks, make sure uour PC and Board are connnected in same network
//   --> Search for obtained IP, see in manufracturer "Espressif"
//   --> Scan for wifi in your mobile or laptop you eill see your hotspot name in scanned network
// */

// #include <WiFi.h> //Wifi library of Esp32 to access HARDWARRE APIS and othe functionality

// /* Set these to your Wifi credentials. */

// #include "CredWiFi.h"
// const char *Wifi_ssid = WIFI_SSID;       // SSID of your Router OR mobile hotspot
// const char *Wifi_password = WIFI_PASS; // PASSWORD of your Router or Mobile hotspot see below example

// const char *Apssid = "BojanESP"; // give Accesspoint SSID, your esp's hotspot name
// //* const char *Appassword = "123456789";      // password of your esp's hotspot

// void setup()
// {

//     // put your setup code here, to run once:

//     Serial.begin(115200); // to enable Serial Commmunication with connected Esp32 board
//     delay(500);
//     WiFi.mode(WIFI_AP_STA); // changing ESP9266 wifi mode to AP + STATION

//     //* WiFi.softAP(Apssid, Appassword);  // Starting AccessPoint on given credential
//     WiFi.softAP(Apssid);              // Starting AccessPoint on given credential
//     IPAddress myIP = WiFi.softAPIP(); // IP Address of our Esp32 accesspoint(where we can host webpages, and see data)
//     Serial.print("Access Point IP address: ");
//     Serial.println(myIP);

//     Serial.println("");

//     delay(1500);
//     Serial.println("connecting to Wifi:");
//     Serial.println(Wifi_ssid);

//     WiFi.begin(Wifi_ssid, Wifi_password); // to tell Esp32 Where to connect and trying to connect
//     while (WiFi.status() != WL_CONNECTED)
//     { // While loop for checking Internet Connected or not
//         delay(500);
//         Serial.print(".");
//     }

//     Serial.println("");
//     Serial.println("WiFi connected");
//     Serial.println("IP address: ");
//     Serial.println(WiFi.localIP()); // successful Connection of Esp32,
//                                     // printing Local IP given by your Router or Mobile Hotspot,
//                                     // Esp32 connect at this IP  see in advanced Ip scanner
//     Serial.println("");
// }

// void loop()
// {
//     // put your main code here, to run repeatedly:
//     delay(100);
// }

// #include <Arduino.h>
// #include <WiFi.h>

// const char *ssid = "Vujovic";
// const char *passphrase = "ritern123";

// IPAddress local_IP(192, 168, 4, 22);
// IPAddress gateway(192, 168, 4, 9);
// IPAddress subnet(255, 255, 255, 0);

// void setup()
// {
//     Serial.begin(115200);
//     Serial.println();
//     Serial.print("Setting soft-AP configuration ... ");
//     Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
//     Serial.print("Setting soft-AP ... ");
//     Serial.println(WiFi.softAP(ssid, passphrase) ? "Ready" : "Failed!");
//     // Serial.println(WiFi.softAP(ssid) ? "Ready" : "Failed!");
//     // WiFi.softAP(ssid);
//     // WiFi.softAP(ssid, passphrase, channel, ssdi_hidden, max_connection)

//     Serial.print("Soft-AP IP address = ");
//     Serial.println(WiFi.softAPIP());
// }
// void loop()
// {
//     Serial.print("[Server Connected] ");
//     Serial.println(WiFi.softAPIP());
//     delay(500);
// }
