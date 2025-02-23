/****************************************************************
*                                                               *
*   Data.hpp                                                    *
*                                                               *
*   Struct defining data to be served by the webserver.         *
*                                                               *
*****************************************************************/
#ifndef DATA_HPP
#define DATA_HPP

#include <Arduino.h>
#include <Arduino_JSON.h>



// ## Data
// Struct defining data to be served by the webserver.
// ### Defined properties:
// - `speed` (`float`) - The speed of the motor, in `RPM`.
// - `torque` (`float`) - The torque of the motor, in `N·m`.
// - `voltage` (`float`) - The voltage read by the INA219, in `V`.
// - `current` (`float`) - The current read by the INA219, in `A`.
// - `powerin` (`float`) - The electrical power input to the motor, in `W`.
// - `powerout` (`float`) - The estimated mechanical power output from the motor, in `W`.
// - `efficiency` (`float`) - The efficiency of the motor, `powerin`/`powerout`, in `%`.
// - `temperature` (`float`) - The estimated coil temperature from the INA219, in `°F`.
// - `elapsed` (`float`) - The total time elapsed since the NodeMCU first booted up, in `s`.
typedef struct Data {
    // ## Data
    // Struct defining data to be served by the webserver.
    Data() { }

    // ## Data
    // Struct defining data to be served by the webserver.
    // ### Parameters
    // - `speed` - The speed of the motor, in `RPM`.
    // - `torque` - The torque of the motor, in `N·m`.
    // - `voltage` - The voltage read by the INA219, in `V`.
    // - `current` - The current read by the INA219, in `A`.
    // - `powerin` - The electrical power input to the motor, in `W`.
    // - `powerout` - The estimated mechanical power output from the motor, in `W`.
    // - `efficiency` - The efficiency of the motor, `powerin`/`powerout`, in `%`.
    // - `temperature` - The estimated coil temperature from the INA219, in `°F`.
    // - `elapsed` - The total time elapsed since the NodeMCU first booted up, in `s`.
    Data(
        float speed,
        float torque,
        float voltage,
        float current,
        float powerin,
        float powerout,
        float efficiency,
        float temperature,
        float elapsed
    ) : speed(speed), 
        torque(torque),
        voltage(voltage),
        current(current),
        powerin(powerin),
        powerout(powerout),
        efficiency(efficiency),
        temperature(temperature),
        elapsed(elapsed) { }

    // ### `Data.speed`
    // The speed of the motor, in `RPM`.
    float speed;

    // ### `Data.torque`
    // The torque of the motor, in `N·m`.
    float torque;

    // ### `Data.voltage`
    // The voltage read by the INA219, in `V`.
    float voltage;

    // ### `Data.current`
    // The current read by the INA219, in `A`.
    float current;

    // ### `Data.powerin`
    // The electrical power input to the motor, in `W`.
    float powerin;

    // ### `Data.powerout`
    // The estimated mechanical power output from the motor, in `W`.
    float powerout;

    // ### `Data.efficiency`
    // The efficiency of the motor, `powerin`/`powerout`, in `%`.
    float efficiency;

    // ### `Data.temperature`
    // The estimated coil temperature from the INA219, in `°F`.
    float temperature;

    // ### `Data.elapsed`
    // The total time elapsed since the NodeMCU first booted up, in `s`.
    float elapsed;
}   Data;




// class Data {
// private:

// public:
//     // ## Data
//     // Class defining data to be served by the webserver.
//     Data() { }

//     // ## Data
//     // Class defining data to be served by the webserver.
//     // ### Parameters
//     // - `speed` - The speed of the motor, in `RPM`.
//     // - `torque` - The torque of the motor, in `N·m`.
//     // - `voltage` - The voltage read by the INA219, in `V`.
//     // - `current` - The current read by the INA219, in `A`.
//     // - `powerin` - The electrical power input to the motor, in `W`.
//     // - `powerout` - The estimated mechanical power output from the motor, in `W`.
//     // - `efficiency` - The efficiency of the motor, `powerin`/`powerout`, in `%`.
//     // - `temperature` - The estimated coil temperature from the INA219, in `°F`.
//     // - `elapsed` - The total time elapsed since the NodeMCU first booted up, in `s`.
//     Data(
//         float speed,
//         float torque,
//         float voltage,
//         float current,
//         float powerin,
//         float powerout,
//         float efficiency,
//         float temperature,
//         float elapsed
//     ) {
//         this->speed = speed;
//         this->torque = torque;
//         this->voltage = voltage;
//         this->current = current;
//         this->powerin = powerin;
//         this->powerout = powerout;
//         this->efficiency = efficiency;
//         this->temperature = temperature;
//         this->elapsed = elapsed;
//     }

