#include <Arduino_FreeRTOS.h>
#include "mario.h"
#include <math.h>

#define interruptPin 2
#define melodyPin 3

volatile long adcSum = 0;
volatile long sampleCount = 0;
volatile long avg = 0;

volatile bool buttonPressed = false;
volatile bool getData = true;

// TASKS
void DataAcquisitionTask(void *pvParameters);
void DiagnosticsTask(void *pvParameters);
void DataConversionOutputTask(void *pvParameters);
void MusicPlayerTask(void *pvParameters);
void IdleTask(void *pvParameters);

void setup() {

  // Opens serial port, sets data rate to 9600 bps
  Serial.begin(9600);

  // LED Pin
  pinMode(LED_BUILTIN, OUTPUT);

  //LED State
  digitalWrite(LED_BUILTIN, LOW);
  
  // Buzzer Pin
  pinMode(melodyPin, OUTPUT);

  // Configure interrupt
  attachInterrupt(digitalPinToInterrupt(interruptPin), onButtonPressed, FALLING);

  // Configure tasks
  xTaskCreate(DataAcquisitionTask,(const portCHAR *) "Data acquisition", 128, NULL, 4, NULL);
  xTaskCreate(DiagnosticsTask, (const portCHAR *) "Diagnostics", 128, NULL, 3, NULL);
  //xTaskCreate(DataConversionOutputTask,(const portCHAR *) "Data conversion and output task", 128, NULL, 3, NULL);              
  xTaskCreate(MusicPlayerTask,(const portCHAR *) "Music player", 128, NULL, 2, NULL);
  xTaskCreate(IdleTask,(const portCHAR *) "Idle", 128, NULL, 1, NULL);

  // Stop interrups
  cli();

  // Configure ADC
  SetADC();

  Serial.println("*********************************************");
  Serial.println("****      Coursework 3: Multitasking     ****");
  Serial.println("*********************************************");

  // Enable global interrupts  
  sei();
}

void loop() {}

ISR(ADC_vect) {
  if (getData) {
    sampleCount++;
    adcSum += ADC;
  }
}

void SetADC(){
  ADCSRA = (1 << ADEN);
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADMUX = (1 << REFS0);
  ADCSRA |= (1 << ADATE);
  ADCSRA |= (1 << ADIE);
  ADCSRA |= (1 << ADSC);
}

void onButtonPressed() {
  buttonPressed = true;
}

void sleepCPU() {
  SMCR &= ~(1 << SM0);
  SMCR &= ~(1 << SM1);
  SMCR &= ~(1 << SM2);
  SMCR |= (1 << SE);
  asm("sleep");
}

void blinkLed() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
  vTaskDelay(1);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
  vTaskDelay(1);
}

void DataAcquisitionTask(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    vTaskDelay( 5000 / portTICK_PERIOD_MS );

    getData  = false;
    
    avg = adcSum / sampleCount;

    Serial.print("[INFO] AVG: ");
    Serial.println(avg);

    // Clear ADC sum and count
    adcSum = 0;
    sampleCount = 0;

    getData = true;
  }
}

void DiagnosticsTask(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    
    if (buttonPressed) {

      Serial.println("[INFO] Button Pressed! ");
      blinkLed();
      
      Serial.print("[INFO] Sample count: ");
      Serial.println(sampleCount);
      
      Serial.print("[INFO] ADC Sum: "); 
      Serial.println(adcSum);

      buttonPressed = false;
    }
    
    vTaskDelay(200/portTICK_PERIOD_MS);
  }
}

void DataConversionOutputTask(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    //Obs: A aplicação não funcionou ao habilitar essa task, então implementei a função dela em "DataAcquisitionTask".
  }
}

void MusicPlayerTask(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    play_melody(); // Call "play_melody" from "mario.h"
  }
}

void IdleTask(void *pvParameters){
  (void) pvParameters;

  for (;;) {
    sleepCPU();
  }
}
