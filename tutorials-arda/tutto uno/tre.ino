const int PIN_PIR = 3;

const int PIN_LED = 4;
const unsigned long REPORT_INTERVAL_MS = 30000UL;
volatile int count = 0;


void onPIRChange(){
    if(digitalRead(PIN_PIR) == HIGH){
        digitalWrite(PIN_LED, HIGH);
        count++;
    }
    else{
        digitalWrite(PIN_LED, LOW);
    }
}

void setup(

    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_LED, OUTPUT);

    digitalWrite(PIN_LED, LOW);

    Serial.begin(9600);
    while(!Serial){};

    Serial.println("Ready!");

    attachInterrupt(digitalPinToInterrupt(PIN_PIR),onPIRChange, CHANGE);

)

void loop(){

    
    delay(REPORT_INTERVAL_MS);
    

    noInterrupts();

    int InterruptCount = count;

    Serial.println(InterruptCount);
    interrupts();

    
}

