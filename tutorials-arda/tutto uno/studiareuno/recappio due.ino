const int PIN_FAN = 7;
const int FAN_STEP = 10;

const int PIN_PIR = 12;

volatile int speed = 0;

void setup(){

    pinMode(PIN_FAN, OUTPUT);
    pinMode(PIN_PIR, INPUT);

    analogWrite(PIN_FAN, 0);

    Serial.begin(9600);
    while(!Serial){};
    Serial.println("ZaaXD");

    attachInterrupt(digitalPinToInterrupt(PIN_PIR), onPIRRise, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_PIR), onPIRFall, FALLING);

}

void onPIRRise(){
    // Fan hızı 5 ten az ise 5 ile başlasın
    int fanSpeed = analogRead(PIN_FAN)*FAN_LAYER/255;

    if (fanSpeed < 5){
        speed = 5; 
    }
    

}

void onPIRFall(){

    int fanSpeed = analogRead(PIN_FAN)*FAN_LAYER/255;

    if(fanSpeed>5){
        speed = 5;
    }

}


void loop(){

    if(Serial.available() > 0){
        char cmd = Serial.read();

        if(cmd == "+"){

            if(speed>=FAN_LAYER){
                Serial.print("Speed");
                Serial.println("YAVAS LA YAVAS GAC TANE ALION");
                return;
            }
            else{
                speed++;
            }   

        }

        else if(cmd == "-"){

            if(speed <= 0){
                Serial.println("O KADAR DA DEGIL LA");
                return;
            }
            else(){
                speed--;
            }

        }

        else{
            Serial.println("DOGRU DUZGUN KULLAN KLAVYEYI");
            return;
        }

        noInterrupts();
        int speedToSet = speed*255/FAN_LAYER;
        analogWrite(PIN_FAN, speedToSet);
        Serial.printn(speedToSet);
        interrupts();

        
    }

}