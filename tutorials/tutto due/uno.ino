// Lab Part 2: the smart home controller.

// Previously, you chose fan speed using + and -. Now the temperature determines the output.

// | Output | OFF | Gradually increases | Fully ON |
// | Fan | At or below 25°C | From 25°C to 30°C | At or above 30°C |
// | Heater | At or above 20°C | As temperature falls from 20°C to 15°C | At or below 15°C |

// NOTE: we use LSM6DSOX IMU instead of analog read (see @tutto uno/cinque.ino)

#include <Arduino_LSM6DSOX.h>

const int FAN_PIN = 9;
const int HEATER_PIN = 2;  // External red led.

const float FAN_START = 25.0;
const float FAN_FULL = 30.0;

const float HEATER_START = 20.0;
const float HEATER_FULL = 15.0;

const unsigned long SAMPLE_INTERVAL_MS = 1000UL;
unsigned long lastSample = 0;

void controlTemperature(float temperature){
    int fanPWM = 0;
    int heaterPWM = 0;
    float percentageTemp = 0.0;

    if (temperature >= FAN_FULL) {
        fanPWM = 255;
    }
    else if (temperature > FAN_START){
        percentageTemp = (temperature - FAN_START) / (FAN_FULL-FAN_START);
        fanPWM = percentageTemp * 255;
    } else{
        fanPWM = 0;
    }

    if(temperature >= HEATER_START){
        heaterPWM = 0;
    }
    else if(temperature > HEATER_FULL){
        percentageTemp = (HEATER_START - temperature) / (HEATER_START-HEATER_FULL);
        heaterPWM = percentageTemp * 255;
    }
    else {
        heaterPWM = 255;
    }

    analogWrite(FAN_PIN, fanPWM);
    analogWrite(HEATER_PIN, heaterPWM);
}

void setup(){
    pinMode(FAN_PIN, OUTPUT);
    pinMode(HEATER_PIN, OUTPUT);

    analogWrite(FAN_PIN, 0);
    analogWrite(HEATER_PIN, 0);

    Serial.begin(9600);
    while(!Serial){}

    if (!IMU.begin()) {
        Serial.println("Failed to initialise IMU.");
        while (true) {}
  }
}

void loop(){
    unsigned long now = millis();
    if (now - lastSample >= SAMPLE_INTERVAL_MS) {
        lastSample = now;

        if (IMU.temperatureAvailable()) {
            float temperature = 0.0;

            if (IMU.readTemperature(temperature)) {
                controlTemperature(temperature);

                Serial.print("Temperature: ");
                Serial.println(temperature);
            }
        }
    }
}