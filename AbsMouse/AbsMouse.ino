#include "AbsMouse.h"
AbsMouse absMouse;
unsigned long lastCmdTime;

void setup() {
  Serial.begin(115200);
  absMouse.begin();
  absMouse.reset();
  Serial.println("Starting BLE work!");
  lastCmdTime = millis();
  // pinMode(LED_BUILTIN, OUTPUT);
}
int i = 0;
void loop() {
  // If no command for 5 seconds, mouse move back to (0,0)
  if (millis() - lastCmdTime >= 5000 && absMouse.now_x != 0 && absMouse.now_y != 0) {
    absMouse.reset();
    lastCmdTime = millis();
    // digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Rest for 5 seconds. Reset the mouse position");
  }
  if (Serial.available()) {
    // digitalWrite(LED_BUILTIN, HIGH);
    String tmp = Serial.readStringUntil(':');
    int index = tmp.indexOf(',');
    char action = tmp[0];
    int x = tmp.substring(1, index).toInt();
    int y = tmp.substring(index + 1, tmp.length()).toInt();
    // Serial.print("X: ");
    // Serial.print(x);
    // Serial.print(" Y:");
    // Serial.println(y);
    switch (action) {
      case 'p':
        absMouse.pressAt(x, y);
        break;
      case 'r':
        absMouse.releaseAt(x, y);
        break;
      case 'm':
        absMouse.moveTo(x, y);
        break;
      default: break;
    }
    lastCmdTime = millis();
  }
}