/*
  Basic Sense Act Think Alarm - With Manual Overridet.
  
  By Sean Corcoran
  Created 22 Jun 2021
  For Task M1.T3C - SIT315 Concurrent and Distributed Programming
  Deakin University 
*/
// Define input and output pins 
#define LED 4
#define BUZZ 5
#define MOTION 2

// Holds the state of the alarm.
volatile bool alarmActive = false;

void setup() {
  // Initialize digital pin LED and BUZZER pins to output and motionInput to input.
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  // Attached interrupts to trigger the alarm ISR.
  attachInterrupt(digitalPinToInterrupt(2), raiseTheAlarm_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), manualToggleAlarm_ISR, FALLING); 
  
  // Setup the serial monitor at 9600
  Serial.begin(9600);
}

void loop() {
}

// Raise the alarm with motion
void raiseTheAlarm_ISR() {
  // If the motion pin reads as high, motion has been detected if not then no motion  
  if (digitalRead(MOTION) == HIGH) {
    alarmOn();
    // Output the motion state to the serial monitor.
    Serial.println("Motion");
    
  } 
  else {
    alarmOff();
    // Output the motion state to the serial monitor.
    Serial.println("No Motion");
  }
}

// Manually Toggle the alarm on and off
void manualToggleAlarm_ISR() {
  if (!alarmActive) {
    alarmOn();
    Serial.println("Alarm Toggled");
}
  else {
    alarmOff();
    Serial.println("Alarm Stopped");
  }
}

// Trigger the alarm on.
void alarmOn() {
  // Set alarm to active.
    alarmActive = true;
  
  // Turn on the LED and play tone.
    digitalWrite(LED, HIGH);
    tone(BUZZ, 85); 
}

// Trigger the alarm off.
void alarmOff() {
  // Set alarm to inactive.
    alarmActive = false;
  
  // Turn off the LED and stop tone.
    digitalWrite(LED, LOW);
    noTone(BUZZ);
}
