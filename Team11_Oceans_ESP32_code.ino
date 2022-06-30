#include "DHTesp.h"
#include<WiFi.h>
const char* ssid = "vivo Y73";
const char* password =  "12345678";
const byte led_gpio_green = 25;
const byte led_gpio_red = 26;
const uint16_t port = 8090;
const char * host = "192.168.199.212";
#define DHTpin 15    //D15 of ESP32 DevKit

DHTesp dht;

void setup()
{
  pinMode(led_gpio_green, OUTPUT);
  pinMode(led_gpio_red, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17

}

void loop()
{
  
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
  Serial.println("Connected to server successful!");

  
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(temperature, 1);
  Serial.print("\t");
  if (temperature > 23){
        digitalWrite(led_gpio_green, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);                       // wait for a second
        digitalWrite(led_gpio_green, LOW);    // turn the LED off by making the voltage LOW
      delay(100); 
      Serial.print("LED glow");
      Serial.print("\n");
      client.print(temperature);
    }
  else {
    digitalWrite(led_gpio_red, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);                       // wait for a second
        digitalWrite(led_gpio_red, LOW);    // turn the LED off by making the voltage LOW
      delay(100); 
      Serial.print("LED glow");
      Serial.print("\n");
      client.print(temperature);
    
    
    }
 
}
