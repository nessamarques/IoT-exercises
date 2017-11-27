#include <Servo.h>
#include <Wire.h>
#include "rgb_lcd.h"

#define encoder0PinA  2
#define encoder0PinB  3

rgb_lcd lcd;
Servo myservo;

volatile unsigned int encoder0Pos = 0;

void setup() {
  
  myservo.attach(9);
  lcd.begin(16, 2);

  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);

  attachInterrupt(0, doEncoder, CHANGE);
  Serial.begin (9600);
}

void loop() {}

void doEncoder() {
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
  
    if(encoder0Pos >= 20)
      encoder0Pos = 0;
  } else {
    encoder0Pos--;
    
    if(encoder0Pos <= -1)
      encoder0Pos = 19;
  }

  int degree = encoder0Pos;
    
  Serial.println (encoder0Pos);
  myservo.write((degree + 1) * 9);
}
