// running light 1.0 by Frederick
// Simple running light example

void setup() {
    for(int n=9; n<=13; n=n+1){
        pinMode(n, OUTPUT);
    }
}

void loop() {
    for(int n=9; n<=13; n=n+1){
        digitalWrite(n, HIGH);
        delay(300);
        digitalWrite(n, LOW);
    }
}
    }
