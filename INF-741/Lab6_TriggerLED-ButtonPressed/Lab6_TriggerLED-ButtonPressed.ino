/*
Lab 6: Trigger the LED when the push button is pressed
Change your Arduino Sketch to:
turn the LED when the push button is pressed instead of
pushed.
 */

const byte ledPin =  13;      // LED pin
const byte interruptPin = 2;  // Interrupt pin = PD2 
volatile byte state = LOW; // Current LED state

void setup() {
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING); 
}

// Main program loop
void loop() {
 digitalWrite(ledPin, state);
} 

// Interrupt Service Routine
void blink() {
 state = !state;
}
