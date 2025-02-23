/****************************************************************
*                                                               *
*   Responder.hpp                                               *
*                                                               *
*   Object intended to only respond to certain events.          *
*                                                               *
*****************************************************************/
#ifndef RESPONDER_HPP
#define RESPONDER_HPP

#include <vector>
#include <functional>
#include "Events/Event.hpp"
#include "Events/EventEmitter.hpp"



// ## Responder
// Class representing some kind of responder object meant to listen to many events to monitor or control based on those events.
// The `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
// ### Parameters
// - `e` - The global `EventEmitter` object.
// - `events` (optional) - A list of `EventType`s (the responder will be registered to receive events of these types).
// - `handler` (optional) - An `onEvent` function that will be called whenever the responder receives an event it is registered for.
class Responder : public EventListener {
public:
    // ## Responder
    // Class representing some kind of responder object meant to listen to many events to monitor or control based on those events.
    // The `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
    // ### Parameters
    // - `e` - The global `EventEmitter` object.
    // - `events` (optional) - A list of `EventType`s (the responder will be registered to receive events of these types).
    // - `handler` (optional) - An `onEvent` function that will be called whenever the responder receives an event it is registered for.
    Responder(
        EventEmitter& emitter,
        const std::vector<EventType>& events = {},
        std::function<void(const Event&)> handler = nullptr
    ) : EventListener(events, handler) { emitter.AddEventListener(this); }
};



#endif // RESPONDER_HPP