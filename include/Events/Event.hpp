/****************************************************************
*                                                               *
*   Event.hpp                                                   *
*                                                               *
*   `Event` struct and `EventType` enum class definitions.      *
*                                                               *
*****************************************************************/
#ifndef EVENT_HPP
#define EVENT_HPP

#include <Arduino.h>



// ## EventType
// Class defining different event types.
// Events of these types are what gets emitted and registered for by sensors/controllers/listeners.
// ### Defined event types:
// - `SWITCH1_STATE_CHANGE`
// - `SWITCH2_STATE_CHANGE`
// - `SWITCH1_STATE_CHANGE_TO_LOW`
// - `SWITCH1_STATE_CHANGE_TO_HIGH`
enum class EventType {
    // SWITCH1_STATE_CHANGE,
    // SWITCH2_STATE_CHANGE,
    SWITCH1_STATE_CHANGE_TO_LOW,
    SWITCH1_STATE_CHANGE_TO_HIGH,
};



// ## Event
// Struct defining the properties of an event.
// ### Defined properties:
// - `type` (`EventType`) - The type of event, as defined by the `EventType` class.
// - `value` (`float`) - The value associated with the event.
// - `type_string` (`String`) - A string representation of the event type (e.g. `"SWITCH1_STATE_CHANGE"` for `EventType::SWITCH2_STATE_CHANGE`).
struct Event {
    EventType type;
    float value;
    String type_string;
};



#endif // EVENT_HPP