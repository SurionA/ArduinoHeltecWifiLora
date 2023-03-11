#include "ESPAsyncWebServer.h"
#include "DHTSensors.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "WiFi.h"

namespace HC_Server {
  AsyncWebServer server(80);
  AsyncWebServer discoveryServer(1707);

  AsyncEventSource events("/events");

  JsonObject getTmpHumPayload(JsonObject root) {
    delay(DHTSensors.getMinimumSamplingPeriod());

    float temperature = DHTSensors.getTemperature();
    float humidity =  DHTSensors.getHumidity();

    JsonObject temperatureObject = root.createNestedObject("temperature");
    temperatureObject["value"] = temperature;
    temperatureObject["unit"] = "°C";

    JsonObject humidityObject = root.createNestedObject("humidity");
    humidityObject["value"] = humidity;
    humidityObject["unit"] = "%";

    return root;
  }

  void init() {
    server.on("/8d777f385d3dfec8815d20f7496026dc", HTTP_ANY, [](AsyncWebServerRequest * request) {

      AsyncJsonResponse * response = new AsyncJsonResponse();
      response->addHeader("Server","ESP Async Web Server");

      JsonObject root = getTmpHumPayload(response->getRoot());

      response->setLength();
      request->send(response);
    });

  // events.onConnect([](AsyncEventSourceClient *client){
  //     if(client->lastId()){
  //       // Serial.printf("Client reconnected! Last message ID that it gat is: %u\n", client->lastId());
  //     }

  //     client->send(WiFi.getHostname(),NULL,millis(),1000);
  //   });

    server.addHandler(&events);

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

    server.begin();
  }

  void sendEvent() {
    DynamicJsonDocument doc(1024);

    JsonObject payload = getTmpHumPayload(doc.to<JsonObject>());

    String payload_string;
    serializeJson( payload, payload_string);

    events.send(payload_string.c_str(),"message",millis());
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