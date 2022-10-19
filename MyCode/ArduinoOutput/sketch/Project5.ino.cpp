#include <Arduino.h>
#line 1 "c:\\Users\\David\\Documents\\GitHub\\EmbeddedSystemsClass\\MyCode\\Project5\\Project5.ino"
#include <ESP8266WiFi.h>

//Replace these with your wifi network settings
const char* ssid = "The Internet"; //wifi network name
const char* password = "1Witts23k"; //pwd

#line 7 "c:\\Users\\David\\Documents\\GitHub\\EmbeddedSystemsClass\\MyCode\\Project5\\Project5.ino"
void setup();
#line 25 "c:\\Users\\David\\Documents\\GitHub\\EmbeddedSystemsClass\\MyCode\\Project5\\Project5.ino"
void loop();
#line 7 "c:\\Users\\David\\Documents\\GitHub\\EmbeddedSystemsClass\\MyCode\\Project5\\Project5.ino"
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
}

void loop(){

}


