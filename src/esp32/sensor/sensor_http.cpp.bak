#include <Wire.h>
#include <I2C_MPU6886.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

// this should get sensor values and also send it to the server via http. not sure if it works...

/// instructions: put in your appropriate ssid, password, serverURL values
// 1 - upload this program. this will start the ESP's wifi. it will also start pushing the http request and giving error -1
// 2 - connect your laptop to the wifi 
// 3 - run http_server.py on your laptop, probably don't use WSL
// in the terminal where you started your server, it should start saying "POST / HTTP/1.1" 200 - Received: ...

const char* ssid = "ESP32-HVEOSL"; /// put in your wifi name here
const char* password = "12345678"; /// put in your wifi password here

const char* serverURL = "http://192.168.4.2:8000"; /// put in your IPv4 address in the format: http://192.168.1.xxx:8000

// sensor setup
I2C_MPU6886 imu;

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float temp;

char buffer[128];

// http POST setup
void connect_wifi(void) {
    Serial.println("Starting SoftAP...");

    WiFi.mode(WIFI_AP);

    bool ok = WiFi.softAP(ssid, password);

    if (!ok) {
        Serial.println("SoftAP failed!");
        return;
    }

    Serial.println("WiFi AP started");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.softAPIP()); // usually 192.168.4.1
}

void send_str(const char* msg) {
    HTTPClient http;

    http.begin(serverURL);
    http.addHeader("Content-Type", "text/csv"); // tell server it's in csv format

    int code = http.POST((uint8_t*)msg, strlen(msg));

    Serial.print("HTTP response code: ");
    Serial.println(code);

    if (code > 0) {
        String payload = http.getString();
        Serial.print("Server reply: ");
        Serial.println(payload);
    } else if (code == -1) {
        Serial.println("Request failed: start the http_server.py, or probably a network or firewall issue");
    } else if (code == -5) {
        Serial.println("Request failed: connection lost during request");
    } else {
        Serial.println("Request failed");
    }

    http.end();
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("Starting I2C...");
  Wire.begin(26, 32);   // M5 Atom Lite Grove Port

  Serial.println("Init MPU6886...");
  imu.begin();

  Serial.println("MPU6886 Init OK");

  Serial.println("Starting wifi...");
  connect_wifi();
}

void loop() {
  imu.getAccel(&accX, &accY, &accZ);
  imu.getGyro(&gyroX, &gyroY, &gyroZ);
  imu.getTemp(&temp);

  sprintf(buffer, "%.2f, %.2f, %.2f, %.2f, %.2f, %.2f", 
          accX, accY, accZ, gyroX, gyroY, gyroZ);
  send_str(buffer);

  delay(300);
}