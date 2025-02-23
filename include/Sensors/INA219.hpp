/****************************************************************
*                                                               *
*   INA219.hpp                                                  *
*                                                               *
*   INA219 voltage/current/power-sensor class definition.       *
*                                                               *
*****************************************************************/
#ifndef INA219_HPP
#define INA219_HPP

#include <vector>
#include <functional>
#include <Wire.h>
#include <Arduino.h>
#include "Sensor.hpp"
#include "SensorBuffer.hpp"
#include "Events/Event.hpp"
#include "Adafruit_INA219.h"
#include "Events/EventEmitter.hpp"



// ## INA219
// Class representing an INA219 sensor.
// The `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
// ### Parameters
// - `e` - The global `EventEmitter` object.
// - `sda_pin` - The GPIO pin that the sensor's SDA is connected to.
// - `scl_pin` - The GPIO pin that the sensor's SCL is connected to.
// - `events` (optional) - A list of `EventType`s (the sensor will be registered to receive events of these types).
// - `handler` (optional) - An `onEvent` function that will be called whenever the sensor receives an event it is registered for.
// ### Example Instantiation
// ```
// #define INA219_SDA_PIN 4
// #define INA219_SCL_PIN 5
// EventEmitter event_emitter; 
// INA219 ina219(event_emitter, INA219_SDA_PIN, INA219_SCL_PIN);
// ```
class INA219 : public Sensor {
private:
    // ### `INA219.sda_pin`
    // Private integer defining which GPIO pin the sensor's SDA is connected to.
    const int sda_pin;

    // ### `INA219.scl_pin`
    // Private integer defining which GPIO pin the sensor's SCL is connected to.
    const int scl_pin;

    // ### `INA219.ada_obj`
    // Private `Adafruit_INA219` object that this class wraps.
    Adafruit_INA219 ada_obj;

    // ### `INA219.reference_temperature`
    // Private float defining the reference room temperature (in `°C`) of the coil the INA219 is in series with.
    // Used in inferring the temperature of the coil.
    const float reference_temperature = 20.f;

    // ### `INA219.reference_resistance`
    // Private float defining the room-temperature resistance (in `Ω`) of the coil the INA219 is in series with.
    // Used in inferring the temperature of the coil.
    const float reference_resistance = 4.f;

    // ### `INA219.temperature_coefficient`
    // Private float defining the Temperature Coefficient of copper (in `1/°C`) of the coil the INA219 is in series with.
    // Used in inferring the temperature of the coil.
    const float temperature_coefficient = 0.00393f;

public:
    Adafruit_INA219 GetAdaObj() {
        return ada_obj;
    }

    struct Measurements {
        // ### `Measurements.power`
        // List of past power readings by the INA219.
        SensorBuffer power;
        // ### `Measurements.voltage`
        // List of past voltage readings by the INA219.
        SensorBuffer voltage;
        // ### `Measurements.current`
        // List of past current readings by the INA219.
        SensorBuffer current;
        // ### `Measurements.resistance`
        // List of past resistance calculations.
        SensorBuffer resistance;
        // ### `Measurements.temperature`
        // List of past inferred temperatures, in `°F`.
        SensorBuffer temperature;
    };
    // ### `INA219.measurements`
    // Stores previous measurements read by the INA219.
    Measurements measurements;

    // ### `INA219.reading_began`
    // Timestamp of when the sensor began reading data.
    unsigned long reading_began;

    // ## INA219
    // Class representing an INA219 sensor.
    // The `events` and `handler` parameters are optional, and if not given, can be set later with the `RegisterForEvents` and `SetOnEvent` functions, respectively.
    // ### Parameters
    // - `e` - The global `EventEmitter` object.
    // - `sda_pin` - The GPIO pin that the sensor's SDA is connected to.
    // - `scl_pin` - The GPIO pin that the sensor's SCL is connected to.
    // - `events` (optional) - A list of `EventType`s (the sensor will be registered to receive events of these types).
    // - `handler` (optional) - An `onEvent` function that will be called whenever the sensor receives an event it is registered for.
    // ### Example Instantiation
    // ```
    // #define INA219_SDA_PIN 4
    // #define INA219_SCL_PIN 5
    // EventEmitter event_emitter; 
    // INA219 ina219(event_emitter, INA219_SDA_PIN, INA219_SCL_PIN);
    // ```
    INA219(
        EventEmitter& e,
        int sda_pin,
        int scl_pin,
        const std::vector<EventType>& events = {},
        std::function<void(const Event&)> handler = nullptr
    ) : Sensor(e, events, handler), sda_pin(sda_pin), scl_pin(scl_pin) {
            /* Define what should happen when the Sensor object is initialized */
            /* Could also define the OnEvent method below and assign it here with SetOnEvent(OnEvent) */
    }

