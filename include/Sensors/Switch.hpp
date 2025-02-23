/****************************************************************
*                                                               *
*   Switch.hpp                                                  *
*                                                               *
*   Class representing a mechanical or electrical switch.       *
*                                                               *
*****************************************************************/
#ifndef SWITCH_HPP
#define SWITCH_HPP

#include <vector>
#include <Wire.h>
#include <Arduino.h>
#include "Sensor.hpp"


// ## Switch
// Class representing a switch.
// The `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
// ### Parameters
// - `e` - The global `EventEmitter` object.
// - `pin` - The GPIO pin that the switch's output is connected to.
// - `events` (optional) - A list of `EventType`s (the switch will be registered to receive events of these types).
// - `handler` (optional) - An `onEvent` function that will be called whenever the switch receives an event it is registered for.
// ### Example Instantiation
// ```
// #define SWITCH_PIN 4
// EventEmitter event_emitter; 
// Switch switch(event_emitter, SWITCH_PIN);
// ```
class Switch : public Sensor {
private:
    // ### `Switch.pin`
    // Private integer defining which GPIO pin the switch's output is connected to.
    const int pin;

public:
    // ### `Switch.last_state`
    // The state `1`/`0` that the switch last read.
    int last_state;

    // ### `Switch.last_statechange_millis`
    // The timestamp of when the last state change occurred.
    unsigned long last_statechange_millis;

    // ## Switch
    // Class representing a switch.
    // The `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
    // ### Parameters
    // - `e` - The global `EventEmitter` object.
    // - `pin` - The GPIO pin that the switch's output is connected to.
    // - `events` (optional) - A list of `EventType`s (the switch will be registered to receive events of these types).
    // - `handler` (optional) - An `onEvent` function that will be called whenever the switch receives an event it is registered for.
    // ### Example Instantiation
    // ```
    // #define SWITCH_PIN 4
    // EventEmitter event_emitter; 
    // Switch switch(event_emitter, SWITCH_PIN);
    // ```
    Switch(
        EventEmitter& e,
        int pin,
        const std::vector<EventType>& events = {},
        std::function<void(const Event&)> handler = nullptr
    ) : Sensor(e, events, handler), pin(pin) {
            /* Define what should happen when the Sensor object is initialized */
            /* Could also define the OnEvent method below and assign it here with SetOnEvent(OnEvent) */
            pinMode(pin, INPUT);            // Designate pin as an input
            last_state = digitalRead(pin);      // Initialize the last_state variable
            last_statechange_millis = millis(); // Initialize the last_statechange_millis variable
    }

    // ### `Switch.Read()`
    // Defines how and what it means to read this switch, and under what condition it should emit an event.
    // This is the function bound to a `Ticker` object and is called continously at the interval specified in `Begin()`.
    void Read() override {
        int current_state = digitalRead(pin);
        if (current_state != last_state) {
            if (current_state == 1) {
                // Switch went from LOW to HIGH
                Event event = {EventType::SWITCH1_STATE_CHANGE_TO_HIGH, static_cast<float>(current_state), String("SWITCH1_STATE_CHANGE_TO_HIGH")};
                emitter.EmitEvent(event);
            }
            else if (current_state == 0) {
                // Switch went from HIGH to LOW
                Event event = {EventType::SWITCH1_STATE_CHANGE_TO_LOW, static_cast<float>(current_state), String("SWITCH1_STATE_CHANGE_TO_LOW")};
                emitter.EmitEvent(event);
            }
            last_state = current_state;
            last_statechange_millis = millis();
        }
        // if (current_state != last_state) {
        //     Event event = {EventType::SWITCH1_STATE_CHANGE, static_cast<float>(current_state), String("SWITCH1_STATE_CHANGE")};
        //     emitter.EmitEvent(event);
        //     last_state = current_state;
        // }
    }
};



#endif // SWITCH_HPP