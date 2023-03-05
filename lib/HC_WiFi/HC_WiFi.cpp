#include "WiFi.h"
#include "heltec.h"

#include "HC_WiFi.h"
namespace HC_WiFi {

    String hostname = "HC_esp32_node_1";

    void connect(const char* ssid, const char *passphrase, int32_t channel, const uint8_t* bssid, bool connect) {

        WiFi.mode(WIFI_STA);
        WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
        WiFi.setHostname(hostname.c_str());

        WiFi.begin(ssid, passphrase, channel, bssid, connect);

        Heltec.display->setFont(ArialMT_Plain_10);
        Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);

        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Heltec.display->clear();
            Heltec.display->drawString(64, 24, "Connecting to WiFi..");
            Heltec.display->display();
        }

        IPAddress ip = WiFi.localIP();

        Heltec.display->clear();
        Heltec.display->drawString(64, 12, (String) ip.toString());
        Heltec.display->drawString(64, 36, (String) WiFi.getHostname());

        Heltec.display->display();

        delay(5000);
    };

}