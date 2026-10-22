// Res = (1023.0 / raw - 1.0) * R_FIXED; 
// tempK = 1.0 / (log(Res / R0) / B + 1.0 / T0_K);
// float tempC = tempK - 273.15;

const int PIN_TEMP = A0;
const float R_FIXED = 100000.0;
const float R0 = 100000.0;
const float B = 4275.0;
const float T0_K = 298.15;

void setup(){

    analogReadResolution(10);
    pinMode(PIN_TEMP, INPUT);
    Serial.begin(9600);
    while(!Serial){};
    Serial.println("Ready!");

}


void loop(){
    int raw = analogRead(PIN_TEMP);

    if(raw>0 && raw <1023){

        float resistence = (1023.0 / raw - 1.0) * R_FIXED;  
        float KelvinT = 1.0 / (log(Res / R0) / B + 1.0 / T0_K);
        float CelsiusT = KelvinT - 273.15;
        Serial.println(CelsiusT);
        
    }
    else{
        Serial.println("Sensor Error!");
    }

}