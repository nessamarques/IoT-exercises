/*******************************************************************************************************************************************************
LAB Activity 1 - Connect two Arduinos using SPI

• Button press in the master changes the LED in the slave
• Use the Arduino library for master implementation
• You can implement the slave in Arduino, but you’ll need to interact directly with the peripheral through the memory-mapped registers (see schematic)
• Advanced version (1.1)
• Use different select pins to connect with more than one Arduino slave
• Relay commands received through the serial terminal to each slave
• May require you to splice wires
• Advanced version (1.2)
• Ditch the Arduino library and implement your own setup/transmission/reception functions (this is very easy with SPI!)

*******************************************************************************************************************************************************/

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
