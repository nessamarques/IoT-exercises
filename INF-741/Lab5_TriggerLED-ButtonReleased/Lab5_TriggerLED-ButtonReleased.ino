/*
Lab 5: Trigger the LED when the push button is released
Write an Arduino Sketch that turns the on-board LED (pin 13)
ON/OFF when the push button is released!
Hint: You must connect the push button to pin 2.
 */

const byte ledPin =  13;      // LED pin
const byte interruptPin = 2;  // Interrupt pin = PD2 
volatile byte state = LOW; // Current LED state

void setup() {
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING); 
}

// Main program loop
void loop() {
 digitalWrite(ledPin, state);
} 

// Interrupt Service Routine
void blink() {
 state = !state;
}
