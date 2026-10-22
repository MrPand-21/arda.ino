// So far, our outputs have been simply ON or OFF. 
// PWM—Pulse-Width Modulation—lets us control the fraction of time an output stays ON.

// Our coding task: start the fan at zero, accept '+' and '-' through Serial, 
// and change the setting in ten steps. 
// Report errors and prevent movement beyond the limits.

const int PIN_FAN = 15;

const int FAN_LAYER = 10;

const int speed = 0;

void setup(){

    pinMode(PIN_FAN, OUTPUT);

    analogWrite(PIN_FAN, HIGH);



}

void loop(){

    if(Serial.available() > 0){
        char ch = Serial.read();

        if(ch == "+"){

            if(speed < FAN_LAYER){
                speed++;
            }

            else{
                Serial.println
            }

        }
    }

}


