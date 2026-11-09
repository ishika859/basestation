
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiUDP udp;
const unsigned int localPort = 4210;

#define BASE_TRIGGER 25

bool landingCommand = false;
bool waiting = false;
bool activated = false;

unsigned long landingTime = 0;

const unsigned long WAIT_TIME = 60000;

void setup() {
  Serial.begin(115200);

  pinMode(BASE_TRIGGER, OUTPUT);
  digitalWrite(BASE_TRIGGER, LOW);

  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");

  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  udp.begin(localPort);

  Serial.println("Waiting for drone data...");
}

void loop() {

  int packetSize = udp.parsePacket();

  if (packetSize) {

    char incoming[100];
    int len = udp.read(incoming, 99);

    if (len > 0) {
      incoming[len] = '\0';
    }

    String message = String(incoming);
    message.trim();

    Serial.print("Drone Data: ");
    Serial.println(message);

    if (message == "LANDING") {
      landingCommand = true;
      Serial.println("Drone is coming to land...");
    }

    if (message == "LANDED" && landingCommand && !activated) {

      landingTime = millis();
      waiting = true;

      Serial.println("Landing confirmed!");
      Serial.println("Waiting 60 seconds...");
    }
  }

  if (waiting && millis() - landingTime >= WAIT_TIME) {

    Serial.println("Activating Base Station!");

    digitalWrite(BASE_TRIGGER, HIGH);
    delay(1000);
    digitalWrite(BASE_TRIGGER, LOW);

    waiting = false;
    activated = true;

    Serial.println("Signal sent to Arduino");
  }
}
