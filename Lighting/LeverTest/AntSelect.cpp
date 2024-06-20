#include "AntSelect.h"

// int ZONE1_START = 0;
// int ZONE1_END = 97;
// int ZONE2_START = 98;
// int ZONE2_END = 129;
// int ZONE3_START = 130;
// int ZONE3_END = 149;

void breathingLever() {
  static uint32_t lastTime = 0;
  static uint8_t brightness = 0;
  static int8_t direction = 5;
  static bool zone2Active = true;
  static bool zone3Active = false;

  uint32_t currentTime = millis();
  
  if (currentTime - lastTime >= 20) { // 20 milliseconds delay for smoother effect
    brightness += direction;

    // Reverse direction at limits
    if (brightness == 0 || brightness == 255) {
      direction = -direction;
      if (brightness == 0) {
        zone2Active = !zone2Active; // Alternate zones when brightness reaches 0
        zone3Active = !zone3Active; // Synchronize zone activation
      }
    }

    // Define the colors
    CRGB color1 = CRGB::Azure;
    CRGB color2 = CRGB::Tomato;
    CRGB currentColor1 = color1.fadeToBlackBy(255 - brightness);
    CRGB currentColor2 = color2.fadeToBlackBy(255 - brightness);

    for(int i = 0; i <= 97; i++){
      ledsAnts[i] = CRGB::Black;
    }
    // Set the color based on the brightness
    for (int i = 98; i <= 129; i++) {
      ledsAnts[i] = zone2Active ? currentColor1 : CRGB::Black;
    }
    for (int i = 130; i <= 149; i++) {
      ledsAnts[i] = zone3Active ? currentColor2 : CRGB::Black;
    }

    lastTime = currentTime;
  }
}

void breathingHill() {
  static uint32_t lastTime = 0;
  static uint8_t brightness = 0;
  static int8_t direction = 5;
  static bool zone1Active = true;
  static bool zone2Active = false;

  uint32_t currentTime = millis();

  if (currentTime - lastTime >= 20) { // 20 milliseconds delay for smoother effect
    brightness += direction;

    // Reverse direction at limits
    if (brightness == 0 || brightness == 255) {
      direction = -direction;
      if (brightness == 0) {
        zone1Active = !zone1Active; // Alternate zones when brightness reaches 0
        zone2Active = !zone2Active; // Synchronize zone activation
      }
    }

    // Define the colors
    CRGB color1 = CRGB::Tomato;
    CRGB color2 = CRGB::Azure;
    CRGB currentColor1 = color1.fadeToBlackBy(255 - brightness);
    CRGB currentColor2 = color2.fadeToBlackBy(255 - brightness);

    // Set the color based on the brightness
    for (int i = 0; i <= 97; i++) {
      ledsAnts[i] = zone1Active ? currentColor1 : CRGB::Black;
    }
    for (int i = 98; i <= 129; i++) {
      ledsAnts[i] = zone2Active ? currentColor2 : CRGB::Black;
    }
    for (int i = 130; i <= 149; i++) {
      ledsAnts[i] = CRGB::Black;
    }

    lastTime = currentTime;
  }
}


