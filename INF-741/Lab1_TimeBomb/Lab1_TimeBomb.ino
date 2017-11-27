/*
  Lab 1 - Time bomb

  - Based on the Arduino blink example create a code to increase and decrease
  the frequency of blink. Like a time bomb, the flash rate increases as the time
  runs out.

  - Start with 500ms delay and decrease by 20ms at each turn. When the delay
  is almost 0ms, increase to 500ms again using 20ms step, then, start over. 
  
  modified 3 Oct 2016
  by Vanessa Marques
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

int tMax = 500;
int tMin = 20;
int s = 20;
int t = tMax;
bool add = false;

void loop() {

    digitalWrite(LED_BUILTIN, HIGH);
    delay(t);                       
    digitalWrite(LED_BUILTIN, LOW); 
    delay(t);

    if(add) 
    {
      t = t + s;  
    }
    else
    {
      t = t - s;  
    }
    
    if(t < tMin)
    {
      add = true;
    }
    else if(t > tMax)
    {
      add = false;
    }
}
