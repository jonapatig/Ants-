/// @file    RPM.h
/// @brief   Class to measure RPM

#ifndef RPM
#define RPM

class AntHillLights {
public:
    AntHillLights(int interruptPin);
    void setup();
    void checkResetRPM();
    void countRPM(); 
   

private:
    int interruptPin;
    float RPM;
    int previousInterupt;
}

#endif //RPM
