# The HVEOSLZP Project

| Name | Username | Email |
|------|----------|-------|
| Henryk Viana | VianaH | henryk.viana@unifr.ch |
| Emma Oper | OperE | emma.oper@unifr.ch |
| Sheryl Lin | LinS | sheryl.lin@unibe.ch|
| Zakhar Petrenko | PetrenkoZ | zakhar.petrenko@unifr.ch |


Music-generating Rave Machine: using the M5Stack 6-Axis IMU to create a real-time device that allows users to manipulate music through physical gestures. The device is a wearable bracelet which tracks accelerometer readings along the x- and y-axis, and sends them to a locally-hosted web app. The app plays a lovely arpeggio using the native Web Audio API, which can then be modulated in pitch and rhythm according to the user's movements. Will you be the next Rave Machine virtuoso?

**Links**:
* [6-Axis IMU Unit(MPU6886)](https://shop.m5stack.com/products/6-axis-imu-unitmpu6886)
* [IMU Mini Unit Documentation](https://docs.m5stack.com/en/unit/imu)
* [IMU Mini Unit API](https://docs.m5stack.com/en/uiflow/blockly/unit/imu)


## Instructions for use:
1. PlatformIO setup:
    * Install VSCode
    * Install PlatformIO extension
    * Open this folder as project in PlatformIO
    * Upload *platformio.ini* to initialize libraries
    * Upload your desired program
    * Optional: to run Unity tests, click on the test button on the toolbar at the bottom, or run `pio test -v`
2. Server setup:
    * Check *lib/server/src/server.cpp* and make sure that the server config values look good. Example (default):

    ```python
    const char* ssid = "ESP32-HVEOSLZP";
    const char* password = "12345678";
    const char* serverURL = "http://192.168.4.2:8000";
    ```

    * On your laptop, run *src/http_server.py*. This will start hosting a server at localhost:8000.
    * Upload *src/main.cpp* to the Atom Lite. This will start running:
        * setupWifi() (from *lib/server*) - starts the Atom's SoftAP Wifi hotspot
        * getData() (from *lib/sensor*) - retrieves IMU acceleration and gyroscope values and stores them as a string in JSON format. The raw data will also print to the serial monitor.
        * sendDataToServer() (from *lib/sensor*) - sends an http POST request to send the data to the server you started, which can be accessed at localhost:8000/latest.
    * If the setup worked, in the terminal where you started your server, it should start saying "POST / HTTP/1.1" 200 - Received: ...
3. Webapp setup:
    ```bash
    # go to the directory containing webapp.html
    cd src
    # invoke the standard python web server
    python -m http.server 5500
    # now in your browser (chrome), go to: 
    http://localhost:5500/rave_machine.html
    ```

### Directory structure
```
.
├── README.md
├── lib
│   ├── README
│   ├── sensor
│   │   ├── include
│   │   │   └── sensor.h
│   │   └── src
│   │       └── sensor.cpp
│   └── server
│       ├── include
│       │   └── server.h
│       └── src
│           └── server.cpp
├── platformio.ini
├── src
│   ├── http_server.py
│   ├── main.cpp
│   └── webapp.html
└── test
    ├── README
    └── test_sensor.cpp
```
