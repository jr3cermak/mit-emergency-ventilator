// E-Vent Functions

void initLCD() {
  // Configure LCD size
  lcd.begin(LCD_CHARS, LCD_ROWS);  
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
