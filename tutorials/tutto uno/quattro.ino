// So far, our outputs have been simply ON or OFF. 
// PWM—Pulse-Width Modulation—lets us control the fraction of time an output stays ON.

// Our coding task: start the fan at zero, accept '+' and '-' through Serial, 
// and change the setting in ten steps. 
// Report errors and prevent movement beyond the limits.

const int FAN_STEPS = 10;
const int FAN_PIN = 8;

int speedStart = 0;

void setup(){
    pinMode(FAN_PIN, OUTPUT)
    analogWrite(FAN_PIN, 0);

    Serial.begin(9600);
    while (!Serial) {
  }

    Serial.println("Send + to increase or - to decrease.");

}

void loop(){
    if (Serial.avaliable() > 0){
        char command = Serial.read();
        if (command == "+"){

            if (FAN_STEPS > speedStart){
                speedStart++;
            } else{
                Serial.println("çOK HIZLIYIZ ZATEN")
                return;
            }

        } else if(command == "-"){

            if(speedStart > 0){
                speedStart--;
            }else{
                Serial.println("Daha yavaş olmaz");
                return;
            }

            
        }else{
            Serial.println("You hsould press - or + ");
            return;
        }
    }

    analogWrite(FAN_PIN, speedStart* 255 / FAN_STEPS)

    //optional
    int percentage = (speedStep * 100) / NUM_STEPS;
    Serial.print("Fan setting: ");
    Serial.print(percentage);
    Serial.println("%");

}