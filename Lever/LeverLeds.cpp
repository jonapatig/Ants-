#include "FastLED.h"
#include "LeverLeds.h"

const int numLeds = 20;

int currentPos = 0;

void leverBackward(){
    fasLED.fill_solid(ledsLever, numLeds, CRGB::Black);
    if (currentPos == numLeds/2){
        currentPos = 0;
    }
    if(currentPos < numLeds/2){
        ledsLever[currentPos] = CRGB::White;
        ledsLever[numLeds - currentPos - 1] = CRGB::White;
        currentPos++;
    }
}

void leverForward(){
    fasLED.fill_solid(ledsLever, numLeds, CRGB::Black);
    if (currentPos == 0){
        currentPos = 9;
    }
    if(currentPos <= 0){
        ledsLever[currentPos] = CRGB::White;
        ledsLever[numLeds - currentPos - 1] = CRGB::White;
        currentPos--;
    }
}