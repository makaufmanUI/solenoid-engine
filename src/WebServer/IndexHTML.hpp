/****************************************************************
*                                                               *
*   IndexHTML.hpp                                               *
*                                                               *
*   HTML code defining the webserver's contents.                *
*                                                               *
*****************************************************************/
#ifndef INDEX_HTML_HPP
#define INDEX_HTML_HPP

#include <Arduino_JSON.h>



const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
    <title>MOTOR DASHBOARD</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Noto+Sans:ital,wght@0,100..900;1,100..900&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    <link rel="icon" href="data:,">
    <style>
        html {
            font-family: Arial;
            display: inline-block;
            text-align: center;
        }
        p {
            /* font-size: 1.2rem; */
            font-size: 1.1rem;
            font-family: 'Noto Sans', sans-serif;
        }
        body {
            margin: 0;
        }
        h4 {
            font-family: 'Noto Sans', sans-serif;
            font-size: 1.1rem;
        }
        .topnav {
            overflow: hidden;
            background-color: #2f4468;
            color: white;
            font-size: 1.7rem;
        }
        .content {
            padding: 20px;
        }
        .card {
            background-color: white;
            box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
        }
        .cards {
            max-width: 700px;
            margin: 0 auto;
            display: grid;
            grid-gap: 2rem;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
        }
        .reading {
            font-size: 2.4rem;
        }
        .elapsedtime {
            font-size: 1.5rem;
        }
        .packet {
            color: #bebebe;
            font-size: 0.3rem;
        }
        .card.rpm {
            color: #3ba10c;
        }
        .card.torque {
            color: #3ba10c;
        }
        .card.temperature {
            color: #fd5614;
        }
        .card.voltage {
            color: #fd7e14;
        }
        .card.current {
            color: #fd7e14;
        }
        .card.powerin {
            color: #1b78e2;
        }
        .card.powerout {
            color: #1b78e2;
        }
        .card.efficiency {
            color: #fd5614;
        }
    </style>
</head>
<body>
    <div class="topnav">
        <h3>MOTOR DASHBOARD</h3>
    </div>
    <div class="content">
        <div class="cards">
            <div class="card rpm">
                <h4><i class="fas fa-cog"></i> &nbsp;SPEED</h4>
                <p><span class="reading"><span id="speed"></span> rpm</span></p>
                <p class="packet"> &nbsp; <span id="rt1"></span></p>
            </div>
            <div class="card torque">
                <h4><i class="fas fa-cog"></i> &nbsp;TORQUE</h4>
                <p><span class="reading"><span id="torque"></span> N&middot;m</span></p>
                <p class="packet"> &nbsp; <span id="rt1"></span></p>
            </div>
            <div class="card voltage">
                <h4><i class="fas fa-bolt"></i> &nbsp;VOLTAGE</h4>
                <p><span class="reading"><span id="voltage"></span> V</span></p>
                <p class="packet"> &nbsp; <span id="rt1"></span></p>
            </div>
            <div class="card current">
                <h4><i class="fas fa-bolt"></i> &nbsp;CURRENT</h4>
                <p><span class="reading"><span id="current"></span> A</span></p>
                <p class="packet"> &nbsp; <span id="rt1"></span></p>
            </div>
            <div class="card powerin">
                <h4><i class="fas fa-arrow-right"></i> &nbsp;POWER IN</h4>
                <p><span class="reading"><span id="powerin"></span> W</span></p>
                <p class="packet"> &nbsp; <span id="rt1"></span></p>
            </div>
            <div class="card powerout">
                <h4><i class="fas fa-arrow-left"></i> &nbsp;POWER OUT</h4>
                <p><span class="reading"><span id="powerout"></span> W</span></p>
                <p class="packet"> &nbsp; <span id="rt1"></span></p>
            </div>
            <div class="card efficiency">
                <h4><i class="fas fa-sort"></i> &nbsp;EFFICIENCY</h4>
                <p><span class="reading"><span id="efficiency"></span> &percnt;</span></p>
                <p class="packet"> &nbsp; <span id="rt1"></span></p>
            </div>
            <div class="card temperature">
                <h4><i class="fas fa-thermometer-half"></i> &nbsp;TEMPERATURE</h4>
                <p><span class="reading"><span id="temperature"></span> &deg;F</span></p>
                <p class="packet"> &nbsp; <span id="rt1"></span></p>
            </div>
        </div>
        <div class="count">
            <h4> &nbsp; </h4>
            <h4><i class="fas fa-clock"></i> Elapsed</h4>
            <p><span class="elapsedtime"><span id="elapsed"></span> s</span></p>
        </div>
    </div>
    <script>
    if (!!window.EventSource) {
        var source = new EventSource('/events');

        source.addEventListener('open', function(e) {
            console.log("Events Connected");
        }, false);
        source.addEventListener('error', function(e) {
            if (e.target.readyState != EventSource.OPEN) {
                console.log("Events Disconnected");
            }
        }, false);

        source.addEventListener('message', function(e) {
            console.log("message", e.data);
        }, false);

        source.addEventListener('new_data', function(e) {
            console.log("new_data", e.data);
            var obj = JSON.parse(e.data);
            document.getElementById("speed").innerHTML = obj.speed.toFixed(0);
            document.getElementById("torque").innerHTML = obj.torque.toFixed(2);
            document.getElementById("voltage").innerHTML = obj.voltage.toFixed(2);
            document.getElementById("current").innerHTML = obj.current.toFixed(2);
            document.getElementById("powerin").innerHTML = obj.powerin.toFixed(2);
            document.getElementById("powerout").innerHTML = obj.powerout.toFixed(2);
            document.getElementById("efficiency").innerHTML = obj.efficiency.toFixed(2);
            document.getElementById("temperature").innerHTML = obj.temperature.toFixed(2);
            document.getElementById("elapsed").innerHTML = obj.elapsed.toFixed(1);
        }, false);
    }
    </script>
