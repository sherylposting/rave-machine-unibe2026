#include <unity.h>
#include <cstring>
#include <Arduino.h>
#include <HTTPClient.h>

#include "sensor.h"
#include "server.h"

// ---- tests ---- //

void test_getData(void){
    char dataBuffer[128];
    getData(dataBuffer, sizeof(dataBuffer));

    Serial.print("getData returned: ");
    Serial.println(dataBuffer);

    TEST_ASSERT_TRUE(std::strstr(dataBuffer, "acc_x") != NULL);
}

void test_ping(void) {
    uint32_t start = millis();
    sendDataToServer("{\"ping\":1}");
    uint32_t latency = millis() - start;

    Serial.printf("ping: %u ms\n", latency);
    TEST_ASSERT_LESS_OR_EQUAL(500, latency); // check if less than 500 ms latency
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_getData);
  RUN_TEST(test_ping);
  return UNITY_END();
}

/**
  * For Arduino framework
  */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}
void loop() {}