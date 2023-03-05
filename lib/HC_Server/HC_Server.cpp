#include "ESPAsyncWebServer.h"
#include "DHTSensors.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "WiFi.h"

namespace HC_Server {
  AsyncWebServer server(80);
  AsyncWebServer discoveryServer(1707);

  void init() {
    server.on("/8d777f385d3dfec8815d20f7496026dc", HTTP_ANY, [](AsyncWebServerRequest * request) {
      delay(DHTSensors.getMinimumSamplingPeriod());

      float temperature = DHTSensors.getTemperature();
      float humidity =  DHTSensors.getHumidity();

      AsyncJsonResponse * response = new AsyncJsonResponse();
      response->addHeader("Server","ESP Async Web Server");

      JsonObject root = response->getRoot();
      JsonObject temperatureObject = root.createNestedObject("temperature");
      temperatureObject["value"] = temperature;
      temperatureObject["unit"] = "°C";

      JsonObject humidityObject = root.createNestedObject("humidity");
      humidityObject["value"] = humidity;
      humidityObject["unit"] = "%";

      response->setLength();
      request->send(response);
    });

    server.begin();
  }

  void discoveryService() {

    discoveryServer.on("/54818b05d116eadc7f67517a3a6e4b33", HTTP_ANY, [](AsyncWebServerRequest * request) {

      IPAddress ip = WiFi.localIP();

      AsyncJsonResponse * response = new AsyncJsonResponse();
      response->addHeader("Server","ESP Async Web Server");

      JsonObject root = response->getRoot();
      root["ip"] = ip.toString();
      root["hostname"] = WiFi.getHostname();


      response->setLength();
      request->send(response);
    });

    discoveryServer.begin();

  }
}