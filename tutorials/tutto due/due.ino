// TASK: remember presence after motion stops

// Motion and presence are different things. Someone sitting still may stop triggering 
// the PIR, but we should not immediately assume they left.

// motionDetected	Has the ISR reported a new detection?
// lastMotion	When did we last process a detection?
// pirPresence	Does the system currently consider the room occupied?
// pir presence = 30 mins since last motion

const int PIR_PIN = 2; //zıkkım
const int PRESENCE_LED_PIN = 7;

const unsigned long PIR_TIMEOUT_MS = 30UL * 60UL * 1000UL; //30dk
unsigned long lastMotion = 0;

volatile bool motionDetected = false;
bool pirPresence = false;

void onMotion(){
      motionDetected = true;
}

void setup(){
    pinMode(PIR_PIN, INPUT);
    pinMode(PRESENCE_LED_PIN, OUTPUT);

    digitalWrite(PRESENCE_LED_PIN, LOW);
    Serial.begin(9600);

    while(!Serial){};

    attachInterrupt(
        digitalPinToInterrupt(PIR_PIN),
        onMotion,
        RISING
    );

}

void loop(){
    bool previousPresence = pirPresence;

    //In between CS (Critical Section)
    noInterrupts();
    bool newMotion = motionDetected;
    motionDetected = false;
    interrupts();

    unsigned long now = millis();

    if (newMotion) {
        lastMotion = now;
        pirPresence = true;
    }

    if (pirPresence && now - lastMotion >= PIR_TIMEOUT_MS) {
        pirPresence = false;
    }

    digitalWrite(PRESENCE_LED_PIN ,pirPresence ? HIGH : LOW);

    if (pirPresence != previousPresence) {
        Serial.println(
        pirPresence ? "Room occupied" : "Room empty"
        );
    }

}



