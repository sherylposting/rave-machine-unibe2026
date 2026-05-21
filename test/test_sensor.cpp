#include <unity.h>
#include <cstring>

#include "sensor.h"

// ---- tests ---- //

void test_getData(void){
    char dataBuffer[128];
    getData(dataBuffer, sizeof(dataBuffer));

    TEST_ASSERT_TRUE(std::strstr(dataBuffer, "ax") != NULL);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_getData);
  return UNITY_END();
}

//For ESP-IDF framework
void app_main() {
  runUnityTests();
}

void setup() {
    // empty
}

void loop() {
    // empty
}