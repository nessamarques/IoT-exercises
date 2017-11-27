/************************************************************************************************************************************************
INF-742 Design and operation principles of cyber-physical systems in the IoT
COURSE WORK 01 - DUTY CYCLE ESTIMATOR

On reset:
	The system will prepare sources of wakeup and, on an infinite loop 
	1.	configure the system to use the lowest possible power sleep mode
	2.	enter sleep mode

On button push:
	1.	The system prints time in milliseconds since boot
	2.	The system prints its estimated duty cycle based on total time and total active time
	3.	The system increments total active time by the appropriate amount 
	4.	The system returns from the ISR and goes back to sleep 

Notes: 
The push button must be connected on pin 2 and the button event must be handled by an ISR (You will need to debounce it).
You must implement a get_time_ms() that will return time in milliseconds since system reset time. In order to maximize sleep time, you need to minimize frequency with which the timer triggers an interrupt. You should therefore NOT generate a timer interrupt every millisecond.  
Your function implementation will have to combine a variable stored in software and the timer counter register. 
You may use the simple_usart library to write to the terminal. You will likely have to include a delay after each print so that the system does not go to sleep before the UART has finished transmitting. 
The program must be designed in C and compiled using the command line tools. You may not use third party code nor libraries.
************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "simple_usart/uart.h"
#include <stdbool.h>

#define IDLE_MODE 0
#define POWER_DOWN_MODE 1
#define POWER_SAVE_MODE 2
#define STANDBY_MODE 3
#define EXT_STANDBY_MODE 4

bool click = false;
volatile long timeSinceBoot;
volatile long activeTime;
volatile long millis;
const float maxValue = 2147483647;
volatile long t0millis;
volatile int t0fraction; 

void set_sleep_mode(char mode) {
	switch (mode) {
		case IDLE_MODE:
		break;
		
		case POWER_DOWN_MODE:
		break;
		
		case POWER_SAVE_MODE:
		break;
		
		case STANDBY_MODE:
		break;
		
		case EXT_STANDBY_MODE:
		break;
	}
}

void sleep_cpu() {
	asm ( "sleep" );
}

void initialize_uart(){
	uart_init();
	stdout = &uart_output;
	stdin  = &uart_input;
}
 
void setup_timer0(){
	TIMSK0 = (1<<TOIE0);
	TCNT0 = 0x00;
	TCCR0B = _BV(CS02) | _BV(CS00);
}
 
void setup_watchDogTimer() {
	if(MCUSR & _BV(WDRF)){
		MCUSR &= ~_BV(WDRF);
		WDTCSR |= (_BV(WDCE) | _BV(WDE));
		WDTCSR = 0x00;
	}

	WDTCSR |= (_BV(WDCE) | _BV(WDE));
	WDTCSR =   _BV(WDIE);
}

ISR(WDT_vect) {
	millis += 16;
}

ISR(TIMER0_OVF_vect){
    t0millis += 16;
	t0fraction += 384;
	
	if(t0fraction >= 1000) {
		t0fraction -= 1000;
		t0millis++;
	}
}

long get_time_ms() {
	return millis;
}

 long get_time_interval(long time) {
	if(time > get_time_ms()){
		return maxValue - time + 1 + get_time_ms();
	}
	else {
		return (get_time_ms() - time);
	}
}

ISR(INT0_vect){	
	// Handle Interrupt
	if(get_time_interval(timeSinceBoot) > 300) {
		timeSinceBoot = get_time_ms();
		activeTime = t0millis + (long)((float)TCNT0 * 0.064);

		printf("\n\n[INFO] Button Pressed!\n");
		click = true;
	}
}

void onButtonPush(){
	printf("*** Time since boot: %ld ms *** \n", timeSinceBoot);
	
	float dutyCycle = ((float)activeTime / (float)timeSinceBoot) * 100;
	printf("*** Duty cycle: %4.2f *** \n", dutyCycle);

	click = false;
}

void onReset(){
	//printf("[INFO] Sleeping...\n");
	set_sleep_mode(POWER_DOWN_MODE);
	sleep_cpu();
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

	// Initialize timer
	setup_timer0();
	setup_watchDogTimer();

	onReset();
	printf("\n\n[INFO] Start!\n");
	
	//Enable global interrupts
	sei();

	while(1) {
		if(click) {
			onButtonPush();
		}
		else {
			onReset();
		}
	}
}