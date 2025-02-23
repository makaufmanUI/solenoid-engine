/****************************************************************
*                                                               *
*   WebServer.cpp                                               *
*                                                               *
*   Asynchronous WiFi webserver hosted by the NodeMCU.          *
*                                                               *
*****************************************************************/
#include "Data.hpp"
#include "WebServer.h"
#include "IndexHTML.hpp"



WebServer::WebServer(int port, const char* ssid, const char* password)
    : port(port), ssid(ssid), password(password), server(port), events("/events")
{
    // Other initialization
    incoming_data.speed        = 0.0;
    incoming_data.torque       = 0.0;
    incoming_data.voltage      = 0.0;
    incoming_data.current      = 0.0;
    incoming_data.powerin      = 0.0;
    incoming_data.powerout     = 0.0;
    incoming_data.efficiency   = 0.0;
    incoming_data.temperature  = 0.0;
    incoming_data.elapsed      = 0.0;
}



void WebServer::OnRoot(AsyncWebServerRequest* request)
{
    request->send_P(
        200,
        "text/html",
        index_html
    );
}



void WebServer::Start()
{
    // Start the SoftAP
    // Serial.print("Starting Access Point... ");
    started = WiFi.softAP(ssid, password, 6);
    // Serial.println(started == true ? "success." : "failed.");

    ip_address = WiFi.softAPIP();
    mac_address = WiFi.macAddress();
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest* request) {
        this->OnRoot(request);
    });
    events.onConnect([](AsyncEventSourceClient* client){
        if (client->lastId()) {
            Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
        }
        // client->send("Hello!", NULL, millis(), 5000);
        client->send("Hello!", NULL, millis());
    });
    server.addHandler(&events);

    // Start the web server
    // Serial.print("Starting web server... ");
    server.begin();
    // Serial.println("done.");

    // Serial.print("Acess Point IP Address: ");
    // Serial.println(ip_address.toString());

    WiFi.setOutputPower(20.5);
}



JSONVar WebServer::ToJSON(const Data* data)
{
    JSONVar json_data;

    json_data["speed"] = (*data).speed;
    json_data["torque"] = (*data).torque;
    json_data["voltage"] = (*data).voltage;
    json_data["current"] = (*data).current;
    json_data["powerin"] = (*data).powerin;
    json_data["powerout"] = (*data).powerout;
    json_data["efficiency"] = (*data).efficiency;
    json_data["temperature"] = (*data).temperature;
    json_data["elapsed"] = (*data).elapsed;

    return json_data;
}



void WebServer::UpdateWithStoredData()
{
    JSONVar json_data;

    json_data["speed"] = incoming_data.speed;
    json_data["torque"] = incoming_data.torque;
    json_data["voltage"] = incoming_data.voltage;
    json_data["current"] = incoming_data.current;
    json_data["powerin"] = incoming_data.powerin;
    json_data["powerout"] = incoming_data.powerout;
    json_data["efficiency"] = incoming_data.efficiency;
    json_data["temperature"] = incoming_data.temperature;
    json_data["elapsed"] = incoming_data.elapsed;

    String jsonString = JSON.stringify(json_data);
    events.send(jsonString.c_str(), "new_data", millis());
}



void WebServer::UpdateData(const Data* data)
{
    JSONVar json_data;
    const uint8_t* data_obj = (uint8_t*) data;
    memcpy(&incoming_data, data_obj, sizeof(incoming_data));

    json_data["speed"] = incoming_data.speed;
    json_data["torque"] = incoming_data.torque;
    json_data["voltage"] = incoming_data.voltage;
    json_data["current"] = incoming_data.current;
    json_data["powerin"] = incoming_data.powerin;
    json_data["powerout"] = incoming_data.powerout;
    json_data["efficiency"] = incoming_data.efficiency;
    json_data["temperature"] = incoming_data.temperature;
    json_data["elapsed"] = incoming_data.elapsed;

    String jsonString = JSON.stringify(json_data);
    events.send(jsonString.c_str(), "new_data", millis());
}



void WebServer::ScheduleUpdates(float update_interval)
{
    // timer.attach_ms(update_interval, std::bind(&WebServer::UpdateWithStoredData, this));
    timer.attach_ms_scheduled_accurate(update_interval, std::bind(&WebServer::UpdateWithStoredData, this));
}



void WebServer::StopUpdates()
{
    timer.detach();
}