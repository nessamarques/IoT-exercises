/*
  Lab 2 - Morse Code

  International Morse Code
  1)The length of a dot is one unit
  2)A dash is three units
  3)The space between parts of the same letter is one unit.
  4)The space between letters is three units.
  5)The space between words is seven units.

  Goal: Based on the previous morse code description, implement an arduino
  sketch to send a morse coded message using the Arduino UNO built in LED
  (connected to pin 13).
  The message should be stored on a global string named msg and initialized as:
  char* msg[] = "HELLO IOT WORLD";
  Your code must to be generic enough to allow sending other messages.
  Use 150 milliseconds as your basic time unit. 
  
  modified 3 Oct 2016
  by Vanessa Marques
*/

const int unit = 150;
const int dot = unit;
const int dash = 3 * unit;
const int space = unit;
const int space_letters = 3 * unit;
const int space_words = 7 * unit;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

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

