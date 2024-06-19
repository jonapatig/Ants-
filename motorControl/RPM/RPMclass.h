/// @file    RPMclass.h
/// @brief   Class to measure RPM

#ifndef RPMclass_H
#define RPMclass_H

class RPMclass {
public:
    RPMclass(int interruptPin);
    void setup();
    void checkResetRPM();
    void countRPM();
    float getRPM();  // Return type should be float

private:
    int interruptPin;
    int previousInterrupt;  // Corrected typo
    float RPM;
};

#endif // RPMclass_H
