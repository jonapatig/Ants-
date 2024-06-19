#include "BreathingLever.h"

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

    for(int i = ZONE1_START; i <= ZONE1_END; i++){
      leds[i] = CRGB::Black;
    }
    // Set the color based on the brightness
    for (int i = ZONE2_START; i <= ZONE2_END; i++) {
      leds[i] = zone2Active ? currentColor1 : CRGB::Black;
    }
    for (int i = ZONE3_START; i <= ZONE3_END; i++) {
      leds[i] = zone3Active ? currentColor2 : CRGB::Black;
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
    for (int i = ZONE1_START; i <= ZONE1_END; i++) {
      leds[i] = zone1Active ? currentColor1 : CRGB::Black;
    }
    for (int i = ZONE2_START; i <= ZONE2_END; i++) {
      leds[i] = zone2Active ? currentColor2 : CRGB::Black;
    }
    for (int i = ZONE3_START; i <= ZONE3_END; i++) {
      leds[i] = CRGB::Black;
    }

    lastTime = currentTime;
  }
}


