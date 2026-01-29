// candle dimmer by fredima2x v1.0

void setup() {
  pinMode(9, OUTPUT);
  randomSeed(analogRead(A1));
}

void loop() {
  int s=random(0, 256);
  analogWrite(9, s);
  delay(100);
}
