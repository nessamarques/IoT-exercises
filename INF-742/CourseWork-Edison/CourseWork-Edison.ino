
#include "rgb_lcd.h"

const byte ledPin =  13;
const byte interruptPin = 7;
volatile byte state = LOW;

rgb_lcd lcd;
SerialLCD slcd(11,12);

void setup() {
  pinMode(ledPin, OUTPUT);
  attachInterrupt(interruptPin, blink, FALLING); 
  
  lcd.begin(16, 2);
   slcd.begin();
  lcd.setRGB(0,255,0);
}

// Main program loop
void loop() {
 digitalWrite(ledPin, state);
 lcd.setRGB(state ? 255 : 0 ,0,0);
 slcd.print(state ? "SAFE" : "INTRUDDER");

} 

// Interrupt Service Routine
void blink() {
 state = !state;
}
