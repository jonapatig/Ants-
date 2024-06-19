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
    void getRPM(); 
    
   

private:
    int interruptPin;
    int previousInterupt;
    float RPM;
}

#endif //RPM
