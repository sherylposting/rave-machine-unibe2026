# Project design
### Components
- **IMU sensor**: 6-Axis IMU Unit (MPU6886), which reads gyroscope and accelerometer values for x, y, z. Produces raw readings which can be interpreted as directional tilt or acceleration. 
- **Microprocessor**: M5Stack Atom Lite ESP32 device, connected to the IMU via I2C. Hosts a SoftAP wifi hotspot which the user can connect to, for convenient data sharing without using public networks. Sends values to the web server via http POST requests.
- **Web server (backend)**: Locally hosted, standard library Python web server which handles http POST and GET requests. Ingests and stores data from the microprocessor and sends it to the web app.
- **Web app (frontend)**: Javascript web app, which retrieves the data using GET requests from the web server. This is needed in order to utilize the native Web Audio API, for playing audio in the user's browser.

### Development decisions
We used the PlatformIO development platform (as a VSCode extension) with an Arduino framework for compiling, library management, and firmware flashing. The programs are written in C++, mostly in the style of C with minimal implementation of C++ as needed. Unit testing is done using the built-in PlatformIO Unity tester.
#### Data storage
A total of 6 raw values (acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z) are retrieved from the IMU sensor and stored as a char array. They are then reformatted into JSON format using snprintf(), and sent to the web server.