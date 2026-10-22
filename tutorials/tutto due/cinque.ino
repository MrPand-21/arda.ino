/*
    Exercise 13 - complete Serial set-point example.
    Presence: PIR HIGH -> occupied set-points, PIR LOW -> unoccupied set-points.

    o/u : choose the occupied/unoccupied set-points to EDIT.
    +/- : raise/lower fanStart and fanFull of that profile by 1 C.
    ?   : status.
*/

#include <Arduino_LSM6DSOX.h>

const int FAN_PIN = 9;
const int PIR_PIN = 7;

const unsigned long SAMPLE_INTERVAL_MS = 1000UL;

struct SetPoints {
  float fanStart;
  float fanFull;
};

SetPoints occupiedSettings = {25.0, 30.0};
SetPoints unoccupiedSettings = {28.0, 33.0};
bool editingOccupied = true;
bool roomOccupied = false;

bool temperatureValid = false;
float temperatureC = 0.0;

unsigned long lastSample = 0;
int fanPWM = 0;

void processCommand(char command) {

  if (command == '?') {
    Serial.println("Adamızlanbizde");
    return;
  }
  if (command == 'o') {
    editingOccupied = true;
    Serial.println("Editing occupied profile.");
    return;
  }
  if (command == 'u') {
    editingOccupied = false;
    Serial.println("Editing unoccupied profile.");
    return;
  }

  // changing target changes the profile it refers to (reference assignment)
  SetPoints& target = editingOccupied ? occupiedSettings : unoccupiedSettings;
  if (command == '+') {
    target.fanStart++;
    target.fanFull++;
  }
  else if (command == '-') {
    target.fanStart--;
    target.fanFull--;
  }
  else {
    Serial.println("Unknown command. Send ? for status.");
    return;
  }
  Serial.println("Settings updated.");
}

void sampleTemperature(unsigned long now) {
  if (now - lastSample >= SAMPLE_INTERVAL_MS) {
    lastSample = now;
    if (IMU.temperatureAvailable()) {
      int measuredTemperature = 0;
      temperatureValid = IMU.readTemperature(measuredTemperature) != 0;
      if (temperatureValid) {
        temperatureC = measuredTemperature;
      }
    }
  }
}

void updateOutputs(const SetPoints& active) {
  int nextFanPWM = 0;
  if (temperatureValid) {
    if (temperatureC >= active.fanFull) {
      nextFanPWM = 255;
    }
    else if (temperatureC > active.fanStart) {
      nextFanPWM = (temperatureC - active.fanStart) * 255.0 /
                   (active.fanFull - active.fanStart);
    }
  }
  // PWM hardware keeps running; only write again when a value changes.
  if (nextFanPWM != fanPWM) {
    fanPWM = nextFanPWM;
    analogWrite(FAN_PIN, fanPWM);
  }
}

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  analogWrite(FAN_PIN, 0);

  Serial.begin(9600);
  while (!Serial) {}

  if (!IMU.begin()) {
    Serial.println("Failed to initialise IMU.");
    while (true) {}
  }

  Serial.println("Ready. o/u select a profile; +/- edit; ? status.");
}

void loop() {
  unsigned long now = millis();
  bool previousPresence = roomOccupied;

  roomOccupied = digitalRead(PIR_PIN) == HIGH;
  sampleTemperature(now);

  // One character per iteration keeps the other tasks responsive.
  if (Serial.available() > 0) {
    processCommand((char)Serial.read());
  }

  updateOutputs(roomOccupied ? occupiedSettings : unoccupiedSettings);
}
