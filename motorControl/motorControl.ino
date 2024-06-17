#define motorApwm 6
#define motorAin1 5
#define motorAin2 4

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
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 255; i+=1){
    analogWrite(motorApwm, i);
    delay(100);
    Serial.print(i);
  }
}
