#include "MandibleLever.h"

#define leverInput 8
#define leverOutput 9

MandibleLever lever(leverInput, leverOutput);

void setup() {
    lever.begin();
}

void loop() {
    lever.update();
}
