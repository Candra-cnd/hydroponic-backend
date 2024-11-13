#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>


// DHT Sensor
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Definisi PIN

#define GREED_LED_PIN 5
#define YELLOW_LED_PIN 10
#define RED_LED_PIN 12
#define RELAY_PIN 7
#define BUZZER_PIN 9

// Pengaturan WiFi dan MQTT
const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* mqtt_server = "broker.hivemq.com";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Inisialisasi Pin Aktuator
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Koneksi ke WiFi
  setup_wifi();

  // Pengaturan client MQTT
  client.setServer(mqtt_server, 1883);

}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("HydroponicSystem")) {
      Serial.print("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Membaca data dari sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Apakah pembacaan berhasil?
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read fro DHT sensor!");
    return;
  }

  // Mengendalikan Aktuator berdasarkan kondisi
  if (temperature > 35) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitaWrite(BUZZER_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else if (temperature >= 30 && temperature <= 35) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    digitalWrite(GREED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Mengirim data ke MQTT
  if (!isnan(temperature) && !isnan(humidity)) {
    String suhuStr = String(temperature);
    String kelembapanStr = String(humidity);   
    String data = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
    client.publish("hydroponics/sensor", data.c_str());
  }

  // Mereset LED setelah delay
  delay(2000);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}
