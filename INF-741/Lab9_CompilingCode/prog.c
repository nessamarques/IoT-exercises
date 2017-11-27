#include <avr/io.h>
#define LED PB5
void delay_ms(uint8_t ms) {
 uint16_t delay_count = 1000000 / 17500;
 volatile uint16_t i;

 while (ms != 0) {
 for (i=0; i != delay_count; i++);
 ms--;
 }
}
int main(void) {
 int i = 0;
 DDRB = 0xFF;
 for(;;) {
 PORTB = 0xFF;
 for (i =0; i<10; i++){
 delay_ms(200);
 }
 PORTB = 0;
 for (i =0; i<10; i++){
 delay_ms(200);
 }
 }

 return 0;
}