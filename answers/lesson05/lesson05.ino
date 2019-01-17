/* Redd Plantene
 * @author: Nikhil André Luthra - Bouvet Norge
 * @author: Christer Nordbø - Bouvet Norge
 * @web: reddplantene.labben.org / bouvet.no/reddplantene
 * @web: bouvet.no / nikhil.luthra.no / cnordbo.no
 */
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Fyll ut med SSID og passord
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// Fyll ut ApiKey og Kanal
const char * ApiKey = "";
unsigned long Kanal = 0;

#define MOISTURE_PIN A0
#define MOISTURE_POWER_PIN D7

WiFiClient MyClient;

void setup() {
  Serial.begin(115200);
  pinMode(MOISTURE_PIN, INPUT);
  
  pinMode(MOISTURE_POWER_PIN, OUTPUT);
  digitalWrite(MOISTURE_POWER_PIN, LOW);

  //Oppgave: Initialiser ThingSpeak klienten
 
  ThingSpeak.begin(MyClient);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  digitalWrite(MOISTURE_POWER_PIN, HIGH);
  delay(300);
  
  int sensorValue = analogRead(MOISTURE_PIN);
  
  delay(100);
  digitalWrite(MOISTURE_POWER_PIN, LOW);
  
  // Oppgave: Send inn sensorValue verdien til ThingSpeak
  int responseCode = ThingSpeak.writeField(Kanal,1,sensorValue,ApiKey);
  
  // Oppgave: Sjekk at forespørselen gikk gjennom, skriv ut en feilmelding om ikke. 
  if(responseCode == 200) {
    Serial.print("Value sent to thingspeak: ");
    Serial.println(sensorValue);
  } else {
    Serial.print("Error sending data: ");
    Serial.println(responseCode);
  }

  delay(15000);
}
