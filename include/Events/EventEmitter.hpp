/****************************************************************
*                                                               *
*   EventEmitter.hpp                                            *
*                                                               *
*   EventEmitter class definition.                              *
*                                                               *
*****************************************************************/
#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include <vector>
#include "Event.hpp"
#include "EventListener.hpp"



// ## EventEmitter
// Class representing an event-emitting object.
// Only a single event emitter is required, and is passed to all sensor/controller objects.
class EventEmitter {
private:
    // ### `EventEmitter.listeners`
    // Private vector of pointers to `EventListener` objects.
    // This vector is automatically populated by new sensor/controller objects during instantiation.
    // When emitting an event of a particular type, only the listeners registered to that event type will be notified.
    std::vector<EventListener*> listeners;

public:
    // ### `EventEmitter.AddEventListener()`
    // Used to append new listeners to the `EventEmitter.listeners` vector on sensor/controller object instantiation.
    // Called automatically by all sensor objects from the base `Sensor` class and by all controller objects from the `Controller` class.
    // ### Parameters
    // - `listener` - A pointer to an `EventListener` object, which is passed automatically during sensor/controller object creation.
    void AddEventListener(EventListener* listener) {
        listeners.push_back(listener);
    }

    // ### `EventEmitter.EmitEvent()`
    // Emits an event.
    // This event is emitted to only those sensor/controller objects that are registered for it.
    // The specification of which sensor/controller objects are registered to which events is done in either their contructors or their `RegisterForEvent` methods.
    // ### Parameters
    // - `event` - An `Event` struct with the following properties:
    //      --> `value` (`float`) - The value associated with the event.
    //      --> `type` (`EventType`) - The type of event, as defined by the `EventType` class.
    //      --> `type_string` (`String`) - A string representation of the event type (e.g. `"TEMPERATURE_CHANGE"` for `EventType::TEMPERATURE_CHANGE`).
    void EmitEvent(const Event& event) {
        for (auto listener : listeners) {
            if (listener->IsRegisteredFor(event.type)) {
                listener->OnEvent(event);
            }
        }
    }
};



#endif // EVENT_EMITTER_HPP