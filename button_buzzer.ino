int i;
int e;
void setup() {
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  i=digitalRead(4);
  if (i==0) {
    tone(11, 500);
  } else {
    noTone();
  }
  e=digitalRead(5);
  if (e==0) {
    tone(11, 100);
  } else {
    noTone();
  }
}
