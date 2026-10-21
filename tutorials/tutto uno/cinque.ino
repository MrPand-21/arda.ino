// Exercise 5: reading the analog temperature sensor. 
// We’ll follow the conversion from voltage to an ADC reading, 
// then from that reading to temperature

// The ADC, or Analog-to-Digital Converter, performs that conversion. 
// With the lab’s 10-bit reading resolution, there are: 2^10 = 1024 options

const int TEMP_LED = A0;
const unsigned long SAMPLE_INTERVAL_MS = 10000UL; // seconds

// math variables
const float R_FIXED = 100000.0;
const float R0 = 100000.0;
const float B = 4275.0;
const float T0_K = 298.15;


void setup(){
    analogReadResolution(10)
  Serial.begin(9600);
  while (!Serial) {
  }
}

void loop(){
    int raw = analogRead(TEMP_PIN);

    //We reject zero because it causes division by zero, 
    // and 1023 because the calculated resistance becomes zero, making log(0) invalid
    if(raw > 0 && raw < 1023){
        //The .0 makes this floating-point division. We need fractional results; 
        // integer division would lose them
        float resistance = (1023.0 / raw - 1.0) * R_FIXED; 
        temperatureKelvin = 1.0 / (log(resistance / R0) / B + 1.0 / T0_K);

        float temperatureC = temperatureKelvin - 273.15;
        Serial.print("Temperature: ");
         Serial.print(temperatureC, 2); //For a floating-point value, the second argument requests two decimal places.
        Serial.println(" C");
    }
    else {
         Serial.println("Reading outside conversion range, check the items");
    }


    delay(SAMPLE_INTERVAL_MS);

}