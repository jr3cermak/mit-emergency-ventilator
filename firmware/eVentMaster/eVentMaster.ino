/*
  E-Vent Firmware
  
  Requires Liquid Crystal Library

  Set points are stored into non-volitile RAM/EEPROM so that reboots will
  return to the exact same settings.

*/

// EEPROM Library
#include <EEPROM.h>
// Liquid Crystal library for LCD
#include <LiquidCrystal.h>
// I2C
#include <Wire.h>

// Splash screen stays up until the button is pressed for
// the first time.
bool splashActive = true;

// LCD Configuration & Pin Assignments
const int LCD_CHARS = 16;
const int LCD_ROWS = 2;
// Assignment Map: LED PIN = ARDUINO PIN
const int LCDrs = 12, LCDen = 11, LCDd4 = 10, LCDd5 = 9, LCDd6 = 8, LCDd7 = 7;
LiquidCrystal lcd(LCDrs, LCDen, LCDd4, LCDd5, LCDd6, LCDd7);

// Vent Mode
// 0 = Setup: Homing
// 1 = Run:   Operational/running with set points
int VENT_MODE = 0;

// Potentiometer Set Point Controls
// EEPROM Storage: This can be adjusted as EEPROM memory is used
const int EEPROM_SP_STORE = 0;
// Define your ADC bit size; in most cases, it is 10 bits
#define CUSTOM_ADC
// If you have more bits in your ADC, adjust that here and
// comment out the next line.
#undef CUSTOM_ADC
const int ADCsize = 10;
// Add a percent deadband at each end, the value below is
// percent.  Ex: 1024 * (DEADBAND/100.0)
float POT_CONTROL_DEADBAND = 5.0;
// POT_VOLUME_SP
const int POT_VOLUME_SP_PIN = A0;
int POT_VOLUME_SP_RAW = 0;
float POT_VOLUME_SP_SCALED = 0.0;
int POT_VOLUME_SP_STORED = 0;
// POT_BPM_SP
const int POT_BPM_SP_PIN = A1;
int POT_BPM_SP_RAW = 0;
float POT_BPM_SP_SCALED = 0.0;
int POT_BPM_SP_STORED = 0;
// POT_IE_RATIO_SP
const int POT_IE_RATIO_SP_PIN = A2;
int POT_IE_RATIO_SP_RAW = 0;
float POT_IE_RATIO_SP_SCALED = 0.0;
int POT_IE_RATIO_SP_STORED = 0;
// POT_PRES_SP
const int POT_PRES_SP_PIN = A3;
int POT_PRES_SP_RAW = 0;
float POT_PRES_SP_SCALED = 0.0;
int POT_PRES_SP_STORED = 0;
// SETPOINT_BUTTON
/* 
 * If the BUTTON is held on power up, the unit will be reset
 * and placed into Setup mode.
 * 
 * System is also placed into setup mode if the EEPROM read
 * is not sane.
 * 
 * Setup: 
 *  TODO: Perform homing or calibration operations
 *  (1) Allow various calibrations of the ventilator
 *  (2) A held press of more than one second will switch to operational mode
 * Operational:
 *  (1) A momentary press of the button will update set points
 *  (2) A held press of more than one second will switch to setup mode
 */
const int SETPOINT_BUTTON_MODE_PIN = 4;
int SETPOINT_BUTTON_MODE_STATE = 0;
int SETPOINT_BUTTON_MODE_STATE_LAST = 0;
int SETPOINT_BUTTON_MODE_DEBOUNCE_DELAY = 50;
int SETPOINT_BUTTON_MODE_HELD = 0;
int SETPOINT_BUTTON_MODE_HELD_IN_SETUP = 0;
// ALARM LED/BUZZER
int ALARM_LED_BUZZER_STATE = 0;

// DEBUG
int onePass = 0;

// FUNCTIONS

void setup() {
  // Read button state
  readSetPointModeButton();
  if (modeButtonPressed()) {
    SETPOINT_BUTTON_MODE_HELD_IN_SETUP = 1;
  }
  // Configure ADC Resolution (if available)
#ifdef CUSTOM_ADC
  analogReadResolution(ADCsize);
#endif
  // Configure LCD size
  initLCD();

  if (SETPOINT_BUTTON_MODE_HELD_IN_SETUP) {
    // Show spash screen
    showSplash();    
  } else {
    // readEEPROM
    readEEPROM();
  }
  // Configure I2C (Master)
  Wire.begin();
  // DEBUG
  showSplash();
}

// MAIN PROGRAM

void loop() {
  if (onePass == 0) {
    onePass = 1;
    Wire.beginTransmission(2);
    Wire.write("X is ");
    Wire.write(onePass);
    Wire.endTransmission();
  }
}
