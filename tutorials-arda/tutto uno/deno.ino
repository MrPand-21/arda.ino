#include <MBED_RPi_Pico_TimerInterrupt.h>

const int  GREEN_PIN = 2;
const int RED_PIN = 3;

const unsigned long RED_HALF_PERIOD_MS = 1500;
const unsigned long GREEN_HALF_PERIOD_MS = 3500;

bool isRedOpen = false;
bool isGreenOpen = false;

MBED_RPI_PICO_Timer timer1(1);

TIMER_ISR_START()
TIMER_ISR_END()




void setup(){
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(RED_PIN, OUTPUT);

    digitalWrite(GREEN_PIN, LOW);
    digitalWrite


    Serial.begin(9600);
    
    while (!Serial) {}
    Serial.println("Ready");

    timer1.setInterval(
        GREEN_HALF_PERIOD_MS * 1000UL,
        blinkGreen
    );

}

void loop(){

    isRedOpen = !isRedOpen;


}