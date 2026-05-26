#include <WiFi.h>
#include <HTTPClient.h>
#include "server.h"

/// instructions: put in your appropriate ssid, password, serverURL values
    // 1 - run http_server.py on your laptop python, probably don't use WSL
    // 2 - upload main.cpp
    // 3 - open tools -> serial monitor to check the ESP's output
// in the terminal where you started your server, it should start saying "POST / HTTP/1.1" 200 - Received: ...

const char* ssid = "ESP32-HVEOSLZP";
const char* password = "12345678";
const char* serverURL = "http://192.168.4.2:8000";

// starts the ESP32's wifi hotspot (Software-enabled Access Point, softAP)
void setupWiFi() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.println("WiFi AP started");
}

// sends data from ESP32 -> the server started at http_server.py
// assumes data is a string in JSON format
void sendDataToServer(const char* msg) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "text/json"); // notes that data is in json format
    
    int code = http.POST((uint8_t*)msg, strlen(msg)); // http POST
    Serial.printf("HTTP Response: %d\n", code);
    http.end();
}