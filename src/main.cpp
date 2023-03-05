#include "heltec.h"

#include "DHTSensors.h"
#include "HC_WiFi.h"
#include "HC_Server.h"
#include "secrets.h"


void setup() {
    pinMode(LED,OUTPUT);
    digitalWrite(LED,HIGH);

    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, false /*Serial Enable*/);

    HC_WiFi::connect((const char*) SECRETS::ssid, (const char*) SECRETS::password);

    DHTSensors.setup(27, DHTesp::DHT22);
    DHTSensors.displayTempHumidityOnOled();

    HC_Server::init();
    HC_Server::discoveryService();

}



void loop() {
    DHTSensors.displayTempHumidityOnOled();
    delay(5000);
	Heltec.display->clear();
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
    Heltec.display->drawString(64, 24, ESP.getChipModel());

	Heltec.display->display();
    delay(5000);

}