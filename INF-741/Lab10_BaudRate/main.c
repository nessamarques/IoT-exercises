#include <avr/io.h>
#include <avr/interrupt.h>
#define USART_BAUDRATE 9600 // Defines the baud rate
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1) // Calculate the prescale

int circular_buffer_pop(){
	int ret = 0;
	//TODO: ...
	return ret;
}

int circular_buffer_push() { //UDR0) {
	int ret = 0;
	//TODO: ...
	return ret;
}

int main (void) {

 		/* UART setup */
 		/* .... */
		sei(); // Enable the Global Interrupt Enable flag

 		for (;;) {
			char c;
 			while((c = circular_buffer_pop()) == -1) {} // Wait until circular buffer has data.
			while((UCSR0A & (1<<UDRE0)) == 0 ){} // Wait until the port is ready to be written to
 			UDR0 = c; // Write the byte to the serial port
 		}
}

ISR(USART_RX_vect) { // Interruption function
	circular_buffer_push(); //UDR0); // Push data to circular buffer
}