    // ### `INA219.Initialize()`
    // Initializes the INA219 to prepare for reading values.
    // ```
    // if (!ina219.Initialize()) {
    //     Serial.println("Failed to find/initialize INA219.");
    //     while (1) { delay(10); }
    // }
    // ```
    bool Initialize() {
        return ada_obj.begin();
    }

    // ### `INA219.GetPower()`
    // Reads the power consumption, in `Watts`, of the load the INA219 is in series with.
    float GetPower() {
        float power = ada_obj.getPower_mW() / 1000.f;
        measurements.power.Add(power);
        return power;
    }

    // ### `INA219.GetCurrent()`
    // Reads the current, in `Amperes`, traveling through the INA219 and the load it is in series with.
    float GetCurrent() {
        float current = ada_obj.getCurrent_mA() / 1000.f;
        measurements.current.Add(current);
        return current;
    }

    // ### `INA219.GetVoltage()`
    // Reads the voltage, in `Volts`, across the load the INA219 is in series with.
    float GetVoltage() {
        float voltage = ada_obj.getBusVoltage_V() + (ada_obj.getShuntVoltage_mV() / 1000.f);
        measurements.voltage.Add(voltage);
        return voltage;
    }

    // ### `INA219.GetResistance()`
    // Calculates the resistance, in `Ohms`, of the load the INA219 is in series with.
    float GetResistance() {
        float power = GetPower();
        float voltage = GetVoltage();
        float resistance = voltage * voltage / power;
        measurements.resistance.Add(resistance);
        return resistance;
    }

    // ### `INA219.GetAveragePower()`
    // Returns the average of all power measurements, in `W`, made since the buffer was last cleared.
    float GetAveragePower() {
        return measurements.power.GetAverage();
    }

    // ### `INA219.GetAverageCurrent()`
    // Returns the average of all current measurements, in `A`, made since the buffer was last cleared.
    float GetAverageCurrent() {
        return measurements.current.GetAverage();
    }

    // ### `INA219.GetAverageVoltage()`
    // Returns the average of all voltage measurements, in `V`, made since the buffer was last cleared.
    float GetAverageVoltage() {
        return measurements.voltage.GetAverage();
    }

    // ### `INA219.GetAverageResistance()`
    // Returns the average of all resistance measurements, in `Ω`, made since the buffer was last cleared.
    float GetAverageResistance() {
        return measurements.resistance.GetAverage();
    }

    // ### `INA219.GetInferredTemperature()`
    // Returns the inferred coil temperature based on calculations of resistance.
    float GetInferredTemperature() {
        float resistance = GetResistance();
        float temperature_C = reference_temperature + ((1/temperature_coefficient) * (resistance/reference_resistance - 1));
        float temperature_F = (temperature_C * 9/5) + 32;
        measurements.temperature.Add(temperature_F);
        return temperature_F;
    }

    // ### `INA219.GetAverageInferredTemperature()`
    // Returns the average of all inferred temperatures, in `°F`, done since the buffer was last cleared.
    float GetAverageInferredTemperature() {
        return measurements.temperature.GetAverage();
    }

    // ### `INA219.Read()`
    // Defines how and what it means to read this sensor, and under what condition it should emit an event.
    // This is the function bound to a `Ticker` object and is called continously at the interval specified in `Begin()`.
    void Read() override {
        GetPower();
        GetCurrent();
        GetVoltage();
        GetResistance();
        GetInferredTemperature();
    }
};



#endif // INA219_HPP