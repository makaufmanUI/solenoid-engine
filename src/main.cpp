/****************************************************************
*                                                               *
*   main.cpp                                                    *
*                                                               *
*   Main file containing setup and loop code.                   *
*                                                               *
*****************************************************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "LEDs.h"
#include "Events.h"
#include "Sensors.h"
#include "WebServer/Data.hpp"
#include "WebServer/WebServer.h"

#define SWITCH1_PIN 14  // D5
#define SWITCH2_PIN 16  // D0
#define INA_SDA_PIN  4  // D2
#define INA_SCL_PIN  5  // D1


// Global objects
EventEmitter event_emitter;
BuiltinLED board_led = BuiltinLED();
Switch switch1(event_emitter, SWITCH1_PIN);
// Switch switch2(event_emitter, SWITCH2_PIN);
INA219 ina219(event_emitter, INA_SDA_PIN, INA_SCL_PIN);

// Web server object
WebServer server(80, "esp8266", "12345678");

// Global variables
double x_avg = 0.01346962;      // m
unsigned long t0 = millis();    // ms


// Event handlers
// void ina219_OnEvent(const Event& event) {
//     // Responding to SWITCH1_STATE_CHANGE_TO_LOW / SWITCH1_STATE_CHANGE_TO_HIGH
//     if (event.type == EventType::SWITCH1_STATE_CHANGE_TO_LOW) {
//         // State changed from HIGH to LOW
//         board_led.Off();
//         ina219.StopPolling();
//         double dt = (millis() - ina219.reading_began) / 1000.0;
//         float rpm = 30.0 / dt;
//         float force = 1 / (212.86 * dt * dt);
//         float torque = force * x_avg;
//         float voltage = ina219.measurements.voltage.GetAverage();
//         float current = ina219.measurements.current.GetAverage();
//         float powerin = voltage * current;
//         float powerout = (rpm * rpm * rpm) * (x_avg / 1829397.0);
//         float efficiency = powerout / powerin;
//         float temperature = ina219.measurements.temperature.GetAverage();
//         float elapsed = (millis() - t0) / 1000.0;
//         Data data;
//         data.speed = rpm;
//         data.torque = torque * 1000.0;          // N·m -> N·mm
//         data.voltage = voltage;
//         data.current = current;
//         data.powerin = powerin;
//         data.powerout = powerout;
//         data.efficiency = efficiency * 100.0;   // d% -> %
//         data.temperature = temperature;
//         data.elapsed = elapsed;
//         server.UpdateData(&data);
//     }
//     else if (event.type == EventType::SWITCH1_STATE_CHANGE_TO_HIGH) {
//         // State changed from LOW to HIGH
//         board_led.On();
//         ina219.reading_began = millis();
//         ina219.Begin(2);
//     }
// }
void ina219_OnEvent(const Event& event) {
    // Responding to SWITCH1_STATE_CHANGE_TO_LOW / SWITCH1_STATE_CHANGE_TO_HIGH
    if (event.type == EventType::SWITCH1_STATE_CHANGE_TO_LOW) {
        // State changed from HIGH to LOW
        board_led.Off();
        ina219.StopPolling();
        float dt = (millis() - ina219.reading_began) / 1000.0;
        float rpm = 30.0 / dt;
        float force = 1 / (212.86 * dt * dt);
        float torque = force * x_avg;
        float voltage = ina219.measurements.voltage.GetAverage();
        float current = ina219.measurements.current.GetAverage();
        float powerin = voltage * current;
        float powerout = (rpm * rpm * rpm) * (x_avg / 1829397.0);
        float efficiency = powerout / powerin;
        float temperature = ina219.measurements.temperature.GetAverage();
        float elapsed = (millis() - t0) / 1000.0;

        server.incoming_data.speed = rpm;
        server.incoming_data.torque = torque * 1000.0;          // N·m -> N·mm
        server.incoming_data.voltage = voltage;
        server.incoming_data.current = current;
        server.incoming_data.powerin = powerin;
        server.incoming_data.powerout = powerout;
        server.incoming_data.efficiency = efficiency * 100.0;   // .% -> %
        server.incoming_data.temperature = temperature;
        server.incoming_data.elapsed = elapsed;
    }
    else if (event.type == EventType::SWITCH1_STATE_CHANGE_TO_HIGH) {
        // State changed from LOW to HIGH
        board_led.On();
        ina219.reading_began = millis();
        ina219.Begin(2);
    }
}





void setup()
{
    board_led.Initialize();
    Serial.begin(115200);
    
    // Register events & set callback
    ina219.RegisterForEvents({
        EventType::SWITCH1_STATE_CHANGE_TO_LOW,
        EventType::SWITCH1_STATE_CHANGE_TO_HIGH
    });
    ina219.SetOnEvent(ina219_OnEvent);

    // Start switch polling
    switch1.Begin(1);

    // Start webserver
    server.Start();

    // Schedule webserver updates
    server.ScheduleUpdates(250);

    // Start INA219 polling if switch1 state is HIGH
    if (switch1.last_state == 1) {
        ina219.reading_began = millis();
        ina219.Begin(2);
    }
}





void loop()
{
    yield();
}

