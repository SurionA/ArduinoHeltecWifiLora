#include "heltec.h"

#include "DHTSensors.h"
#include "HC_WiFi.h"
#include "HC_Server.h"
#include "secrets.h"

void setup() {
    pinMode(LED,OUTPUT);
    digitalWrite(LED,HIGH);

    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, false /*Serial Enable*/);
    Heltec.display->clear();
    Heltec.display->display();

    HC_WiFi::connect((const char*) SECRETS::ssid, (const char*) SECRETS::password);

    DHTSensors.setup(27, DHTesp::DHT22);
    DHTSensors.displayTempHumidityOnOled();

    HC_Server::init();
    HC_Server::discoveryService();
}

void loop() {
    int i = 0;
    while (i < 2) {
        DHTSensors.displayTempHumidityOnOled();
        delay(10000);

        Heltec.display->clear();
        Heltec.display->display();
        delay(5000);

        i++;
    }

    HC_Server::sendEvent();
}