void ledOn() {
  digitalWrite(ledPin, 1);
}

void ledBlink() {
  digitalWrite(ledPin, 1);
  delay(100);
  digitalWrite(ledPin, 0);
  delay(100);
  digitalWrite(ledPin, 1);
  delay(100);
  digitalWrite(ledPin, 0);
  delay(100);
}