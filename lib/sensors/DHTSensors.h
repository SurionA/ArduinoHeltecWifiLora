#include "DHTesp.h"

#ifndef hc_dhtsensors_h
#define hc_dhtsensors_h

class HC_DHTSensorsClass: public DHTesp {
    public:
        void displayTempHumidityOnOled();
};

extern HC_DHTSensorsClass DHTSensors;

#endif