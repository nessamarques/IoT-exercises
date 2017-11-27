#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "declareGlobal.h"

volatile uint8_t buzzerState = SLEEPING;
volatile uint8_t state = 0;
volatile uint8_t buttonPressed;
volatile uint8_t whichButtonPressed;

void uart_putchar(char c, FILE *stream) {
  if (c == '\a') {
      fputs("*ring*\n", stderr);  
      return;
    }

  if (c == '\n') {
    uart_putchar('\r', stream);
  }
  
  while ((UCSR0A & (1 << UDRE0)) == 0) {}
  
  UDR0 = c;
}

char uart_getchar(FILE *stream) {
    uint8_t c;
    char *cp, *cp2;
    static char b[RX_BUFSIZE];
    static char *rxp;

    if (rxp == 0)
    
      for (cp = b;;) {
        while ((UCSR0A & (1 << RXC0)) == 0 ){}
      
      	if (UCSR0A & _BV(FE0)) {
            return _FDEV_EOF;
        }
        
        if (UCSR0A & _BV(DOR0)) {
              return _FDEV_ERR;
        }
        
      	c = UDR0;
        
      	if (c == '\r') {
        	c = '\n';
        }
          
      	if (c == '\n') {
            *cp = c;
            uart_putchar(c, stream);
            rxp = b;
            break;
        } else if (c == '\t'){
            c = ' ';
      }

        if ((c >= (uint8_t)' ' && c <= (uint8_t)'\x7e') || c >= (uint8_t)'\xa0') {
            if (cp == b + RX_BUFSIZE - 1) {
                uart_putchar('\a', stream);
            } else {
                *cp++ = c;
                uart_putchar(c, stream);
            }
            continue;
        }

        switch (c) {
            case 'c' & 0x1f:
                return -1;

            case '\b':

            case '\x7f':
                if (cp > b) {
                    uart_putchar('\b', stream);
                    uart_putchar(' ', stream);
                    uart_putchar('\b', stream);
                    cp--;
                }
            break;

            case 'r' & 0x1f:
                uart_putchar('\r', stream);
                for (cp2 = b; cp2 < cp; cp2++) {
                    uart_putchar(*cp2, stream);
                }
            break;

            case 'u' & 0x1f:
                while (cp > b) {
                    uart_putchar('\b', stream);
                    uart_putchar(' ', stream);
                    uart_putchar('\b', stream);
                    cp--;
                }
            break;

            case 'w' & 0x1f:
            while (cp > b && cp[-1] != ' ')  {
                    uart_putchar('\b', stream);
                    uart_putchar(' ', stream);
                    uart_putchar('\b', stream);
                    cp--;
                }
            break;
        }
    }
    
  	c = *rxp++;
    
  	if (c == '\n') {
    	rxp = 0;
    }
  
    return c;
}

void resetPlayers(node_t ** head, int players) {
    node_t * current;
    
  	if (*head != NULL) {
        current = *head;
        while (current->next != NULL) {
            node_t * aux = current;
            current = current->next;
            free(aux);
        }
        free(current);
    }   
    
  	current = malloc(sizeof(node_t));
    current->val = 1;
    current->next = NULL;
    *head = current;
    
  	int i = 2;
    
  	while (i <= players) {
        current->next = malloc(sizeof(node_t));
        current->next->val = i;
        current->next->next = NULL;
        current = current->next;
        i++;
    }
}

void removePlayer(node_t ** head, node_t * player) {
    node_t * previous = NULL;
    node_t * current = *head;
    
  	while (current != NULL) {
        if (current == player) {
            if (previous == NULL) {
                *head = player->next;
            } else {
                previous->next = player->next;
            }
            free(player);
            break;
        }
        previous = current;
        current = current->next;
    }
}

void resetNotes(node_t ** head) {
    node_t * current;
    if (*head != NULL) {
        current = *head;
        while (current->next != NULL) {
            node_t * aux = current;
            current = current->next;
            free(aux);
        }
        free(current);
    }
    *head = NULL;
}

int verifyNote(node_t ** head, node_t * currentNote, int note) {
    if (currentNote == NULL) {
        node_t * aux;
        aux = malloc(sizeof(node_t));
        aux->val = note;
        aux->next = NULL;
        if (*head == NULL) {
            *head = aux;
        } else {
            node_t * current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = aux;
        }
        return ADDED;
    } else {
        if (currentNote->val == note) {
            return SUCCESS;
        } else {
            return FAIL;
        }
    }
}

node_t * playersHead = NULL;
node_t * currentPlayer = NULL;
node_t * notesHead = NULL;
node_t * currentNote = NULL;
 
int millis() {
    return t0millis;
}

uint32_t micros() {
    return (uint32_t)t0millis * 1000UL + (uint32_t)t0fraction + (uint32_t)TCNT0 * 4;
}

