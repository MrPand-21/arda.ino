#include <MBED_RPi_Pico_TimerInterrupt.h>

const int LED_RED_PIN = 2;
const int LED_GREEN_PIN = 3;

const unsigned long RED_HALF_PERIOD_MS = 1500;
const unsigned long GREEN_HALF_PERIOD_MS = 3500;

bool redState = false;
volatile bool greenState = false; //ISR Changes it.

MBED_RPI_PICO_Timer timer1(1);

//should be fast
void blinkGreen(uint alarm_num){
  TIMER_ISR_START(alarm_num);
  greenState = !greenState;
  digitalWrite(LED_GREEN_PIN, greenState ? HIGH : LOW);
  TIMER_ISR_END(alarm_num);
}


void setup() {
    Serial.begin(9600);
    while(!Serial){

    }
    Serial.println("Adam olun la başlıyoz")
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);

  timer1.setInterval(
    GREEN_HALF_PERIOD_MS * 1000UL,
    blinkGreen
  );


}

void loop() {
    if (Serial.avaliable() > 0){ //receive buffer, how many chars are waiting for us 
        char command = Serial.read();
        if (command == "R"){
            Serial.print("Red LED: ");
            Serial.println(redState ? "ON" : "OFF");
        }
        else if(command == "L"){
            Serial.print("Green LED:");
            Serial.println(greenState ? "ON" : "OFF");

        }
        else{
            Serial.println("Send the correct command la")
        }
    }

    redState = !redState;
   digitalWrite(LED_RED_PIN, redState ? HIGH : LOW);
   delay(RED_HALF_PERIOD_MS);

}
