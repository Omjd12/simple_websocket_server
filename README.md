# Simple WebSocket Server on ESP32

A minimal implementation of browser-to-microcontroller communication using WebSockets, an ESP32, and the Arduino framework.

The ESP32 connects to a Wi-Fi network, starts a WebSocket server on port `80`, and advertises the mDNS hostname `robot.local`. A browser-based client connects to the server, sends a message, and receives a response from the ESP32.

## Features

- ESP32 Wi-Fi connectivity
- WebSocket server using the `ArduinoWebsockets` library
- Local hostname discovery using mDNS
- Browser-based WebSocket client
- Two-way text messaging between browser and ESP32

## Repository Structure

```text
simple_websocket_server/
├── simple_websocket_server.ino
├── simple_websocket.html
└── README.md
```

## Requirements

### Hardware
- ESP32 development board
- Computer or smartphone with a modern web browser
- Wi-Fi network accessible to both devices

### Software
- Arduino IDE
- ESP32 board support for Arduino
- `ArduinoWebsockets` library
- A modern web browser

The `WiFi.h` and `ESPmDNS.h` headers are provided by the ESP32 Arduino core.

## Getting Started

### 1. Configure Wi-Fi

Open `simple_websocket_server.ino` and configure your Wi-Fi credentials.

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

**Security note:** Keep real Wi-Fi credentials out of public repositories.

### 2. Upload the ESP32 Firmware

Open `simple_websocket_server.ino` in Arduino IDE, select your ESP32 board and serial port, and upload the sketch.

Open Serial Monitor at **115200 baud**.

After connecting to Wi-Fi, the ESP32 attempts to initialize mDNS with the hostname `robot` and prints its local IP address. The WebSocket server then listens on port `80`.

### 3. Connect the Browser Client

Open `simple_websocket.html` in a browser on a device connected to the same network.

The page connects to the ESP32 using:

```javascript
const socket = new WebSocket("ws://robot.local");
```

If `robot.local` does not resolve on your network, use the IP address printed in Serial Monitor:

```javascript
const socket = new WebSocket("ws://192.168.1.100");
```

Replace the example IP address with the actual address of your ESP32.

### 4. View the Communication

Open the browser's developer tools and select the **Console** tab to view the connection status and messages exchanged with the ESP32.

## Expected Output

Browser console:

```text
connected
esp32: hello from ESP32
```

The ESP32 sends the message `hello from ESP32` after the browser establishes a connection. It also logs the message received from the client.

## How It Works

1. **Wi-Fi initialization:** The ESP32 connects to the configured wireless network using `WiFi.begin()`.
2. **mDNS initialization:** `MDNS.begin("robot")` attempts to make the ESP32 reachable using `robot.local` on clients that support mDNS.
3. **Server initialization:** `server.listen(80)` starts the WebSocket server on port `80`.
4. **Client connection:** JavaScript uses the browser's built-in `WebSocket` API to establish a connection.
5. **Message transmission:** The browser sends `hello esp32` to the ESP32.
6. **Message reception:** The ESP32 polls the connection and logs incoming client messages.
7. **Response:** The ESP32 sends `hello from ESP32` back to the browser, where the `onmessage` handler displays it in the console.

## Communication Architecture

```text
       Wi-Fi Network
             |
     +-------+--------+
     |                |
   ESP32            Browser
 WebSocket          WebSocket
   Server             Client
 Port 80                |
     |                  |
     +--- Text Messages-+
```

## Potential Applications

This implementation provides a foundation for:

- Browser-based robot control interfaces
- Real-time sensor telemetry dashboards
- Wireless communication between a computer and an embedded system
- Live monitoring of robot state and orientation
- Sending commands to ESP32-based robotics projects

## Limitations

- The implementation exchanges fixed text messages rather than actual sensor readings.
- It is a minimal single-client example, not a multi-client server architecture.
- The connection uses unencrypted `ws://`, which is suitable only for appropriate local-network testing.
- The `robot.local` hostname depends on mDNS support; the ESP32's IP address can be used as a fallback.
- The current implementation does not provide authentication, automatic reconnection, or a structured command protocol.

## Future Improvements

- Stream real-time sensor data, such as IMU measurements or robot state.
- Add a browser UI for monitoring and control.
- Support structured messages using JSON.
- Add connection recovery and explicit client-disconnection handling.
- Implement command validation and authentication.
- Separate Wi-Fi configuration from the main firmware.
- Add secure transport where required by the deployment environment.

## License

No license has been specified for this repository.
