/*
    Exercise 13 - complete Serial set-point example.
    Presence: PIR HIGH -> occupied set-points, PIR LOW -> unoccupied set-points.

    o/u : choose the occupied/unoccupied set-points to EDIT.
    +/- : raise/lower fanStart and fanFull of that profile by 1 C.
    ?   : status.
*/
#include <Arduino_LSM6DSOX.h>

const int PIN_PIR = 1;
const int PIN_FAN = 2;

const unsigned long INTERVAL = 1000;
int lastTime = 0;

struct SETPOINT{
    float FAN_MAX;
    float FAN_MIN;
}

SETPOINT occupiedPoints = {20.0, 30.0};
SETPOINT unoccupiedPoints = {20.5, 30.5};

int temperatureC = 0;

bool isRoomOccupied = false;


void setup(){
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_FAN, OUTPUT);

    analogWrite(PIN_FAN, 0);

    Serial.begin(9600);
    while(!Serial);
    Serial.println("OGFYKSZ!");

    if(!IMU.begin()){
        Serial.println("BASLAAAAAT LAA!");
        while(True){};
    }

}

void loop(){

    now = millis();
    if(now - lastTime >= INTERVAL){
        lastTime = now;
        bool isRoomOccupiedRn = digitalRead(PIN_PIR) == HIGH;Ü

        float temperature = 0;
        
        //okuma
        if (IMU.temperatureAvailable()){
            int status = IMU.readTemperature(temperature);

            if (status != 0){
                temperatureC = temperature;
                Serial.println(temperatureC);
            }
        }

        //serialle settingleri oynama // fanı çalıştırma

        

    }

}