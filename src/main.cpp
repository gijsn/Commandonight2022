#include <Arduino.h>

#define _TASK_SLEEP_ON_IDLE_RUN
#include <TaskScheduler.h>


#define PIN_LATCH D7 //ST_CP
#define PIN_CLOCK D6 //SH_CP
#define PIN_DATA D8 //DS

#define PIN_LED1 D0
#define PIN_LED2 D1
#define PIN_LED3 D2
#define PIN_LED4 D3

Scheduler ts;

void updateShiftRegister(uint16_t data);

void led1On();
void led1Off();
void led2On();
void led2Off();
void led3On();
void led3Off();
void led4On();
void led4Off();
void change7Segment();

// Tasks
Task tLed1(100, TASK_FOREVER, &led1On, &ts, true);
Task tLed2(100, TASK_FOREVER, &led2On, &ts, true);
Task tLed3(1000, TASK_FOREVER, &led3On, &ts, true);
Task tLed4(500, TASK_FOREVER, &led4On, &ts, true);
Task tsegment7(500, TASK_FOREVER, &change7Segment, &ts, true);

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */


void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);  
  pinMode(PIN_CLOCK, OUTPUT);

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
      digitalWrite(PIN_LED1, LOW);
  digitalWrite(PIN_LED2, LOW);
  digitalWrite(PIN_LED3, LOW);
  digitalWrite(PIN_LED4, LOW);

  digitalWrite(PIN_LED1, HIGH);
  delay(50);
  digitalWrite(PIN_LED1, LOW);
  delay(100);
  for(int i = 0; i < 100; i++){
    digitalWrite(PIN_LED1, HIGH);
    delay(random(100));
    digitalWrite(PIN_LED1, LOW);
    delay(random(100));
  }
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{

  	ts.execute();
  // leds = 0;	// Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  // updateShiftRegister();
  // delay(500);
  //   digitalWrite(PIN_LED1, LOW);
  // digitalWrite(PIN_LED2, HIGH);
  // digitalWrite(PIN_LED3, LOW);
  // digitalWrite(PIN_LED4, HIGH);
  // for (int i = 0; i < 8; i++)	// Turn all the LEDs ON one by one.
  // {
  //   bitSet(leds, i);		// Set the bit that controls that LED in the variable 'leds'
  //   updateShiftRegister();
    
  //     digitalWrite(PIN_LED1, LOW);
  // digitalWrite(PIN_LED2, HIGH);
  // digitalWrite(PIN_LED3, LOW);
  // digitalWrite(PIN_LED4, HIGH);
  //   delay(500);
  //     digitalWrite(PIN_LED1, HIGH);
  // digitalWrite(PIN_LED2, LOW);
  // digitalWrite(PIN_LED3, HIGH);
  // digitalWrite(PIN_LED4, LOW);
  // delay(500);
  // }
  // digitalWrite(PIN_LED1, LOW);
  // digitalWrite(PIN_LED2, HIGH);
  // digitalWrite(PIN_LED3, LOW);
  // digitalWrite(PIN_LED4, HIGH);
}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister(uint16_t data)
{

}







void led1On() {
  digitalWrite(PIN_LED1, HIGH);
  tLed1.setCallback(led1Off);
  // tLed1.setInterval(random(100));
  // tLed1.restart();
}

void led1Off(){
  digitalWrite(PIN_LED1, LOW);
  tLed1.setCallback(led1On);
  // tLed1.setInterval(random(100));
  // tLed1.restart();
}

void led2On() {
  digitalWrite(PIN_LED2, HIGH);
  tLed2.setCallback(led2Off);
  tLed2.setInterval(random(200));
}

void led2Off(){
  digitalWrite(PIN_LED2, LOW);
  tLed2.setCallback(led2On);
  tLed2.setInterval(random(2000));
}

void led3On() {
  digitalWrite(PIN_LED3, HIGH);
  tLed3.setCallback(led3Off);
  tLed3.setInterval(random(1000));
}

void led3Off(){
  digitalWrite(PIN_LED3, LOW);
  tLed3.setCallback(led3On);
  tLed3.setInterval(random(1000));
}

void led4On() {
  digitalWrite(PIN_LED4, HIGH);
  tLed4.setCallback(led4Off);
  tLed4.setInterval(random(500));
}

void led4Off(){
  digitalWrite(PIN_LED4, LOW);
  tLed4.setCallback(led4On);
  tLed4.setInterval(random(5000));
}
uint8_t disp1;
uint8_t disp2;
void change7Segment(){
  bool chooseDisp = random(2);
  if(chooseDisp){
    disp1 = (uint8_t) random(256);
  }else {
    disp2 = (uint8_t) random(256);
  }
   digitalWrite(PIN_LATCH, LOW);
   shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, disp1);
   shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, disp2);
   digitalWrite(PIN_LATCH, HIGH);
  tsegment7.setInterval(random(200));
}