</body>
</html>)rawliteral";






// const char index_html[] PROGMEM = R"rawliteral(
// <!DOCTYPE HTML><html>
// <head>
//     <title>COIL MOTOR DASHBOARD</title>
//     <meta name="viewport" content="width=device-width, initial-scale=1">
//     <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
//     <link rel="icon" href="data:,">
//     <style>
//         html {
//             font-family: Arial;
//             display: inline-block;
//             text-align: center;
//         }
//         p {
//             font-size: 1.2rem;
//         }
//         body {
//             margin: 0;
//         }
//         .topnav {
//             overflow: hidden;
//             background-color: #2f4468;
//             color: white;
//             font-size: 1.7rem;
//         }
//         .content {
//             padding: 20px;
//         }
//         .card {
//             background-color: white;
//             box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
//         }
//         .cards {
//             max-width: 700px;
//             margin: 0 auto;
//             display: grid;
//             grid-gap: 2rem;
//             grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
//         }
//         .reading {
//             font-size: 2.8rem;
//         }
//         .packet {
//             color: #bebebe;
//         }
//         .card.temperature {
//             color: #fd7e14;
//         }
//         .card.humidity {
//             color: #1b78e2;
//         }
//     </style>
// </head>
// <body>
//     <div class="topnav">
//         <h3>COIL MOTOR DASHBOARD</h3>
//     </div>
//     <div class="content">
//         <div class="cards">
//             <div class="card temperature">
//                 <h4><i class="fas fa-thermometer-half"></i> BOARD #1 - TEMPERATURE</h4>
//                 <p><span class="reading"><span id="t1"></span> &deg;C</span></p>
//                 <p class="packet">Reading ID: <span id="rt1"></span></p>
//             </div>
//             <div class="card humidity">
//                 <h4><i class="fas fa-tint"></i> BOARD #1 - HUMIDITY</h4>
//                 <p><span class="reading"><span id="h1"></span> &percnt;</span></p>
//                 <p class="packet">Reading ID: <span id="rh1"></span></p>
//             </div>
//             <div class="card temperature">
//                 <h4><i class="fas fa-thermometer-half"></i> BOARD #2 - TEMPERATURE</h4>
//                 <p><span class="reading"><span id="t2"></span> &deg;C</span></p>
//                 <p class="packet">Reading ID: <span id="rt2"></span></p>
//             </div>
//             <div class="card humidity">
//                 <h4><i class="fas fa-tint"></i> BOARD #2 - HUMIDITY</h4>
//                 <p><span class="reading"><span id="h2"></span> &percnt;</span></p>
//                 <p class="packet">Reading ID: <span id="rh2"></span></p>
//             </div>
//         </div>
//     </div>
//     <script>
//     if (!!window.EventSource) {
//         var source = new EventSource('/events');

//         source.addEventListener('open', function(e) {
//             console.log("Events Connected");
//         }, false);
//         source.addEventListener('error', function(e) {
//             if (e.target.readyState != EventSource.OPEN) {
//                 console.log("Events Disconnected");
//             }
//         }, false);

//         source.addEventListener('message', function(e) {
//             console.log("message", e.data);
//         }, false);

//         source.addEventListener('new_data', function(e) {
//             console.log("new_data", e.data);
//             var obj = JSON.parse(e.data);
//             document.getElementById("t"+obj.id).innerHTML = obj.temperature.toFixed(2);
//             document.getElementById("h"+obj.id).innerHTML = obj.humidity.toFixed(2);
//             document.getElementById("rt"+obj.id).innerHTML = obj.readingId;
//             document.getElementById("rh"+obj.id).innerHTML = obj.readingId;
//         }, false);
//     }
//     </script>
// </body>
// </html>)rawliteral";



#endif // INDEX_HTML_HPP