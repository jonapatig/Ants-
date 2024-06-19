/// @file    RPM.h
/// @brief   Class to measure RPM

#ifndef RPM
#define RPM

class RPM {
public:
    RPM(int interruptPin);
    void setup();
    void checkResetRPM();
    void countRPM();
    float getRPM(); 
    
   

private:
    int interruptPin;
    int previousInterrupt;  // Corrected typo
    float RPM;
}

#endif //RPM
