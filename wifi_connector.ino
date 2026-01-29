#include <WiFi.h>
#include <HTTPClient.h>

#define BUTTON_PIN 21

const char* ssid = "TheFrediphone";
const char* password = "qualitativ";
int buttonState;

void get_network_info() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("[*] Network information for ");
    Serial.println(ssid);

    Serial.println("[+] BSSID : " + WiFi.BSSIDstr());
    Serial.print("[+] Gateway IP : ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("[+] Subnet Mask : ");
    Serial.println(WiFi.subnetMask());
    Serial.println((String)"[+] RSSI : " + WiFi.RSSI() + " dB");
    Serial.print("[+] ESP32 IP : ");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  get_network_info();
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    http.begin("https://fredima.de/lamp/off.php"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
    if (httpCode > 0) { //Check for the returning code
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end(); //Free the resources
    delay(2000);
  }
}
