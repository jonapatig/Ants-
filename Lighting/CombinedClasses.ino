#include "AntHillLights.h"
#include "LEDControlCircle.h"
#define Ant_NUM_LEDS 133
#define Ant_DATA_PIN 4
#define Vine_NUM_LEDS 96
#define Vine_DATA_PIN 3
// Corrected array definition
//  CRGB::Aquamarine, CRGB::Chartreuse, CRGB::Crimson, CRGB::Wheat,CRGB::SpringGreen,CRGB::Salmon,CRGB::Plaid,CRGB::PaleGreen,CRGB::Navy,CRGB::Orange, CRGB::Gold,CRGB::Goldenrod,, CRGB::Tomato, CRGB::Sienna, CRGB::Purple,CRGB::PaleVioletRed

CRGB color_array[] = {CRGB( 255, 125, 0),CRGB::Aquamarine, CRGB::Chartreuse, CRGB::Crimson, CRGB::Wheat,CRGB::SpringGreen,CRGB::Salmon,CRGB::Plaid,CRGB::PaleGreen,CRGB::Navy,CRGB::Orange, CRGB::Gold,CRGB::Goldenrod, CRGB::Tomato, CRGB::Sienna, CRGB::Purple,CRGB::PaleVioletRed};


AntHillLights ZoneControl(Ant_NUM_LEDS, Ant_DATA_PIN);
LEDControlCircle ledControl(Vine_NUM_LEDS, Vine_DATA_PIN);

void setup() {
    ZoneControl.setup();
    ledControl.setup();
}

void loop() {

    ZoneControl.setColorInZone(1, CRGB::Black);
    ZoneControl.setColorInZone(2, CRGB::Black);
    ZoneControl.setColorInZone(3, CRGB::Black);
    ledControl.setColor(0, 359, CRGB::Black);
    int numColors = sizeof(color_array) / sizeof(color_array[0]);
    float segmentSize = 359.0 / numColors;

    for (int i = 0; i < numColors; i++) {
        float startDegree = i * segmentSize;
        float endDegree = startDegree + segmentSize;
        // Ensure we don't exceed 360 degrees
        endDegree = endDegree > 359.0 ? 359.0 : endDegree;

        // Pulse each segment with the corresponding color
        // ledControl.pulseColor(startDegree, endDegree, color_array[i], 2000);
        ledControl.fadeColor(startDegree,endDegree, color_array[i],500);
        ZoneControl.fadeColorInZone(i%3, color_array[i],500);
        delay(20); // Wait for 1 second between segments
    }
    delay(1000);
    // Optional: Clear all LEDs after completing the sequence
    ledControl.setColor(0, 359, CRGB::Black);
}