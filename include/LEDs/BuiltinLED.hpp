/****************************************************************
*                                                               *
*   BuiltinLED.hpp                                              *
*                                                               *
*   NodeMCU built-in LED controller.                            *
*                                                               *
*****************************************************************/
#ifndef BUILTIN_LED_HPP
#define BUILTIN_LED_HPP

#include <Arduino.h>



// ## `BuiltinLED`
// NodeMCU built-in LED controller.
class BuiltinLED {
private:
    // ### `BuiltinLED.pin`
    // The GPIO pin number of the built-in LED (`2`).
    const unsigned int pin = 2;

    // ### `BuiltinLED.state`
    // The current state of the built-in LED (`0` / `1`).
    unsigned int state;

    // ### `BuiltinLED.state_str`
    // The current state of the built-in LED (`"OFF"` / `"ON"`).
    String state_str;

public:
    // ## `BuiltinLED`
    // NodeMCU built-in LED controller.
    BuiltinLED() { }

    // ### `BuiltinLED.last_state_change`
    // Stores the timestamp (`millis()`) of the last change of LED state.
    unsigned long last_state_change;

    // ### `BuiltinLED.Initialize()`
    // Initializes the built-in LED (sets its GPIO as OUTPUT).
    void Initialize() {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        state = 0;
        state_str = String("OFF");
        last_state_change = millis();
    }

    // ### `BuiltinLED.On()`
    // Turns the built-in LED on.
    void On() {
        digitalWrite(pin, HIGH);
        state = 1;
        state_str = String("ON");
        last_state_change = millis();
    }

    // ### `BuiltinLED.Off()`
    // Turns the built-in LED off.
    void Off() {
        digitalWrite(pin, LOW);
        state = 0;
        state_str = String("OFF");
        last_state_change = millis();
    }

    // ### `BuiltinLED.Toggle()`
    // Toggles the built-in LED:
    // - Turns it on if currently off
    // - Turns it off if currently on
    void Toggle() {
        if (state == 0) {
            On();
        } else {
            Off();
        }
    }

    // ### `BuiltinLED.GetState()`
    // Returns the current state (`0` / `1`) of the built-in LED.
    unsigned int GetState() {
        return state;
    }

    // ### `BuiltinLED.GetStateStr()`
    // Returns the current state (`"OFF"` / `"ON"`) of the built-in LED.
    String GetStateStr() {
        return state_str;
    }
};



#endif // BUILTIN_LED_HPP