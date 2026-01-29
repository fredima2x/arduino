#include <Wire.h> // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek
#include <WiFi.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LED_PIN = 3;
const int BUTTON_PIN = 12;

int Highscore = 0;
int BUTTON = 1;
int delta_time = 0;
int wait_time = 0;
int total_time = 0;
int attempt_count = 0;
int average_time = 0;
int server = 0; // 1 = connect to wifi, 0 = no wifi

void INIT() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.home();
    lcd.print("Reaction Test v3");
    delay(500);
    //INIT COMMANDS
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    randomSeed(analogRead(0));
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // WiFi connection
    if (server == 1) {
        WiFi.begin("TheFrediphone", "qualitativ");
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
        }
        Serial.println("WiFi connected");
    }

    lcd.clear();
}


void setup() {
    INIT();
}

void loop() {
    digitalWrite(LED_PIN, LOW);
    BUTTON = digitalRead(BUTTON_PIN);
    lcd.print("Press to start!");
    while (BUTTON == 1) {
        BUTTON = digitalRead(BUTTON_PIN);
    }
    lcd.home();     
    lcd.clear();
    lcd.print("Get Ready...");
    delay(2000);
    int waitTime = random(1000, 5000);  
    for (int i = 0; i < waitTime; i = i+1) {
        delay(1);
        BUTTON = digitalRead(BUTTON_PIN);
        if (BUTTON == 0) {
            digitalWrite(LED_PIN, LOW);
            lcd.clear();
            lcd.print("Too soon!");
            delay(2000);
            lcd.clear();
            return;
        }
    }
    delta_time=millis();
    lcd.clear();
    lcd.print("GO!");
    digitalWrite(LED_PIN, HIGH);  
    while (digitalRead(BUTTON_PIN) == 1) {
        BUTTON = digitalRead(BUTTON_PIN);
    }
    wait_time=millis()-delta_time;
    total_time = total_time + wait_time;
    attempt_count = attempt_count + 1;
    average_time = total_time / attempt_count;
    if (wait_time > 1000) {
        lcd.clear();
        lcd.print("Too slow!");
        delay(2000);
        lcd.clear();
        return;
    }
    if (wait_time < Highscore || Highscore == 0) {
        Highscore = wait_time;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("New Highscore!");
        lcd.setCursor(0, 1);
        lcd.print("Score: ");
        lcd.print(Highscore);
        delay(3000); 
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Score:");
        lcd.print(wait_time);
        lcd.setCursor(0, 1);
        delay(3000);
        lcd.clear();
        lcd.home();

        int percent = (Highscore * 100) / wait_time;
        if (percent > 100) percent = 100;

        lcd.print(percent);
        lcd.print("% of Highscore");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.setCursor(15, 1);
        lcd.print("]");
        int progress = min(14, (percent * 14) / 100);
        Serial.println(progress);
        Serial.println(percent);
        lcd.setCursor(1, 1);
        for (int i = 0; i < progress; i++) {
            lcd.print("=");
            delay(200);
        }
        delay(3000);
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Average: ");
    lcd.print(average_time);
    lcd.setCursor(0, 1);
    lcd.print("Attempts: ");
    lcd.print(attempt_count);
    delay(3000);
    lcd.clear();
    delay(1000);
}

// End of code
