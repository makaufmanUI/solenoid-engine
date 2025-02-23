/****************************************************************
*                                                               *
*   Sensor.hpp                                                  *
*                                                               *
*   Sensor base-class declaration.                              *
*   All sensor-related objects inherit from this class.         *
*                                                               *
*****************************************************************/
#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <set>
#include <vector>
#include <functional>
#include <Ticker.h>
#include <Arduino.h>
#include "Events/Event.hpp"
#include "Events/EventEmitter.hpp"
#include "Events/EventListener.hpp"



// ## Sensor
// Base class for all sensor-related objects.
// The `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
// ### Parameters
// - `e` - The global `EventEmitter` object.
// - `events` - A list of event types (the sensor will be registered to receive events of these types).
// - `handler` - An `onEvent` function that will be called whenever the sensor receives an event it is registered for.
class Sensor : public EventListener {
protected:
    // ### `Sensor.timer`
    // Protected `Ticker` object that the sensor binds its `Read` method to, to enable continous polling.
    Ticker timer;

    // ### `Sensor.emitter`
    // Protected reference to the global `EventEmitter` object, for adding this sensor to its vector of listeners during object instantiation.
    EventEmitter& emitter;

public:
    // ## Sensor
    // Base class for all sensor-related objects.
    // The `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
    // ### Parameters
    // - `e` - The global `EventEmitter` object.
    // - `events` - A list of event types (the sensor will be registered to receive events of these types).
    // - `handler` - An `onEvent` function that will be called whenever the sensor receives an event it is registered for.
    Sensor(
        EventEmitter& e,
        const std::vector<EventType>& events = {},
        std::function<void(const Event&)> handler = nullptr
    ) : EventListener(events, handler), emitter(e) { emitter.AddEventListener(this); }

    
    // ### `Sensor.Begin()`
    // Begins the periodic polling of the sensor.
    // ### Parameters
    // - `update_interval` - How long to wait between each polling of the sensor, in milliseconds.
    void Begin(float update_interval) {
        // timer.attach(update_interval/1000.f, std::bind(&Sensor::Read, this));
        // timer.attach_ms_scheduled_accurate(update_interval, std::bind(&Sensor::Read, this));
        timer.attach_ms(update_interval, std::bind(&Sensor::Read, this));
    }

    // ### `Sensor.IsPolling()`
    // Checks if the sensor is actively polling.
    bool IsPolling() {
        return timer.active();
    }

    // ### `Sensor.StopPolling()`
    // Stops the periodic polling of the sensor.
    void StopPolling() {
        timer.detach();
    }

    // Pure virtual function to be implemented by derived classes
    virtual void Read() = 0;
};



#endif // SENSOR_HPP