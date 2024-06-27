#include "AntSelect.h"

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
    CRGB color1 = CRGB::Goldenrod;
    CRGB color2 = CRGB::Goldenrod;
    CRGB currentColor1 = color1.fadeToBlackBy(255 - brightness);
    CRGB currentColor2 = color2.fadeToBlackBy(255 - brightness);

    for (int i = 0; i <= 95; i++) {
      ledsAnts[i] = CRGB::Black;
    }
    // Set the color based on the brightness
    for (int i = 96; i <= 125; i++) {
      ledsAnts[i] = zone2Active ? currentColor1 : CRGB::Black;
    }
    for (int i = 126; i <= 170; i++) {
      ledsAnts[i] = zone3Active ? currentColor2 : CRGB::Black;
    }

    lastTime = currentTime;
  }
}

void breathingHill() {
  static uint32_t lastTime = 0;
  static uint8_t brightnessA = 10; // Start brightness at 50 instead of 0
  static uint8_t brightnessB = 255; // Start brightness at 50 instead of 0
  static int8_t direction = 5;
  static bool zone1Active = true;
  static bool zone2Active = false;

  CRGB color1 = CRGB::Goldenrod;
  CRGB color2 = CRGB::Goldenrod;

  uint32_t currentTime = millis();

  if (currentTime - lastTime >= 20) { // 20 milliseconds delay for smoother effect
    brightnessA += direction;
    brightnessB -= direction;
    // Reverse direction at limits and alternate zones
    if (brightnessB <= 10 || brightnessB >= 255) {
      direction = -direction;
    }
    // Define the colors
    CRGB currentColor1 = color1;
    CRGB currentColor2 = color2;

    // Apply brightness fade
    currentColor1.fadeLightBy(255 - brightnessA);
    currentColor2.fadeLightBy(255 - brightnessB);

    // Set the color based on the brightness
    for (int i = 0; i <= 95; i++) {
      ledsAnts[i] = currentColor1; // Ensure it does not go completely black
    }
    for (int i = 96; i <= 125; i++) {
      ledsAnts[i] = currentColor2; // Ensure it does not go completely black
    }
    for (int i = 126; i <= 170; i++) {
      ledsAnts[i] = CRGB::Black;
    }
    FastLED.show();
    lastTime = currentTime;
  }
}




void hillActive() {
  static uint32_t lastTime = 0;
  static uint8_t brightness = 50; // Start brightness at 50 instead of 20
  static int8_t direction = 5;

  uint32_t currentTime = millis();

  if (currentTime - lastTime >= 20) { // 20 milliseconds delay for smoother effect
    brightness += direction;
    // Reverse direction at limits
    if (brightness <= 50 || brightness >= 255) {
      direction = -direction;
    }

    // Define the color
    CRGB color2 = CRGB::Red;

    CRGB currentColor2 = color2;

    // Apply brightness fade
    currentColor2.fadeLightBy(255 - brightness);

    // Set the color based on the brightness
    for (int i = 0; i <= 95; i++) {
      ledsAnts[i] = CRGB::Black;
    }
    for (int i = 96; i <= 125; i++) {
      ledsAnts[i] = currentColor2; // Zone 2 always lightly breathes
    }
    for (int i = 126; i <= 170; i++) {
      ledsAnts[i] = CRGB::Black;
    }
    lastTime = currentTime;
  }
}

void leverForward(){
  const int numLeds = 20;
  static int currentPos = 0;
  static int ticker = 0;

    for (int i = 126; i <= 170; i++) {
      ledsAnts[i] = CRGB::Black;
    }
    if (currentPos == 0){
        currentPos = 9;
    }
    if(currentPos >= 0){
        ledsAnts[125 + currentPos] = CRGB::White;
        ledsAnts[125 + numLeds - currentPos] = CRGB::White;
        if(ticker%3==0){
          currentPos--;
          ticker = 0;
        }
    }
  ticker += 1;
}

void leverBackward(){
  const int numLeds = 20;
  static int currentPos = 0;
  static int ticker = 0;

    for (int i = 125; i <= 170; i++) {
      ledsAnts[i] = CRGB::Black;
    }
    if (currentPos == numLeds/2){
        currentPos = 0;
    }
    if(currentPos < numLeds/2){
        ledsAnts[125 + currentPos] = CRGB::White;
        ledsAnts[125 + numLeds - currentPos] = CRGB::White;
        if(ticker%3==0){
          currentPos++;
          ticker = 0;
        }
    }
  ticker+=1;
}
