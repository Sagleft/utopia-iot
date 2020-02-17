void resetIndicator() {
  digitalWrite(D5, LOW); //R
  digitalWrite(D6, LOW); //G
  digitalWrite(D7, LOW); //B
}

void indicateAlert() {
  resetIndicator();
  digitalWrite(D6, HIGH);
}

void indicateErr() {
  resetIndicator();
  digitalWrite(D5, HIGH);
}

void indicateUnknown() {
  resetIndicator();
  digitalWrite(D7, HIGH);
}