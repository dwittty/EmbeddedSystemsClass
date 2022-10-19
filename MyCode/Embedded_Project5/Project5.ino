#include <ESP8266WiFi.h>
#include <DHTesp.h>


//Replace these with your wifi network settings
const char* ssid = "MySSID"; //wifi network name
const char* password = "Mypass"; //pwd
DHTesp dht;

void setup(){
    delay(1000);
    Serial.begin(115200);

    WiFi.begin(ssid,password);

    Serial.println();
    Serial.print("Connecting");
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    Serial.println("success!");
    Serial.print("IP Address is: ");
    Serial.println(WiFi.localIP());
    dht.setup(12, DHTesp::DHT11);
}

void loop(){    
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    Serial.print("Humidity: " );
    Serial.println(humidity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    delay(5000);
}

