void setup() {
  Serial.begin(9600);

}

void loop() {
  static uint32_t lastSwitchTime = 0;
  uint32_t currentTime = millis();
  static int state = 0;

  // Check if 5 seconds have passed
  if (currentTime - lastSwitchTime >= 1000) {
    state = (state + 1) % 8;
    lastSwitchTime = currentTime;
  }
  Serial.println(state);

}
