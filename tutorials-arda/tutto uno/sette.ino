// TASK: Elapsed time mantığı ile blue, red, green pinleri çalıştır
// sırasıyla 1.5 sn de bir, 2.5 sn de bir, 7 sn de bir

const int PIN_ROSSO = 1;
const int PIN_VERDE = 2;
const int PIN_AZZURE = 3;

const unsigned int TempoVerde = 7000;
const unsigned int TempoRosso = 2500;
const unsigned int TempoAzzure = 1500;

int lastVerde, int lastRosso, int lastAzzure = 0;

bool Verde = false;
bool Rosso = false;
bool Azzure = false;


void setup(){

    pinMode(PIN_ROSSO, OUTPUT);
    pinMode(PIN_VERDE, OUTPUT);
    pinMode(PIN_AZZURE, OUTPUT);

    digitalWrite(PIN_ROSSO, LOW);
    digitalWrite(PIN_VERDE, LOW);
    digitalWrite(PIN_AZZURE, LOW);

    Serial.begin(9600);

    while(!Serial){};

    Serial.println("Ready to Go!");

}

void loop(){

    unsigned long currentTime = millis();
V

    // elapsed = now - last
    int elapsedVerde = currentTime - lastVerde;
    int elapsedRosso = currentTime - lastRosso;
    int elapsedAzzure = currentTime - lastAzzure;

    // elapsedVerde = 8sn, temp = 7sn
    if ( elapsedVerde > TempoVerde ){
        Verde = !Verde;
        digitalWrite(PIN_VERDE, Verde ? HIGH : LOW);
    }

    if ( elapsedRosso > TempoRosso ){
        Rosso = !Rosso;
        digitalWrite(PIN_Rosso, Rosso ? HIGH : LOW);
    }

    if ( elapsedAzzure > TempoAzzure ){
        Azzure = !Azzure;
        digitalWrite(PIN_AZZURE, Azzure ? HIGH : LOW);
    }

    
    if(Serial.available() > 0){
        char cmd = Serial.read();
    
        if(cmd == "R" || cmd == "r"){
            Serial.print("LED STATUS: ");
            Serial.println(Verde ? "ACIK LA" : "NEIN DEGIL");
        }
        else if(cmd == "O" || cmd == "o"){
            Serial.print("LED STATUS");
            Serial.print(Rosso ? "ACIK LA" : "NEEEIN");
            Serial.println(Azzure ? "ACIK LA" : "NEEEIN");
        }
        else {
            Serial.println("NE DIYON LA SEN DEGISIK");
        }

    }

}