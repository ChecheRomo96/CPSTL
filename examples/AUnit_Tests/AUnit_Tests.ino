#include <AUnit.h>

void setup() {
#if ! defined(EPOXY_DUINO)
  delay(1000); // wait for stability on some boards to prevent garbage Serial
#endif
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  while (!Serial); // for the Arduino Leonardo/Micro only
  Serial.println("Legacy AUnit runner: no CPSTL test cases are registered in this sketch.");
  Serial.println("Open a module tutorial for a worked example, or tests/Arduino for hardware tests.");
#if defined(EPOXY_DUINO)
  Serial.setLineModeUnix();
#endif
}

void loop() {
  aunit::TestRunner::run();
}
