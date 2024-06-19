/// @file    RPMclass.h
/// @brief   Class to measure RPM

#ifndef RPMCLASS_H
#define RPMCLASS_H

class RPMclass {
public:
    RPMclass(int interruptPin);
    void setup();
    void checkResetRPM();
    static void countRPM();  // Make this method static
    float getRPM();  // Return type should be float
    bool getInterruptFlag();  // Method to get the interrupt flag

private:
    int interruptPin;
    static RPMclass* instance;  // Static pointer to the instance
    int previousInterrupt;  // Corrected typo
    float RPM;
    static volatile bool interruptFlag;  // Static volatile interrupt flag
};

#endif // RPMCLASS_H
