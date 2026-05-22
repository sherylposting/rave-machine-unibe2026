#include <unity.h>
#include <cstring>
#include <Arduino.h>

#include "sensor.h"

// ---- tests ---- //

void test_getData(void){
    char dataBuffer[128];
    getData(dataBuffer, sizeof(dataBuffer));

    Serial.print("getData returned: ");
    Serial.println(dataBuffer);

    TEST_ASSERT_TRUE(std::strstr(dataBuffer, "acc_x") != NULL);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_getData);
  RUN_TEST(test_getData);
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