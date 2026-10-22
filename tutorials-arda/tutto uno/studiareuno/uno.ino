#include <MBED_RPi_Pico_TimerInterrupt.h>

const int GREEN_LED = 3;
const int RED_LED = 4;

const unsigned long TimerGREEN = 1500;
const unsigned long TimerRED = 3500;

bool isGreen = false;
bool isRed = false;

MBED_RPI_PICO_Timer timer1(1);

void setup(){

    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);

    Serial.begin(9600);
    while(!Serial){};
    Serial.println("Ready!");

    timer1.setInterval(
        TimerGREEN * 1000,
        blinkGreen
    );



    

}

void blinkGreen(int alarmID){

    TIME_ISR_START(alarmID);
    isGreen = !isGreen;
    digitalWrite(GREEN_LED, isGreen ? HIGH : LOW);
    TIME_ISR_END(alarmID);


}

void loop(){

    delay(TimerRED);
    isRed = !isRed;
    digitalWrite(RED_LED, isRed ? HIGH : LOW);

    if(Serial.available()>0){
        char ch = Serial.read();

        if(ch == "r" || ch == "R"){
            Serial.print("RED: ");
            Serial.println(isRed ? "HIGH" : "LOW la uşaum");
        }

        else if(ch =="l" || ch =="L"){
            Serial.print("GREEN: ");
            Serial.println(isRed ? "HIGH" : "LOW");
        }

        else {
            Serial.println("NEIIIN!");
        }
    }

}