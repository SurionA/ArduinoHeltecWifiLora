
#ifndef hc_wifi_h
#define hc_wifi_h

        namespace HC_WiFi {

                void connect(const char* ssid, const char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL, bool connect = true);

        }

#endif