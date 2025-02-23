/****************************************************************
*                                                               *
*   WebServer.h                                                 *
*                                                               *
*   Asynchronous WiFi webserver hosted by the NodeMCU.          *
*                                                               *
*****************************************************************/
#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Ticker.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Arduino_JSON.h>
#include <ESPAsyncWebServer.h>
#include "Data.hpp"



// ## WebServer
// WebServer class used for hosting a dashboard on a network created at runtime.
// ### Parameters
// - `port` - The port number to run the network through.
// - `ssid` - The name to assign the network when created.
// - `password` - The password to assign the network when created. Must be >= 8 characters in length.
// 
// Example instantiation and starting:
// ```c++
// WebServer Server(80, "esp8266", "12345678");
// Server.Start();  // Now discoverable by devices as `esp8266`
// ```
class WebServer {
private:
    // ### `WebServer.port`
    // The port number that the network is running through.
    const int port;

    // ### `WebServer.ssid`
    // The name given to the network when created.
    const char* ssid;

    // ### `WebServer.password`
    // The password given to the network when created.
    const char* password;

    // ### `WebServer.server`
    // The behind-the-scenes `AsyncWebServer` object that the `WebServer` class is a wrapper for.
    AsyncWebServer server;

    // ### `WebServer.events`
    // An `AsyncEventSource` object used to handle the sending of new data to the dashboard (server-side-events).
    AsyncEventSource events;

    // ### `WebServer.timer`
    // Protected `Ticker` object that the webserver can bind its `UpdateData` method to, to enable continous/scheduled updating.
    Ticker timer;

    // ### `WebServer.OnRoot()`
    // Private function defining what happens when a client visits the root ("/") of the dashboard.
    // This isn't ever called manually (called in `WebServer.Start()`), and simply serves the `index_html` page defined in `IndexHTML.hpp`.
    // ### Parameters
    // - `request` - A pointer to an `AsyncWebServerRequest` object.
    void OnRoot(AsyncWebServerRequest* request);

    // ### `WebServer.ToJSON()`
    // Private function that converts the contents of a `Data` object to a JSON variable.
    // ### Parameters
    // - `data` - A pointer to a `Data` object containing the data to convert.
    JSONVar ToJSON(const Data* data);

    // ### `WebServer.UpdateWithStoredData()`
    // Private function that updates the contents of the webserver using data stored in `WebServer.incoming_data`.
    void UpdateWithStoredData();

public:
    // ## WebServer
    // WebServer class used for hosting a dashboard on a network created at runtime.
    // ### Parameters
    // - `port` - The port number to run the network through.
    // - `ssid` - The name to assign the network when created.
    // - `password` - The password to assign the network when created. Must be >= 8 characters in length.
    // 
    // Example instantiation and starting:
    // ```c++
    // WebServer Server(80, "esp8266", "12345678");
    // Server.Start();  // Now discoverable by devices as `esp8266`
    // ```
    WebServer(
        int port,
        const char* ssid,
        const char* password
    );

    // ### `WebServer.started`
    // Boolean indicating if the webserver has successfully started.
    bool started;

    // ### `WebServer.mac_address`
    // The MAC address of the NodeMCU ESP8266.
    String mac_address;

    // ### `WebServer.ip_address`
    // The IP address of the NodeMCU ESP8266 on the network it creates.
    IPAddress ip_address;

    // ### `WebServer.incoming_data`
    // Data that comes from a type of `Controller` object.
    // This variable always stores the data that was most recently sent to the dashboard.
    Data incoming_data;

    // ### `Webserver.Start()`
    // Public function that sets up the webserver and gets it ready for receiving new data.
    // This function needs to be called in `void setup()` prior to the main loop code beginning.
    void Start();

    // ### `WebServer.UpdateData()`
    // Public function updates the dashboard with new data.
    // This function should be called by a type of `Controller` whose sole purpose is to create `data_struct` objects after events for updating the dashboard.
    // ### Parameters
    // - `incoming_data` - A reference to a `data_struct` object, containing the payload used to update the dashboard.
    void UpdateData(const Data* incoming_data);

    // ### `WebServer.ScheduleUpdates()`
    // Starts scheduled updates of the webserver's content using data currently stored in `WebServer.incoming_data`.
    // ### Parameters
    // - `update_interval` - How long to wait between each update, in milliseconds.
    void ScheduleUpdates(float update_interval);

    // ### `WebServer.StopUpdates()`
    // Stops scheduled updates of the webserver's content.
    void StopUpdates();
};



#endif // WEB_SERVER_H