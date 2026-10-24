// Lab Part 2: the smart home controller.

// Previously, you chose fan speed using + and -. Now the temperature determines the output.
// Temperature must be checked every 1 second and fan levels must updated accordingly.

// | Output | OFF | Gradually increases | Fully ON |
// | Fan | At or below 25°C | From 25°C to 30°C | At or above 30°C |
// | Heater | At or above 20°C | As temperature falls from 20°C to 15°C | At or below 15°C |

// NOTE: we use LSM6DSOX IMU instead of analog read (see @tutto uno/cinque.ino)
#include <Arduino_LSM6DSOX.h>

const int PIN_FAN = 1;
const int PIN_HLED = 2;

const float FAN_MAX = 30.0;
const float FAN_MIN = 25.0;

float fanSpeed = 0;
float thermo = 0;

const float HEATER_MAX = 20.0;
const float HEATER_MIN = 15.0;

unsigned long INTERVAL = 1000;
int lastTime = 0;

void controller(int temperature){

    if(temperature<FAN_MIN){
        fanSpeed = 0; //0-255
    }
    else if(temperature > FAN_MIN && temperature < FAN_MAX){
        float percentage = (temperature - FAN_MIN)/(FAN_MAX - FAN_MIN);
        fanSpeed = (float)percentage * 255;
    }
    else{
        fanSpeed = 255;
    }
    
    
    if(temperature<HEATER_MIN){
        thermo = 255;
    }
    else if(temperature > HEATER_MIN && temperature < HEATER_MAX){
        float percent = (HEATER_MAX - temperature)/(HEATER_MAX - HEATER_MIN);
        thermo = (float)percent*255;
    }
    else{
        thermo = 0;
    }

    analogWrite(PIN_FAN, fanSpeed);
    analogWrite(PIN_HLED, thermo);

}

void setup(){

    pinMode(PIN_FAN, OUTPUT);
    pinMode(PIN_HLED, OUTPUT);

    analogWrite(PIN_FAN, 0);
    analogWrite(PIN_HLED, 0);

    Serial.begin(9600);
    while(!Serial){};
    Serial.println("Ready to GO!");

    if(!IMU.begin()){
        Serial.println("!");
        while(true){};
    }

}

void loop(){

    if(millis() - lastTime >= INTERVAL){
        lastTime = millis();
        
        if(IMU.temperatureAvailable()){
            
            float temperature;
            IMU.readTemperature(temperature);
            controller(temperature);
        }
    }

    
}