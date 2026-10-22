
#include <MBED_RPi_Pico_TimerInterrupt.h>

const int GREEN_PIN = 2;
const int RED_PIN = 3;

const unsigned long RED_HALF_PERIOD_MS = 1500;
const unsigned long GREEN_HALF_PERIOD_MS = 3500;

bool isRedOpen = false;
bool isGreenOpen = false;

MBED_RPI_PICO_Timer timer1(1);


void blinkGreen(int alarm_num){
TIMER_ISR_START(alarm_num)

    isGreenOpen = !isGreenOpen;
    digitalWrite(GREEN_PIN, isGreenOpen ? HIGH : LOW);.
    
TIMER_ISR_END(alarm_num)

}

void setup(){
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(RED_PIN, OUTPUT);

    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, LOW);


    Serial.begin(9600);
    
    while (!Serial) {}
    Serial.println("Ready");

    timer1.setInterval(
        GREEN_HALF_PERIOD_MS * 1000UL,
        blinkGreen
    );

}

void loop(){


    if(Serial.available() > 0){

        char ch = Serial.read();

        if(ch == "r" || ch == "R"){
            Serial.print("RED PIN: ");
            Serial.println(isRedOpen ? "AÇIK ULAN BU" : "LOW");
        }

        else if(ch == "l" || ch == "L"){
            Serial.print("GREEN PIN: ");
            Serial.println(isGreenOpen ? "NE DIYON LAN ACIK ISTE" : "LOW");
        }

        else{
            Serial.println("DOGRU BAS SU KLAVYEYE");
        }

    }

    isRedOpen = !isRedOpen;
    digitalWrite(RED_PIN, isRedOpen ? HIGH : LOW);
    delay(RED_HALF_PERIOD_MS);

}