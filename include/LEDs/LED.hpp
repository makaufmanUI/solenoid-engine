/****************************************************************
*                                                               *
*   LED.hpp                                                     *
*                                                               *
*   Generic LED controller.                                     *
*                                                               *
*****************************************************************/
#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>



// ## `LED`
// Generic LED controller.
class LED {
private:
    // ### `LED.pin`
    // The GPIO pin number of the LED (`2`).
    unsigned int pin;

    // ### `LED.state`
    // The current state of the LED (`0` / `1`).
    unsigned int state;

    // ### `LED.state_str`
    // The current state of the LED (`"OFF"` / `"ON"`).
    String state_str;

public:
    // ## `LED`
    // Generic LED controller.
    LED(const unsigned int pin) : pin(pin) { }

    // ### `LED.last_state_change`
    // Stores the timestamp (`millis()`) of the last change of LED state.
    unsigned long last_state_change;

    // ### `LED.Initialize()`
    // Initializes the LED (sets its GPIO as OUTPUT).
    void Initialize() {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        state = 0;
        state_str = String("OFF");
        last_state_change = millis();
    }

    // ### `LED.On()`
    // Turns the LED on.
    void On() {
        digitalWrite(pin, HIGH);
        state = 1;
        state_str = String("ON");
        last_state_change = millis();
    }

    // ### `LED.Off()`
    // Turns the LED off.
    void Off() {
        digitalWrite(pin, LOW);
        state = 0;
        state_str = String("OFF");
        last_state_change = millis();
    }

    // ### `LED.Toggle()`
    // Toggles the LED's state:
    // - Turns it on if currently off
    // - Turns it off if currently on
    void Toggle() {
        if (state == 0) {
            On();
        } else {
            Off();
        }
    }

    // ### `LED.GetState()`
    // Returns the current state (`0` / `1`) of the LED.
    unsigned int GetState() {
        return state;
    }

    // ### `LED.GetStateStr()`
    // Returns the current state (`"OFF"` / `"ON"`) of the LED.
    String GetStateStr() {
        return state_str;
    }
};



#endif // LED_HPP