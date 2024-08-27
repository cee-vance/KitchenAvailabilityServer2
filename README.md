# ESP32 Kitchen Activity Monitor

This project uses an ESP32 microcontroller and a PIR motion sensor to monitor kitchen activity. The ESP32 hosts a webserver that displays the current status of the kitchen, helping to determine when the kitchen is available.

## Features

- **Motion Detection**: Uses a PIR motion sensor to detect activity in the kitchen.
- **Web Interface**: Hosts a webserver on the ESP32 to display the kitchen status.
- **Real-time Updates**: Provides real-time updates on kitchen availability.
- **Low Power Consumption**: Efficiently monitors activity with minimal power usage.
  
![BreadboardSetup](https://github.com/user-attachments/assets/e859d1fb-047e-4650-be4f-ff6861486913)

## Components

- ESP32 Development Board
- PIR Motion Sensor (e.g., HC-SR501)
- Breadboard and Jumper Wires
- USB Cable for Programming
- Optional: LED and Resistor for Visual Indicator

## Setup

1. **Hardware Connections**:
    - Connect the PIR motion sensor to the ESP32:
        - VCC to 3.3V
        - GND to GND
        - OUT to GPIO 26 (or any other available GPIO pin)
    - (Optional) Connect an LED to another GPIO pin for visual indication.

2. **Software**:
    - Install the Arduino IDE.
    - Install the ESP32 board in the Arduino IDE. Follow the instructions here.
    - Download the required libraries:
        - `WiFi.h`
        - `WebServer.h`



3. **Usage**:
    - Power the ESP32 and connect to the same WiFi network.
    - Open a web browser and enter the ESP32's IP address to view the kitchen status.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

- Inspired by various ESP32 and PIR sensor tutorials available online.
- Special thanks to the open-source community for their contributions.
