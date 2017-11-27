/*
  Lab 4: Trigger the Morse code using a push button

  Modify your Morse Code sketch to trigger the message when the push button is pressed.
  Once pressed send entire message.
  Once the message is sent, wait for the user to press the push button again to send the message again.
  
  modified 7 Oct 2016
  by Vanessa Marques
*/

const int unit = 150;
const int dot = unit;
const int dash = 3 * unit;
const int space = unit;
const int space_letters = 3 * unit;
const int space_words = 7 * unit;


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
    writeMorseCode();   
  }
}

void writeMorseCode(){
  char msg[] = {'H', 'E', 'L', 'L', 'O', ' ', 'I', 'O', 'T', ' ', 'W', 'O', 'R', 'L', 'D'};
  
  for (int i = 0; i < 15; i++)
  {
      char c = msg[i];
  
      if(c == 'A'){fnWrite(dot);  fnWrite(dash);  delay(space_letters);}
      if(c == 'B'){fnWrite(dash); fnWrite(dot);   fnWrite(dot);   fnWrite(dot);   delay(space_letters);}
      if(c == 'C'){fnWrite(dash); fnWrite(dot);   fnWrite(dash);  fnWrite(dot);   delay(space_letters);}
      if(c == 'D'){fnWrite(dash); fnWrite(dot);   fnWrite(dot);   delay(space_letters);}
      if(c == 'E'){fnWrite(dot);  delay(space_letters);}
      if(c == 'F'){fnWrite(dot);  fnWrite(dot);   fnWrite(dash);  fnWrite(dot);   delay(space_letters);}
      if(c == 'G'){fnWrite(dash); fnWrite(dash);  fnWrite(dot);   delay(space_letters);}
      if(c == 'H'){fnWrite(dot);  fnWrite(dot);   fnWrite(dot);   fnWrite(dot);   delay(space_letters);}
      if(c == 'I'){fnWrite(dot);  fnWrite(dot);   delay(space_letters);}
      if(c == 'J'){fnWrite(dot);  fnWrite(dash);  fnWrite(dash);  fnWrite(dash);  delay(space_letters);}
      if(c == 'K'){fnWrite(dash); fnWrite(dot);   fnWrite(dash);  delay(space_letters);}
      if(c == 'L'){fnWrite(dot);  fnWrite(dash);  fnWrite(dot);   fnWrite(dot);   delay(space_letters);}
      if(c == 'M'){fnWrite(dash); fnWrite(dash);  delay(space_letters);}
      if(c == 'N'){fnWrite(dash); fnWrite(dot);   delay(space_letters);}
      if(c == '0'){fnWrite(dash); fnWrite(dash);  fnWrite(dash);  delay(space_letters);}
      if(c == 'P'){fnWrite(dot);  fnWrite(dash);  fnWrite(dash);  fnWrite(dot);   delay(space_letters);}
      if(c == 'Q'){fnWrite(dash); fnWrite(dash);  fnWrite(dot);   fnWrite(dash);  delay(space_letters);}
      if(c == 'R'){fnWrite(dot);  fnWrite(dash);  fnWrite(dot);   delay(space_letters);}
      if(c == 'S'){fnWrite(dot);  fnWrite(dot);   fnWrite(dot);   delay(space_letters);}
      if(c == 'T'){fnWrite(dash); delay(space_letters);}
      if(c == 'U'){fnWrite(dot);  fnWrite(dot);   fnWrite(dash);  delay(space_letters);}
      if(c == 'V'){fnWrite(dot);  fnWrite(dot);   fnWrite(dot);   fnWrite(dash);  delay(space_letters);}
      if(c == 'W'){fnWrite(dot);  fnWrite(dash);  fnWrite(dash);  delay(space_letters);}
      if(c == 'X'){fnWrite(dash); fnWrite(dot);   fnWrite(dot);   fnWrite(dash);  delay(space_letters);}
      if(c == 'Y'){fnWrite(dash); fnWrite(dot);   fnWrite(dash);  fnWrite(dash);  delay(space_letters);}
      if(c == 'Z'){fnWrite(dash); fnWrite(dash);  fnWrite(dot);   fnWrite(dot);   delay(space_letters);}
      if(c == '1'){fnWrite(dot);  fnWrite(dash);  fnWrite(dash),  fnWrite(dash);  fnWrite(dash);delay(space_letters);}
      if(c == '2'){fnWrite(dot);  fnWrite(dot);   fnWrite(dash);  fnWrite(dash);  fnWrite(dash);delay(space_letters);}
      if(c == '3'){fnWrite(dot);  fnWrite(dot);   fnWrite(dot);   fnWrite(dash);  fnWrite(dash);delay(space_letters);}
      if(c == '4'){fnWrite(dot);  fnWrite(dot);   fnWrite(dot);   fnWrite(dot);   fnWrite(dash);delay(space_letters);}
      if(c == '5'){fnWrite(dot);  fnWrite(dot);   fnWrite(dot);   fnWrite(dot);   fnWrite(dot);delay(space_letters);}
      if(c == '6'){fnWrite(dash); fnWrite(dot);   fnWrite(dot);   fnWrite(dot);   fnWrite(dot);delay(space_letters);}
      if(c == '7'){fnWrite(dash); fnWrite(dash);  fnWrite(dot);   fnWrite(dot);   fnWrite(dot);delay(space_letters);}
      if(c == '8'){fnWrite(dash); fnWrite(dash);  fnWrite(dash);  fnWrite(dot);   fnWrite(dot);delay(space_letters);}
      if(c == '9'){fnWrite(dash); fnWrite(dash);  fnWrite(dash);  fnWrite(dash);  fnWrite(dot);delay(space_letters);}
      if(c == '0'){fnWrite(dash); fnWrite(dash);  fnWrite(dash);  fnWrite(dash);  fnWrite(dash);delay(space_letters);}
      if(c == ' '){delay(space_words);}
  }
}

void fnWrite(int fn){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(fn);
  digitalWrite(LED_BUILTIN, LOW);
  delay(space);
}