int getTimeInterval(int t) {
    if (t > millis()){
        return INT_MAX_VALUE - t + 1 + millis();
    } else {
        return (millis() - t);
    }
}

// Int Timer0
ISR(TIMER0_OVF_vect){
    t0millis++;
    t0fraction += 24;
    if (t0fraction >= 1000) {
        t0fraction -= 1000;
        t0millis++;
    }
}

// Play sound
void playTone(int frequency, int duration) {
    buzzerState = RINGING;
    buzzerTime = millis();
    buzzerStartTime = millis();
    buzzerPeriod = 1/(float)frequency * 1000.f;
    buzzerDuration = duration;
}

// Button click
ISR(INT0_vect) {
    if (getTimeInterval(timer0debounce) > 300) {
        buttonPressed = 1;
        whichButtonPressed = 0;
        playTone(NOTE_C1, 400);
        timer0debounce = millis();
    }
}

// Button click
ISR(INT1_vect) {
    if (getTimeInterval(timer1debounce) > 300) {
        buttonPressed = 1;
        whichButtonPressed = 1;
        playTone(NOTE_F7, 400);
        timer1debounce = millis();
    }
}

void setupInterruptButton() {
    DDRD &= ~((1<<PD2) | (1<<PD3));
    PORTD |= (1 << PORTD2) | (1<<PORTD3);
    EIMSK = 1<<INT0 | 1<<INT1;
    EICRA = 1<<ISC01 | 1<<ISC00 | 1<<ISC10 | 1<<ISC11;
}

void setupTimer0() {
    TIMSK0=(1<<TOIE0);
    TCNT0=0x00;
    TCCR0B = 1<<CS01 | 1<<CS00;
}

int main(void) {
  
    // Stop interrups
    cli();
    
    // Initialize Uart
    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
    UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
    UBRR0H = (BAUD_PRESCALE >> 8);
    UBRR0L = BAUD_PRESCALE;
    FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
    stdout = stdin = &uart_str;

    //Led pin
    DDRB = 0xFF;
    PORTB = 0x00;
    
    setupInterruptButton();

    setupTimer0();
    
    //Enable global interrupts  
    sei();

    while(1) {
        
        //Buzzer state machine
        switch(buzzerState) {
            case SLEEPING:
            break;
            case RINGING:
            if (getTimeInterval(buzzerTime) > buzzerPeriod) {
                buzzerTime = millis();
                PORTB = ~PORTB;
            }
            if (getTimeInterval(buzzerStartTime) > buzzerDuration) {
                PORTB = 0x00;
                buzzerState = SLEEPING;
            }
            break;
        }
        
        switch(state) {
            case 0:
                printf("\n\n******************************\n");
                printf("*** Follow the leader game ***\n");
                printf("******************************\n\n");
            
                printf("-> Welcome to the follow the leader game! Please enter the number of players: [2-9] \n");
                state = 1;
            break;
        
            case 1:
                if (scanf("%d", &players) == 1 && players > 1 && players < 10) {
                    resetPlayers(&playersHead, players);
                    resetNotes(&notesHead);
                    roundTurn = 1;
                    state = 2;                
                } else {
                    printf("Wrong input.\n");
                }               
            break;
            
            case 2:
                printf("\n\n-> ROUND %d\n", roundTurn);
                roundTurn++;
                currentPlayer = playersHead;
                state = 3;
            break;
            
            case 3:
                currentNote = notesHead;
                turnStartTimestamp = millis();
                printf("-> Player %d\n", currentPlayer -> val);
                state = 4;
            break;
            
            case 4:
                if (getTimeInterval(turnStartTimestamp) > 5000) {
                    printf("\n\n-> Time expired. You have been eliminated! \n");
                    state = 6;
                } else if (buttonPressed) {
                    buttonPressed = 0;
                    switch(verifyNote(&notesHead, currentNote, whichButtonPressed)) {
                        case FAIL:
                            state = 5;
                        break;
                        case SUCCESS:
                            currentNote = currentNote -> next;
                        break;
                        case ADDED:
                            state = 7;
                        break;
                    }
                    turnStartTimestamp = millis();
                }
            break;
            
            case 5:
                printf("-> Incorrect sequence! You have been eliminated.\n");
            
            case 6:;
                node_t * aux = currentPlayer;
                if (currentPlayer->next == NULL) {
                    state = 2;
                } else {                    
                    currentPlayer = currentPlayer->next;                    
                    state = 3;
                }
                removePlayer(&playersHead, aux);
                if (playersHead -> next == NULL) {
                    printf("-> Player %d won!\n", playersHead -> val);
                    state = 0;
                }
            break;
            
            case 7:
                if (currentPlayer -> next == NULL) {
                    state = 2;
                } else {                    
                    currentPlayer = currentPlayer -> next;                    
                    state = 3;
                }
            break;
        }
    }
}
