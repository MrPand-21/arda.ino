// Exercise 4: detect motion using a PIR sensor.
// A PIR module provides a digital signal:
//      HIGH: motion detected.
//      LOW: detection inactive.
// We’ll write a new standalone sketch with these requirements:
//      1. React whenever the PIR output changes.
//      2. Make an external LED follow the PIR’s output.
//      3. Count new detections.
//      4. Print the total every 30 seconds.
// These are the requirements of your lab’s Exercise 1.3.

const int PIR_PIN = 7;
const int LED_PIN = 2;
const unsigned long REPORT_INTERVAL_MS = 30000UL;
volatile unsigned long eventCount = 0;

void onPIRChange(){
    bool detected = (digitalRead(PIR_PIN) == HIGH);
    digitalWrite(LED_PIN, detected ? HIGH : LOW);
    if (detected) {
    eventCount++;
    }

}

void setup(){
    pinMode(PIR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    digitalWrite(LED_PIN, LOW);
    Serial.begin();

    while(!Serial){}

    attachInterrupt(
        digitalPinToInterrupt(PIR_PIN),
    onPIRChange,
    CHANGE );
}

void loop(){
    delay(REPORT_INTERVAL_MS);
    noInterrupts();
    unsigned long countSnapshot = eventCount;
    interrupts();
    Serial.print("Total motion events: ");
  Serial.println(countSnapshot);
}