/****************************************************************
*                                                               *
*   EventListener.hpp                                           *
*                                                               *
*   EventListener class definition.                             *
*                                                               *
*****************************************************************/
#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include <set>
#include "Event.hpp"



// ## EventListener
// Event listener interface class.
// This class is inherited by the base `Sensor` class and the `Controller` class.
// Both the `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
// ### Parameters
// - `events` - A list of event types (the inheriting object will be registered to receive events of these types).
// - `handler` - An `onEvent` function that will be called whenever the inheriting object receives an event it is registered for.
class EventListener {
protected:
    // ### `EventListener.registered_events`
    // Protected set of `EventType` objects.
    // The event types contained in this set are the events that the inheriting object is registered for and will be notified of.
    // It is populated in one of two ways:
    // - During instantiation via the `events` parameter
    // - After object instantiation, via the `RegisterForEvent` or `RegisterForEvents` method
    // ```c++
    // // During instantiation
    // SomeSensor(event_emitter, {EventType::TEMPERATURE_CHANGE});
    // 
    // // Via the SetOnEvent method
    // SomeSensor sensor(event_emitter);
    // sensor.RegisterForEvent(EventType::TEMPERATURE_CHANGE);
    // sensor.RegisterForEvent({EventType::TEMPERATURE_CHANGE, EventType::HALL_EFFECT_CHANGE});
    // ```
    std::set<EventType> registered_events;

    // ### `EventListener.event_handler`
    // Protected function used as the `onEvent` callback for the inheriting object when receiving an event.
    // It can be defined in one of two ways:
    // - During instantiation via the `handler` parameter
    // - After object instantiation, via the `SetOnEvent` method
    // ```c++
    // // During instantiation
    // SomeSensor(
    //     event_emitter,
    //     {EventType::TEMPERATURE_CHANGE},
    //     [](const Event& event) { /* onEvent logic */ }
    // );
    // 
    // // Via the SetOnEvent method
    // SomeSensor sensor(event_emitter);
    // sensor.SetOnEvent(
    //     [](const Event& event) { /* onEvent logic */ }
    // );
    // ```
    std::function<void(const Event&)> event_handler;

public:
    // ## EventListener
    // Event listener interface class.
    // This class is inherited by the base `Sensor` class and the `Controller` class.
    // Both the `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
    // ### Parameters
    // - `events` - A list of event types (the inheriting object will be registered to receive events of these types).
    // - `handler` - An `onEvent` function that will be called whenever the inheriting object receives an event it is registered for.
    EventListener(
        const std::vector<EventType>& events = {},
        std::function<void(const Event&)> handler = nullptr
    ) : registered_events(events.begin(), events.end()), event_handler(handler) {
        if (!event_handler) {
            event_handler = [](const Event& event) {
                Serial.println("[Default Handler] Event received but no custom handler set.");
            };
        }
    }

    // ### `EventListener.OnEvent()`
    // A wrapper for the inheriting object's (sensor/controller) event handler function.
    // The wrapping of the event handler is done so a check can be performed that ensures the inheriting object is registered for the given event first.
    // This method is called automatically when the global event emitter's `EmitEvent` method is called, the condition of which is defined in the inheriting object's `Read` method.
    // Because the global event emitter handles the invoking of this function, it should never need to be called directly.
    // ### Parameters
    // - `event` - An `Event` struct with the following properties:
    //      --> `value` (`float`) - The value associated with the event.
    //      --> `type` (`EventType`) - The type of event, as defined by the `EventType` class.
    //      --> `type_string` (`String`) - A string representation of the event type (e.g. `"TEMPERATURE_CHANGE"` for `EventType::TEMPERATURE_CHANGE`).
    void OnEvent(const Event& event) {
        if (IsRegisteredFor(event.type)) {
            event_handler(event);
        }
    }

    // ### `EventListener.IsRegisteredFor()`
    // Checks if the inheriting object is explicitly registered for a given `EventType`.
    // It is called automatically when the global event emitter's `EmitEvent` method is called, before invoking the inheriting object's `onEvent` function/event handler.
    // Because the global event emitter indirectly handles the invoking of this function, it should never need to be called directly.
    // ### Parameters
    // - `type` - An `EventType` enum (i.e. `EventType::TEMPERATURE_CHANGE`).
    bool IsRegisteredFor(EventType type) const {
        return registered_events.find(type) != registered_events.end();
    }

    // ### `EventListener.SetOnEvent()`
    // Sets the `onEvent` function/event handler of the object.
    // This event handler is what is called whenever an event is received that the object is registered for.
    // ### Parameters
    // - `function` - A `void` return-type function with a single `const Event& event` parameter.
    // 
    // This function can be passed in when pre-defined or can be defined inline:
    // ```c++
    // // Defining function inline
    // SomeSensor sensor(event_emitter);
    // sensor.SetOnEvent(
    //     [](const Event& event) { /* onEvent logic */ }
    // );
    // 
    // // Passing a pre-defined function
    // void sensorOnEvent(const Event& event) { /* onEvent logic */ }
    // SomeSensor sensor(event_emitter);
    // sensor.SetOnEvent(sensorOnEvent);
    // ```
    void SetOnEvent(std::function<void(const Event&)> function) {
        event_handler = function;
    }

    // ### `EventListener.RegisterForEvent()`
    // Registers the object for an event.
    // Once registered, the object's `onEvent` function/event handler will be called whenever an event of that type is emitted.
    // ### Parameters
    // - `event` - An `EventType` enum (i.e. `EventType::TEMPERATURE_CHANGE`).
    // ```c++
    // // Example
    // SomeSensor sensor(event_emitter);
    // sensor.RegisterForEvent(EventType::TEMPERATURE_CHANGE);
    // ```
    void RegisterForEvent(EventType event) {
        registered_events.insert(event);
    }

    // ### `EventListener.RegisterForEvents()`
    // Registers the object for several events.
    // Once registered, the object's `onEvent` function/event handler will be called whenever an event of one of these types is emitted.
    // ### Parameters
    // - `events` - A vector of `EventType` enums (i.e. `EventType::TEMPERATURE_CHANGE`).
    // ```c++
    // // Example
    // SomeSensor sensor(event_emitter);
    // sensor.RegisterForEvents({EventType::TEMPERATURE_CHANGE, EventType::HALL_EFFECT_CHANGE});
    // ```
    void RegisterForEvents(const std::vector<EventType>& events) {
        registered_events.insert(events.begin(), events.end());
    }
};



#endif // EVENT_LISTENER_HPP