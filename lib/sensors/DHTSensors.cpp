#include "heltec.h"
#include "DHTSensors.h"
#include "HC_Icons.h"

void HC_DHTSensorsClass::displayTempHumidityOnOled(){
    delay(getMinimumSamplingPeriod());

    String temperatureDisplay ="" + (String) getTemperature() + "°C";
    String humidityDisplay = "" + (String) getHumidity() + " %";

    Heltec.display->clear();

    Heltec.display->setFont(ArialMT_Plain_24);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);

    Heltec.display->drawIco16x16(10,6, HC_Icons::temperature_icon16x16);
    Heltec.display->drawString(74, 0, temperatureDisplay);

    Heltec.display->drawIco16x16(10,38, HC_Icons::humidity2_icon16x16);
    Heltec.display->drawString(74, 32, humidityDisplay);

    Heltec.display->display();
};

HC_DHTSensorsClass DHTSensors;