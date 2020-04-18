// E-Vent Sensors

// Clip potientiometers at the set deadband
int deadbandClipping(int rawValue) {
  
}

// POT_VOLUME_SP
void readPotVolume() {
  POT_VOLUME_SP_RAW = analogRead(POT_VOLUME_SP_PIN);
  return;
}

// POT_BPM_SP

// POT_IE_RATIO_SP

// POT_PRES_SP

// SETPOINT_MODE_BUTTON
void readSetPointModeButton() {
  SETPOINT_BUTTON_MODE_STATE = digitalRead(SETPOINT_BUTTON_MODE_PIN);
}

bool modeButtonPressed() {
  if (SETPOINT_BUTTON_MODE_STATE == 1) {
    return true;
  } else {
    return false;
  }
}
