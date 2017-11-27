/*
Reaction timer: You must design and implement a system using Arduino Uno to measure the user reaction time and write it on the terminal. 

On reset:
- The system turns the LED off. OK!
- The system writes "Press button to start" OK!
- After pressing the button, the system starts the game. OK!

During the game: 
1) The system waits for a random time (between 1 and 3 seconds)  and turns the LED on.
2) The system waits for the user to press the button. OK!
3) Once the user press the button, the system measures the time elapsed between the moment the LED was turned on and the moment the user pressed the button and writes the following 
message on the terminal: "Reaction time = XXX ms", where XXX is the time in milliseconds. Once the message is printed, the system goes to the next round.
4) If the user presses the button before the LED turns on, the system prints "Too early" and goes to the next round.
5) If the user takes too long to press the button (5s), the system prints "Time out" and resets. 

The push button must be connected on pin 2 and the button event must be handled by an ISR (You may need to debounce it).
The timer must be configured to update a global variable (named milliseconds) that keeps the number of milliseconds elapsed since the system was turned on. The variable type must 
be an "int". 
You must implement both the millis() and micros() functions. The millis() function returns the contents of the milliseconds variable. The micros() function must combine the value 
from the milliseconds variable and the value stored on the timer counter register.
You may use the simple_usart library to write to the terminal. In your code, include stdio.h and the given uart.h. To use the UART initialize it with the code:

uart_init();
stdout = &uart_output;
stdin  = &uart_input;

After initializing the UART, you can use printf, puts, and getchar.
The library and a small example is available on moodle.
*/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "simple_usart/uart.h"

volatile unsigned long tMillis;
unsigned long firstClickTime ;
unsigned long currentClick;
unsigned long lastClick;

int minTime = 0; //Random time
int maxTime = 5000; //Max time allowed - 5 seconds
int minRndValue = 1000; // Minimum possible value allowed for minTime.
int maxRndValue = 3000; // Maximum possible value allowed for minTime.

bool playing = false;

unsigned long millis() {
    return tMillis;
}

unsigned long micros() {
    return tMillis/1000;
}

void onReset()
{
	printf("[INFO] onReset\n");
	
	//Select a random value between 1 and 3 seconds
	minTime = ((rand() % (maxRndValue + 1 - minRndValue ) + minRndValue));
   
	printf("[INFO] Turns the LED off\n");
	PORTB = 0x00; // Set output pins as LOW (LED OFF)

	firstClickTime = 0;
	currentClick = 0;
	lastClick = 0;
	
	printf("\n*** PRESS BUTTON TO START! ***\n\n");
}

// Time interrupts
ISR (TIMER1_COMPA_vect) {
	tMillis++;
}

void startGame()
{
	printf("[INFO] Button pressed\n");
	playing = true;
	
	// First click
	if(firstClickTime == 0)
	{
		firstClickTime = millis();
		
		printf("[INFO] Turns the LED ON\n");
		PORTB = 0xFF; // Set output pins as HIGH (LED ON)
		
		printf("[INFO] GAME STARTED!\n");
	}
	else
	{
		int diff = currentClick - firstClickTime;
	
		printf("\n*** REACTION TIME: %ld ms ***\n\n", currentClick);
		
		if(diff < minTime)
		{
			printf("\n*** TOO EARLY ***\n\n");
		}
		else if ((diff >= minTime) && (diff < maxTime)) {
			printf("[INFO] OK!\n");
		}
		else if(diff >= maxTime)
		{
			printf("\n*** TIMEOUT ***\n\n");
			onReset();
		}
	}
}

// Button interrupts
ISR (INT0_vect) {
	
	lastClick = currentClick;	
	currentClick = millis();
	
	if(firstClickTime == 0)
	{
		startGame();
	}
	else
	{
		if(lastClick != currentClick)
		{
			startGame();
		}
	}
}

int main( void ) {

	// Initialize UART
	uart_init();
	stdout = &uart_output;
	stdin  = &uart_input;
	
	srand((unsigned)time(NULL));
	
	cli(); // stop interrups
	
	DDRB = 0xFF; // Configure PORTB as output
	DDRD &= ~(1 << DDD2); // PD2 (PCINT0 pin) is now an input
	PORTD |= (1 << PORTD2); // PD2 is now with pull-up enabled
	EICRA &= ~(1 << ISC00); // set INT0 to trigger on
	EICRA |= (1 << ISC01); // FALLING edge (ISC0 = 01)
	EIMSK |= (1 << INT0); // Allow INT0 interrupts
	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
	TCNT1 = 0;
	OCR1A = 0xFA;
	TIMSK1 |= (1 << OCIE1A);
	
	sei(); // start interrupts
	
	onReset();
	
	while(1) {
		
		if(playing)
		{
			if(( currentClick - firstClickTime) >= maxTime)
			{
				printf("\n*** TIMEOUT ***\n\n");
				onReset();
			}
		}
	} 
}
