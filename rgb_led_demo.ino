void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  for (int a=0; a<=255; a=a+1) {
    for (int b=0; b<=255; b=b+1) {
      for (int c=0; c<=255; c=c+1) {
        analogWrite(9, a);
        analogWrite(10, b);
        analogWrite(11, c);
      }
    }
  }
}
