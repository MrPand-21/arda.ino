// Task: schedule several tasks without delay().

// Instead of halting the program completly, ask "Has enough time passed to do this task?"
// remember when a task last ran, and depending on elapsed time, do an action again

const int RED_PIN = 2;
const int GREEN_PIN = 3;

const unsigned long RED_INTERVAL_MS = 1500;
const unsigned long GREEN_INTERNAL_MS = 3500;

unsigned long lastRed = 0;
unsigned long lastGreen = 0;

bool redState = false;
bool greenState = false;

void setup(){

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);

    Serial.begin(9600);
    while(!Serial){}
}

void loop(){
    unsigned long now = millis();
    //calcualte deltas / elapsed times
    elapsedRed = now - lastRed;
    elapsedGreen = now - lastGreen;

    if ( elapsedRed >= RED_INTERVAL_MS ){
        lastRed = now;

        redState = !redState;
        digitalWrite(RED_PIN, redState ? HIGH:LOW)
    }

    if (elapsedGreen >= GREEN_INTERNAL_MS){
        lastGreen = now;

        greenState = !greenState;
        digitalWrite(GREEN_PIN, greenState ? HIGH : LOW)
    }

    if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'R') {
      Serial.print("Red: ");
      Serial.println(redState ? "ON" : "OFF");
    }
    else if (command == 'L') {
      Serial.print("Green: ");
      Serial.println(greenState ? "ON" : "OFF");
    }
    else {
      Serial.println("Error: send R or L.");
    }
  }
}