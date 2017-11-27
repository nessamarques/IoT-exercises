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

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "simple_usart/uart.h"
#include <stdbool.h>

void initialize_uart(){
	uart_init();
	stdout = &uart_output;
	stdin  = &uart_input;
}
 
ISR(WDT_vect) {
}

ISR(INT0_vect){
	printf("[INFO] Button pressed!")
}

int main(void)
{
	// Stop interrups
	cli();
	
	// Initialize UART
	initialize_uart();
	
	//Initialize LED port
	DDRB = 0xFF;
	PORTB = 0x00;
	
	//Interrupt button
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PORTD2);
	EIMSK = 1<<INT0;
	EICRA = 1<<ISC00 | 1<<ISC01;

	onReset();
	printf("\n\n[INFO] Start!\n");
	
	//Enable global interrupts
	sei();

	while(1) {
	}
}