// TASK: remember presence after motion stops

// Motion and presence are different things. Someone sitting still may stop triggering 
// the PIR, but we should not immediately assume they left.

// motionDetected	Has the ISR reported a new detection?
// lastMotion	When did we last process a detection?
// pirPresence	Does the system currently consider the room occupied?
// has anyone moved in the last 30 mins?

const int PIN_PIR = 1;
const int PIN_LED = 2;

const unsigned long motionTime= 30*60*1000;

volatile bool motionDetected = false;

int lastDetected = 0;

void onPIR(){
    motionDetected = true;
}    


void setup(){
    
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_LED, OUTPUT);

    digitalWrite(PIN_LED, LOW);

    Serial.begin(9600);
    while(!Serial){};
    Serial.println("READY2GO");

    attachInterrupt(digitalPinToInterrupt(PIN_PIR), onPIR, RISING);
}

void loop(){
    int recentlyMotionDetected;
    int now = millis();

    noInterrupts();
    recentlyMotionDetected = motionDetected;
    motionDetected = false;
    interrupts();

    
    if(recentlyMotionDetected ){
        lastDetected = now;
        digitalWrite(PIN_LED, HIGH);
    }
    else if(!recentlyMotionDetected && now - lastDetected > motionTime ){
        digitalWrite(PIN_LED, LOW);
    }

    
}