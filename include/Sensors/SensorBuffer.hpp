/****************************************************************
*                                                               *
*   SensorBuffer.hpp                                            *
*                                                               *
*   A vector-like buffer for storing sensor readings/values.    *
*                                                               *
*****************************************************************/
#ifndef SENSOR_BUFFER_HPP
#define SENSOR_BUFFER_HPP

#include <deque>
#include <numeric>



// ## `SensorBuffer`
// A vector-like buffer for storing sensor readings/values.
// ### Parameters
// - `MAX_SIZE` - The maximum number of values to hold before overwriting begins (optional, default = `20`).
class SensorBuffer {
private:
    std::deque<float> buffer;       // Acts like a limited-size queue.
    const size_t MAX_SIZE;          // Maximum number of values to hold.

public:
    // ## `SensorBuffer`
    // A vector-like buffer for storing sensor readings/values.
    // ### Parameters
    // - `MAX_SIZE` - The maximum number of values to hold before overwriting begins (optional, default = `20`).
    SensorBuffer(size_t MAX_SIZE = 20) : MAX_SIZE(MAX_SIZE) { }

    // ### `SensorBuffer.count`
    // The number of values currently stored in the buffer.
    unsigned int count;

    // ### `SensorBuffer.Add()`
    // Adds a new sensor reading to the buffer.
    void Add(float measurement) {
        if (buffer.size() == MAX_SIZE) {
            buffer.pop_front();     // Remove oldest element
        }
        buffer.push_back(measurement);
        count = buffer.size();
    }

    // ### `SensorBuffer.Clear()`
    // Clears all values from the buffer (its size will be equal to zero afterwards).
    void Clear() {
        buffer.clear();
        count = 0;
    }

    // ### `SensorBuffer.GetLast()`
    // Gets the most recently added value from the buffer.
    float GetLast() const {
        if (buffer.empty()) {
            return 0.f;
        }
        return buffer.back();
    }

    // ### `SensorBuffer.GetAverage()`
    // Computes the average of all values in the buffer.
    float GetAverage() const {
        if (buffer.empty()) {
            return 0.f;
        }
        double sum = std::accumulate(buffer.begin(), buffer.end(), 0.0);
        double avg = sum / buffer.size();
        return (float)avg;
    }
};



#endif // SENSOR_BUFFER_HPP