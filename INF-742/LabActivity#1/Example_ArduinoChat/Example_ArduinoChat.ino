/*
  Lab 8: Arduino Chat
  Use the software serial to connect two arduinos so that they
  echo messages from one PC terminal to another. 
*/

#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11

// set up a new serial port
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

void setup() {

 // define pin modes for tx, rx:
 pinMode(rxPin, INPUT);
 pinMode(txPin, OUTPUT);

 Serial.begin(9600);
 mySerial.begin(9600);

}

void loop() {

  if(mySerial.available()) {
    Serial.println(mySerial.readString());
  }

  if(Serial.available()) {
    mySerial.println(Serial.readString());
  }  
} 
