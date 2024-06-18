#include "RPM/RPM.h"
#define motorApwm 6
#define motorAin1 5
#define motorAin2 4
#define RPMcounterInertupt 2

RPMcounter RPM(RPMcounterInertupt);

float setRPM = 0;

//PID params
float Kbase = 1;
float Kp= 1;
float Ki = 1;
float Kd = 1;

int motorSpeedController(float setRPM, float measuredRPM){
  int controlValue = Kbase*setRPM
  float error = setRPM- measuredRPM
  controlValue += error*Kp
  return  constrain(controlValue, 0, 255)
}

void setMotorDirection(int in1, int in2, bool direction=false){
  digitalWrite(in1, direction);
  digitalWrite(in2, !direction);
}

void setupMotor(int pwm, int in1,  int in2){
  pinMode(pwm, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // call change motor direction without specifying direction to turn on motor on init direction
  setMotorDirection(in1, in2);
}


void setup() {
  // put your setup code here, to run once:
  setupMotor(motorApwm, motorAin1, motorAin2);
  RPMcounter.setup()
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  RPMcounter.checkResetRPM();
  if(Serial.available()){
    setRPM = Serial.read();
  }  
  analogWrite(motorApwm, motorSpeedController(RPMcounter.RPM))
  Serial.println(setRPM + ", " + RPMcounter.RPM )
  delay(50);
}
