/**********************************************************
Lab 7: Encode terminal messages using morse code
Modify your morse code sketch so that it encodes messages
read from the terminal.
**********************************************************/
#define LED_PIN 13
#define TIME_UNIT                 150
#define DOT_TIME                  TIME_UNIT
#define DASH_TIME                 TIME_UNIT*3
#define DELAY_INSIDE_LETTER       TIME_UNIT
#define DELAY_BETWEEN_LETTERS     TIME_UNIT*3
#define DELAY_BETWEEN_WORDS       TIME_UNIT*7

char msg[50];
char* p[50];

void setup()
{

  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  if(Serial.available()) {
    
    //*msg =  Serial.readString();

    String str =  Serial.readString();
    str.toCharArray(msg, str.length() + 1);

    *p = msg;

    Serial.println(*p);
  
  }  

  while (*p != 0) {
    delay_between_letters();
    const char* code = get_code(*p);
    display(code);
    p++;
  }
  

  
}

const char* get_code(const char c)
{
  switch (c){
    case ' ':
      return " "; 
      break;
    case 'A':
      return ".-";
      break;
    case 'B':
      return "-...";
      break;
    case 'C':
      return "-.-.";
      break;
    case 'D':
      return "-..";
      break;
    case 'E':
      return ".";
      break;
    case 'F':
      return "..-.";
      break;
    case 'G':
      return "--.";
      break;
    case 'H':
      return "....";
      break;
    case 'I':
      return "..";
      break;
    case 'J':
      return ".---";
      break;
    case 'K':
      return "-.-";
      break;
    case 'L':
      return ".-..";
      break;
    case 'M':
      return "--";
      break;
    case 'N':
      return "-.";
      break;
    case 'O':
      return "---";
      break;
    case 'P':
      return ".--.";
      break;
    case 'Q':
      return "--.-";
      break;
    case 'R':
      return ".-.";
      break;
    case 'S':
      return "...";
      break;
    case 'T':
      return "-";
      break;
    case 'U':
      return "..-";
      break;
    case 'V':
      return "...-";
      break;
    case 'W':
      return ".--";
      break;
    case 'X':
      return "-..-";
      break;
    case 'Y':
      return "-.--";
      break;
    case 'Z':
      return "--.";
      break;
    case '1':
      return ".----";
      break;
    case '2':
      return "..---";
      break;
    case '3':
      return "...--";
      break;
    case '4':
      return "....-";
      break;
    case '5':
      return ".....";
      break;
    case '6':
      return "-....";
      break;
    case '7':
      return "--...";
      break;
    case '8':
      return "---..";
      break;
    case '9':
      return "----.";
      break;
    case '0':
      return "-----";
      break;
    default:
      return nullptr;
      break;
  }
}

void dot ()
{
  digitalWrite(LED_PIN, HIGH);
  delay(DOT_TIME);
  digitalWrite(LED_PIN, LOW);
}

void dash ()
{
  digitalWrite(LED_PIN, HIGH);
  delay(DASH_TIME);
  digitalWrite(LED_PIN, LOW);
}

void delay_between_dots_and_dashes()
{
  delay(DELAY_INSIDE_LETTER);
}

void delay_between_words()
{
  // Accounting for the delay already introduced before and after the space:
  delay(DELAY_BETWEEN_WORDS-2*DELAY_BETWEEN_LETTERS);
}

void delay_between_letters()
{
  delay(DELAY_BETWEEN_LETTERS);
}

void display (const char* code) 
{
  for (const char* p = code; *p; p++) {
    switch(*p){
    case '.':
      dot();
      break;
    case '-':
      dash();
      break;
    case ' ':
      delay_between_words();
      break;
    default:
      break; 
    }
    delay_between_dots_and_dashes();
  }
}

