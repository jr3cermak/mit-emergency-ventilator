// E-Vent Functions

// Initialize LCD display
void initLCD() {
  // Configure LCD size
  lcd.begin(LCD_CHARS, LCD_ROWS);  
}

// Initialize MegaMotoPlus board
void initMMP() {
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(MMP_EnablePin, OUTPUT);     
  pinMode(MMP_PWMA_Pin, OUTPUT);
  pinMode(MMP_PWMB_Pin, OUTPUT);
  // change Timer divisor to 8 gives 3.9kHz PWM freq
  setPwmFrequency(MMP_PWMA_Pin, 8);
}

// Read stored values for ventilator
// Memory layout in reference to EEPROM_SP_STORE
// 0    : SERIAL NUMBER
// 1    : POT_VOLUME_SP_STORE
// 2    : POT_BPM_SP_STORE
// 3    : POT_IE_RATIO_STORE
// 4    : POT_PRES_SP
// 5    : VENT_MODE
// TODO: Additional space for calibration values
void readEEPROM() {
  
}

void showSplash() {
  // Show spash screen
  // setCursor(COL,ROW)
  lcd.setCursor(0, 0);
  lcd.print("MIT E-Vent");
  lcd.setCursor(0, 1);
  lcd.print("V0.0 04/04/2020");
}

// Mega Moto Plus Functions

/*
 * Divides a given PWM pin frequency by a divisor.
 * 
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 * 
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired (Timer0)
 *   - Pins 9 and 10 are paired (Timer1)
 *   - Pins 3 and 11 are paired (Timer2)
 * 
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 5, 6 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 * 
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1235060559/0#4
 */
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) { // Timer0 or Timer1
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) { 
      TCCR0B = TCCR0B & 0b11111000 | mode; // Timer0
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode; // Timer1
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode; // Timer2
  }
}
