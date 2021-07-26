/*
  Motor Control with 3 emergency stops and indicator light.
  
  By Sean Corcoran
  Created 26 Jun 2021
  For Task M1.T4D - SIT315 Concurrent and Distributed Programming
  Deakin University
*/

// Holds the stop and start inputs from the interrupt buttons.
volatile byte stop_a, stop_b, stop_c, start = 0;

// Holds the start of the motor.
volatile bool active = false;

void setup()
{
  // Setup the serial monitor at 9600
  Serial.begin(9600);
  
  // Timer LED Output.
  pinMode(13, OUTPUT);
  
  // Motor control pin output.
  pinMode(12, OUTPUT);
  
  // Interrupt Input Pins
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  

  // No Interrupts during setup. 
  noInterrupts();
  
  // Timer Setup
  
  // Clear any register settings.
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Timer for every 1.33 Seconds
  // 0.75Hz
  
  // Set the compare.
  OCR1A = 20832;

  // Prescaler. (1024)
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // When the compare matches enable the interrupt.
  TIMSK1 |= (1 << OCIE1A);

  // CTC mode on.
  TCCR1B |= (1 << WGM12);
  
  // Input Pin Interrupts
  
  // Turn on port D interrupts
  PCICR |= 0b00000100;
  
  // Enable interrupts on pins (4,5,6,7)
  PCMSK2 |= 0b11110000;
  
  // Reenable interrupts.
  interrupts();
}

void loop()
{
  // If the motor is set to active then output high, else stop.
  if (active) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }
}

// Timer interrupt.
ISR(TIMER1_COMPA_vect) {
  // Write to the the LED pin on timer interrupt. (if motor currently active)
  if (active) {
    digitalWrite(13, digitalRead(13) ^ 1 );
  }
  else {
    digitalWrite(13, LOW);
  }
}

// Pin interrupts.
ISR(PCINT2_vect) {
  // Get the readings from the interrupt pins.
  stop_a = PIND & B10000000;
  stop_b = PIND & B01000000;
  stop_c = PIND & B00100000;
  start = PIND & B00010000;
  
  // If any of the emergency buttons were pressed stop the motor
  if (stop_a > 0 || stop_b > 0 || stop_c > 0) {
    active = false;
    
    // Print stop logs
    Serial.println("Emergency Stop");
    Serial.print("StopBTN_A: ");
    Serial.println(stop_a);
    Serial.print("StopBTN_B: ");
    Serial.println(stop_b);
    Serial.print("StopBTN_C: ");
    Serial.println(stop_c);
    
  } else if (start > 0) {
    active = true; // If the start button was pressed start the motor.
  
    // Print start log. 
    Serial.println("Motor Started"); 
  }
}
