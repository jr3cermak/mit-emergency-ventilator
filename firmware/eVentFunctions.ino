// E-Vent Functions

void initLCD() {
  // Configure LCD size
  lcd.begin(LCD_CHARS, LCD_ROWS);  
}

// Read stored values for ventilator
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
