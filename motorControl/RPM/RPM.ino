const int interruptPin = 2;  // Pin 2 is used for the interrupt (depends on the board)
float RPM = 0;
int previousInterupt =0;


void setup() {
  pinMode(interruptPin, INPUT_PULLUP);  // Set the pin as input with internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(interruptPin), countRPM, FALLING);  // Attach the interrupt
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  Serial.println("RPM : " + RPM)
  checkResetRPM()
  delay(50)
}

void checkResetRPM(){
  int currentTime = millis()
  if(currentTime - previousInterupt > 60000){
    RPM = 0
  }
}

void countRPM() {
  int interupt = millis();
  delayMicroseconds(50);          //delay 50 microseconds to prevent accidental triggers
  if(digitalRead(interruptPin)){  //if pin still high stop function
    return ; 
  }
  measuredRPM = (interupt-previousInterupt)/60000 
  RPM = (RPM + measuredRPM)/2 //this is a little lerp filter
  previousInterupt = interupt
}

