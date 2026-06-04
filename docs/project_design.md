# Project design
### Components
- **IMU sensor**: 6-Axis IMU Unit (MPU6886), which reads gyroscope and accelerometer values for x, y, z. Produces raw readings which can be interpreted as directional tilt or acceleration. 
- **Microprocessor**: M5Stack Atom Lite ESP32 device, connected to the IMU via I2C. Hosts a SoftAP wifi hotspot which the user can connect to, for convenient data sharing without using public networks. Sends values to the web server via HTTP POST requests.
- **Web server (backend REST API)**: Locally hosted, standard Python web server which handles HTTP POST and GET requests. Ingests and stores data from the microprocessor and sends it to the web app.
- **Web app (frontend)**: HTML / Javascript web app, which retrieves the data using GET requests from the web server. This is needed in order to utilize the native Web Audio API, for playing audio in the user's browser.
- **Web server (frontend)**: Locally hosted, standard Python web server which is used to serve the user the HTML webapp on a URL, enabling proper HTTP fetch capacities by the webapp. This could be combined into the backend API server, but keeping them separate can be good practice for easier scaling if the project expands to multiple frontend clients.

### Development decisions
We used the PlatformIO development platform (as a VSCode extension) with an Arduino framework for compiling, library management, and firmware flashing. The programs are written in C++, mostly in the style of C with minimal implementation of C++ as needed. Unit testing is done using the built-in PlatformIO Unity tester.

Our web app architecture is a REST API that is hosted on the user's laptop, and manages JSON-formatted HTTP payloads that are sent via the ESP32 SoftAP wifi hotspot. Real-time sensor input is repeatedly sent, dynamically changing the sounds played by the webapp.

Despite REST APIs typically being implemented for non-real-time updates, our system has a latency of ~100-200 ms, which provided a surprisingly responsive user experience. A good future direction of the project would be to update it to a WebSocket API, which is optimized for real-time, bidirectional communication - especially if server load and payload complexity continued to increase (ex. adding multiple sensors for dual-hand control).

#### Data storage
Given the consistency and small size of our data, the project utilizes a static data buffer that is continuously updated. A total of 6 raw values (acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z) are retrieved from the IMU sensor and stored as a char\[120] array. They are then reformatted into JSON format using snprintf(), and sent to the web server in raw bytes (~120 bytes per payload).

#### Testing
There are three tests. test_getData tests whether the ESP32 to IMU connection is successfully returning non-null acceleration values. test_ping sends a ping to the backend, prints the latency in ms, and passes if it is within an acceptable range (<500 ms). test_sendData_GET sends a ping and tests whether the backend is successfully handling HTTP requests by sending a GET request to retrieve the ping data from /latest.