/*
  Basic Sense Act Think Alarm - Using an Interrupt.
  
  By Sean Corcoran
  Created 22 Jun 2021
  For Task M1.T2P - SIT315 Concurrent and Distributed Programming
  Deakin University 
*/
// Define input and output pins 
#define LED 4
#define BUZZ 5
#define MOTION 2

void setup() {
  // Initialize digital pin LED and BUZZER pins to output and motionInput to input.
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  // Attached interrupt to trigger the alarm ISR.
  attachInterrupt(digitalPinToInterrupt(2), raiseTheAlarm_ISR, CHANGE);

  // Setup the serial monitor at 9600
  Serial.begin(9600);

}

void loop() {
}

void raiseTheAlarm_ISR() {
  // If the motion pin reads as high, motion has been detected if not then no motion  
  if (digitalRead(MOTION) == HIGH) {
    // Turn on the LED and play tone.
    digitalWrite(LED, HIGH);
    tone(BUZZ, 85);
    
    // Output the motion state to the serial monitor.
    Serial.println("Motion");
  }
  else {
    // Turn off the LED and stop tone.
    digitalWrite(LED, LOW);
     noTone(BUZZ);
     
    // Output the motion state to the serial monitor.
    Serial.println("No Motion");
  }
}
