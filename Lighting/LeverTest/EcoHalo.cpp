#include "FastLED.h"
#include "EcoHalo.h"

const int numLeds = 96;
const int spotSize = 13;
const int slowDownValue = 4;


int randPos(){
    const int MIN_VALUE = spotSize/2;
    const int MAX_VALUE = numLeds - spotSize/2;
    
    return (rand() % (MAX_VALUE - MIN_VALUE + 1 )) + MIN_VALUE;
}

void runHalo(int numSad) {
  static int fullBrightness = 70;
  static int counter = 0;
  static bool raise = false;
  static int ledsBright[numLeds];
  static int colorOffset[numLeds];
  if (int(random(0, numSad)) == 0) {
        int selectedLed = int(random(0, numLeds));
        ledsBright[selectedLed] = 255;
        colorOffset[selectedLed] = random(-10,15);
      }
  fill_solid(ledsHalo, numLeds, CHSV(96,255,fullBrightness) );

  for (int i = 0; i < numLeds; i++) {
    if (ledsBright[i] > 0) { 
      ledsBright[i]-=3;
      ledsHalo[i] = CHSV(80 + colorOffset[i], 255, ledsBright[i]);
    }
  }
}

void fullEco(){
  runHalo(1);
}
void damagedEco1(){
  runHalo(5);
}
void damagedEco2(){
  runHalo(10);
}

// void fullEco() {
//   const int numSpots = 15;
//   static int spotPos[numSpots] = {0};
//   static int timeAlive[numSpots] = {0};
//   static int hueChange[numSpots] = {0};
//   if(spotPos[0] == 0){
//     for(int i=0; i<numSpots; i++){
//       spotPos[i] = randPos();
//       timeAlive[i] += random(0,spotSize/2+1);
//       hueChange[i] = random(-15,5);
//     }
//   }

//   fill_solid(ledsHalo, numLeds, CHSV(96,255,75) );

//   for(int i=0; i<numSpots; i++){
//     for(int k=0; k<=spotSize/2; k++){
//       if(k == (timeAlive[i])/slowDownValue){
//         ledsHalo[spotPos[i]+k] = CHSV(96+hueChange[i],255,75+(180*(timeAlive[i]/(spotSize/2))));
//         ledsHalo[spotPos[i]-k] = CHSV(96+hueChange[i],255,75+(180*(timeAlive[i]/(spotSize/2))));
//       }
//       else{
//         ledsHalo[spotPos[i]+k] += CHSV(96+hueChange[i],255,75);
//         ledsHalo[spotPos[i]-k] = CHSV(96+hueChange[i],255,75);
//       }
//     }
//     timeAlive[i]++;
//     if (timeAlive[i]/slowDownValue == spotSize/2){
//       timeAlive[i] = random(0,2);
//       spotPos[i] = randPos();
//       hueChange[i] = random(-15,5);
//     }
//   }
// }

// void damagedEco1() {
//   const int numSpots = 10;
//   // Serial.print(numSpots);
//   static int spotPos[numSpots] = {0};
//   static int timeAlive[numSpots] = {0};
//   static int hueChange[numSpots] = {0};
//   if(spotPos[0] == 0){
//     for(int i=0; i<numSpots; i++){
//       spotPos[i] = randPos();
//       timeAlive[i] += random(0,spotSize/2+1);
//       hueChange[i] = random(-15,5);
//     }
//   }

//   fill_solid(ledsHalo, numLeds, CHSV(96,255,75) );

//   for(int i=0; i<numSpots; i++){
//     for(int k=0; k<=spotSize/2; k++){
//       if(k == (timeAlive[i])/slowDownValue){
//         ledsHalo[spotPos[i]+k] = CHSV(96+hueChange[i],255,75+(180*(timeAlive[i]/(spotSize/2))));
//         ledsHalo[spotPos[i]-k] = CHSV(96+hueChange[i],255,75+(180*(timeAlive[i]/(spotSize/2))));
//       }
//       else{
//         ledsHalo[spotPos[i]+k] += CHSV(96+hueChange[i],255,75);
//         ledsHalo[spotPos[i]-k] = CHSV(96+hueChange[i],255,75);
//       }
//     }
//     timeAlive[i]++;
//     if (timeAlive[i]/slowDownValue == spotSize/2){
//       timeAlive[i] = random(0,2);
//       spotPos[i] = randPos();
//       hueChange[i] = random(-15,5);
//     }
//   }
// }

// void damagedEco2() {
//   const int numSpots = 5;
//   static int spotPos[numSpots] = {0};
//   static int timeAlive[numSpots] = {0};
//   static int hueChange[numSpots] = {0};
//   if(spotPos[0] == 0){
//     for(int i=0; i<numSpots; i++){
//       spotPos[i] = randPos();
//       timeAlive[i] += random(0,spotSize/2+1);
//       hueChange[i] = random(-15,5);
//     }
//   }

//   fill_solid(ledsHalo, numLeds, CHSV(96,255,75) );

//   for(int i=0; i<numSpots; i++){
//     for(int k=0; k<=spotSize/2; k++){
//       if(k == (timeAlive[i])/slowDownValue){
//         ledsHalo[spotPos[i]+k] = CHSV(96+hueChange[i],255,75+(180*(timeAlive[i]/(spotSize/2))));
//         ledsHalo[spotPos[i]-k] = CHSV(96+hueChange[i],255,75+(180*(timeAlive[i]/(spotSize/2))));
//       }
//       else{
//         ledsHalo[spotPos[i]+k] += CHSV(96+hueChange[i],255,75);
//         ledsHalo[spotPos[i]-k] = CHSV(96+hueChange[i],255,75);
//       }
//     }
//     timeAlive[i]++;
//     if (timeAlive[i]/slowDownValue == spotSize/2){
//       timeAlive[i] = random(0,2);
//       spotPos[i] = randPos();
//       hueChange[i] = random(-15,5);
//     }
//   }
// }
