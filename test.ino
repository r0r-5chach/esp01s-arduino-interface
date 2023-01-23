#include "SoftwareSerial.h"
#include "Wifi.h"

Wifi* wifi;
String msg;

const int buttonPin = 7;
int buttonState = 0;
String wifiName = 'WIFINAME';
String wifiPass = 'WIFIPASS';

void setup()
{
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
    wifi = new Wifi();
    Serial.println(wifi -> checkStartup());
    Serial.println(wifi -> restart());
    Serial.println(wifi -> connect(wifiName, wifiPass));
}

void loop()
{
    buttonState = digitalRead(buttonPin);

    if(buttonState == HIGH) {
        Serial.println(wifi -> startConnection("UDP", "192.168.1.70", 5000));
        Serial.println(wifi -> send("hello"));
        Serial.println(wifi -> stopConnection());
    }
}