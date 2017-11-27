
#define NOTE_C1  33
#define NOTE_F7  2794

#define INT_MAX_VALUE 2147483647

#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define RX_BUFSIZE 8

#define SLEEPING 0
#define RINGING 1

#define FAIL 0
#define SUCCESS 1
#define ADDED 2

volatile int t0millis;
volatile int t0fraction; 
volatile int turnStartTimestamp;
volatile int timer0debounce;
volatile int timer1debounce;
int buzzerPeriod;
int buzzerDuration;
int buzzerTime;
int buzzerStartTime;
int players;
int roundTurn;

const int overflowInMicrosseconds = 1024;

typedef struct node {
    int val;
    struct node * next;
} node_t;

