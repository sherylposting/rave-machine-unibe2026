#include <WiFi.h>
#include <HTTPClient.h>
#include "server.h"

/// instructions: put in your appropriate ssid, password, serverURL values
// 1 - run http_server.py on your laptop python, probably don't use WSL
// 2 - send this script
// 3 - open tools -> serial monitor to check the ESP's output
// in the terminal where you started your server, it should start saying "POST / HTTP/1.1" 200 - Received: hello from esp32

const char* ssid = "ESP32-HVEOSL";     //[cite: 3]
const char* password = "12345678";     //[cite: 3]
const char* serverURL = "http://192.168.4.2:8000"; //[cite: 3]

void setupWiFi() {
    WiFi.mode(WIFI_AP); //[cite: 3]
    WiFi.softAP(ssid, password); //[cite: 3]
    Serial.println("WiFi AP started");
}

void sendDataToServer(const char* msg) {
    HTTPClient http;
    http.begin(serverURL); //[cite: 3]
    http.addHeader("Content-Type", "text/plain"); //[cite: 3]
    
    int code = http.POST((uint8_t*)msg, strlen(msg)); //[cite: 3]
    Serial.printf("HTTP Response: %d\n", code);
    http.end(); //[cite: 3]
}