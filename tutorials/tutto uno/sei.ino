// Task: show temperature on an LCD using I²C.

// | Signal | Purpose | Pin on your lab board |
// | SDA | Carries data | A4 |
// | SCL | Carries the clock signal that coordinates communication | A5 |

#include <Wire.h> //handles I²C communication
#include <LiquidCrystal_PCF8574.h> //provides commands for this display

LiquidCrystal_PCF8574 lcd(0x27);
String lastDisplayed = "";

const int SDA_PIN = A4;
const int SCL_PIN = A5;
const int TEMP_LED = A0;

void setup(){
    analogReadResolution(10);

    Wire.begin();

    lcd.begin(16, 2); //Initialise a display with 16 columns and 2 rows 
    lcd.setBacklight(255); //Turn the backlight on
    lcd.clear();

    lcd.setCursor(0,0); //Choose where the next text starts (column first, row second)
    lcd.print("Temperature:");

}

void loop(){

    String text = "Sensor error";

    //We reject zero because it causes division by zero, 
    // and 1023 because the calculated resistance becomes zero, making log(0) invalid
    if(raw > 0 && raw < 1023){
        //The .0 makes this floating-point division. We need fractional results; 
        // integer division would lose them
        float resistance = (1023.0 / raw - 1.0) * R_FIXED; 
        temperatureKelvin = 1.0 / (log(resistance / R0) / B + 1.0 / T0_K);

        float temperatureC = temperatureKelvin - 273.15;
        text = String(temperatureC, 1) + " C";
    }

    if ( text != lastDisplayed){
        lcd.setCursor(0, 1);
        lcd.print(text);

        // Erase leftover characters from a longer old message.
        for (unsigned int i = text.length();i < lastDisplayed.length();i++) {
            lcd.print(' ');
        }

        lastDisplayed = text;
    }
}