//     // ### `Data.speed`
//     // The speed of the motor, in `RPM`.
//     float speed;

//     // ### `Data.torque`
//     // The torque of the motor, in `N·m`.
//     float torque;

//     // ### `Data.voltage`
//     // The voltage read by the INA219, in `V`.
//     float voltage;

//     // ### `Data.current`
//     // The current read by the INA219, in `A`.
//     float current;

//     // ### `Data.powerin`
//     // The electrical power input to the motor, in `W`.
//     float powerin;

//     // ### `Data.powerout`
//     // The estimated mechanical power output from the motor, in `W`.
//     float powerout;

//     // ### `Data.efficiency`
//     // The efficiency of the motor, `powerin`/`powerout`, in `%`.
//     float efficiency;

//     // ### `Data.temperature`
//     // The estimated coil temperature from the INA219, in `°F`.
//     float temperature;

//     // ### `Data.elapsed`
//     // The total time elapsed since the NodeMCU first booted up, in `s`.
//     float elapsed;
// };



// // ## Data
// // Class defining data to be served by the webserver.
// // ### Defined properties:
// // - `speed` (`float`) - The speed of the motor, in `RPM`.
// // - `torque` (`float`) - The torque of the motor, in `N·m`.
// // - `voltage` (`float`) - The voltage read by the INA219, in `V`.
// // - `current` (`float`) - The current read by the INA219, in `A`.
// // - `powerin` (`float`) - The electrical power input to the motor, in `W`.
// // - `powerout` (`float`) - The estimated mechanical power output from the motor, in `W`.
// // - `efficiency` (`float`) - The efficiency of the motor, `powerin`/`powerout`, in `%`.
// // - `temperature` (`float`) - The estimated coil temperature from the INA219, in `°F`.
// // - `elapsed` (`float`) - The total time elapsed since the NodeMCU first booted up, in `s`.
// class Data {
// private:

// public:
//     // ## Data
//     // Class defining data to be served by the webserver.
//     Data() { }

//     // ## Data
//     // Class defining data to be served by the webserver.
//     // ### Parameters
//     // - `speed` - The speed of the motor, in `RPM`.
//     // - `torque` - The torque of the motor, in `N·m`.
//     // - `voltage` - The voltage read by the INA219, in `V`.
//     // - `current` - The current read by the INA219, in `A`.
//     // - `powerin` - The electrical power input to the motor, in `W`.
//     // - `powerout` - The estimated mechanical power output from the motor, in `W`.
//     // - `efficiency` - The efficiency of the motor, `powerin`/`powerout`, in `%`.
//     // - `temperature` - The estimated coil temperature from the INA219, in `°F`.
//     // - `elapsed` - The total time elapsed since the NodeMCU first booted up, in `s`.
//     Data(
//         float speed,
//         float torque,
//         float voltage,
//         float current,
//         float powerin,
//         float powerout,
//         float efficiency,
//         float temperature,
//         float elapsed
//     ) {
//         this->speed = speed;
//         this->torque = torque;
//         this->voltage = voltage;
//         this->current = current;
//         this->powerin = powerin;
//         this->powerout = powerout;
//         this->efficiency = efficiency;
//         this->temperature = temperature;
//         this->elapsed = elapsed;
//     }

//     // ### `Data.speed`
//     // The speed of the motor, in `RPM`.
//     float speed;

//     // ### `Data.torque`
//     // The torque of the motor, in `N·m`.
//     float torque;

//     // ### `Data.voltage`
//     // The voltage read by the INA219, in `V`.
//     float voltage;

//     // ### `Data.current`
//     // The current read by the INA219, in `A`.
//     float current;

//     // ### `Data.powerin`
//     // The electrical power input to the motor, in `W`.
//     float powerin;

//     // ### `Data.powerout`
//     // The estimated mechanical power output from the motor, in `W`.
//     float powerout;

//     // ### `Data.efficiency`
//     // The efficiency of the motor, `powerin`/`powerout`, in `%`.
//     float efficiency;

//     // ### `Data.temperature`
//     // The estimated coil temperature from the INA219, in `°F`.
//     float temperature;

//     // ### `Data.elapsed`
//     // The total time elapsed since the NodeMCU first booted up, in `s`.
//     float elapsed;
// };



#endif // DATA_HPP