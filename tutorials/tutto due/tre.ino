// Task: detect sound using the microphone.
// Fazla komplex sınav için GEÇ

// #include <PDM.h>

// const int BUFFER_SAMPLES = 256;
// const int BUFFER_BYTES = BUFFER_SAMPLES * 2;

// const int SOUND_THRESHOLD = 1000;
// const unsigned long QUIET_TIME_MS = 200UL;

// short sampleBuffer[BUFFER_SAMPLES];
// short workingBuffer[BUFFER_SAMPLES];

// volatile int samplesReady = 0;

// bool soundArmed = true;
// unsigned long lastLoudTime = 0;
// unsigned long soundEvents = 0;

// void onPDMdata() {
//   int bytesAvailable = PDM.available();

//   if (bytesAvailable > BUFFER_BYTES) {
//     bytesAvailable = BUFFER_BYTES;
//   }

//   int bytesRead =
//     PDM.read(sampleBuffer, bytesAvailable);

//   samplesReady = bytesRead / 2;
// }

// void setup() {
//   Serial.begin(9600);
//   while (!Serial) {
//   }

//   PDM.setBufferSize(BUFFER_BYTES);
//   PDM.onReceive(onPDMdata);

//   if (!PDM.begin(1, 16000)) {
//     Serial.println("Failed to start microphone.");

//     while (true) {
//     }
//   }
// }

// void loop() {
//   // Make a stable copy before analysing the samples.
//   noInterrupts();

//   int count = samplesReady;

//   for (int i = 0; i < count; i++) {
//     workingBuffer[i] = sampleBuffer[i];
//   }

//   samplesReady = 0;
//   interrupts();

//   if (count == 0) {
//     return;
//   }

//   int peak = 0;

//   for (int i = 0; i < count; i++) {
//     int magnitude = workingBuffer[i];

//     if (magnitude < 0) {
//       magnitude = -magnitude;
//     }

//     if (magnitude > peak) {
//       peak = magnitude;
//     }
//   }

//   unsigned long now = millis();

//   if (peak >= SOUND_THRESHOLD) {
//     lastLoudTime = now;

//     if (soundArmed) {
//       soundEvents++;
//       soundArmed = false;

//       Serial.print("Sound event: ");
//       Serial.println(soundEvents);
//     }
//   }
//   else if (now - lastLoudTime >= QUIET_TIME_MS) {
//     soundArmed = true;
//   }
// }

