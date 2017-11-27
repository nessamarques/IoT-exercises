/*
Lab 3: Turn on the LED when the push button is pressed
Create an Arduino sketch to turn on the built-in LED when the push button is
pressed and turn it off when the button is released.
You may not use any Arduino function or AVR macro to control the GPIO. Instead,
use load and store instructions to configure and use the GPIO registers.
The on-board LED is connected to PB5 (PIN 13 on the arduino board)
Connect the push button to PB0 (PIN 8 on the arduino board)
*/

volatile char* ddrB = (char*) 0x024;   // points ddrB variable to the DDRB register address
volatile char* pinB = (char*) 0x023;   // You should tell to compiler that
volatile char* portB = (char *) 0x025; // the value of the PINB may change at any time
bool read_value = false;

void setup() {
  *ddrB  |=  (1 << 5);  //Configura o led - Pino 8 da porta B - Saída
  *ddrB  &= ~(1 << 0);  //Configura o botão - Pino 0 da porta B - Entrada
  *portB &= ~(1 << 5);  //Apaga o LED
}

void loop() {
  
  read_value = *pinB & (1 << 0); //Lê o valor do pino de entrada - Pino 0
  
  if(read_value)
  {
    *portB |= (1 << 5); //Acende o LED
  }
  else
  {
    *portB &= ~(1 << 5);  //Apaga o LED
  }
}


