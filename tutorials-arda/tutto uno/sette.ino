// TASK: Elapsed time mantığı ile blue, red, green pinleri çalıştır
// sırasıyla 1.5 sn de bir, 2.5 sn de bir, 7 sn de bir

const int PIN_BLUE=1;
const int PIN_RED = 2;
const int PIN_GREEN = 3;

const int last_blue = 0;
const int last_red = 0;
const int last_green = 0;

const int blueT = 1500;
const int redT = 2500;
const int greenT = 7000;


void setup(){
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);

    digitalWrite(PIN_BLUE, LOW);
    digitalWrite(PIN_RED, LOW);
    digitalWrite(PIN_GREEN, LOW);

    Serial.begin(9600);

    while(!Serial){};

    Serial.println(9600);

}


void loop(){

    int currentTime = millis();
    int elapsedBlue = currentTime - last_blue;
    int elapsedRed = currentTime - last_red;
    int elapsedGreen = currentTime - last_green;

    if (elapsedBlue > blueT){
        last_blue = currentTime;
        

    }

}