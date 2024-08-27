# ESP32 Kitchen Activity Monitor

This project uses an ESP32 microcontroller and a PIR motion sensor to monitor kitchen activity. The ESP32 hosts a webserver that displays the current status of the kitchen, helping to determine when the kitchen is available.

## Features

- **Motion Detection**: Uses a PIR motion sensor to detect activity in the kitchen.
- **Web Interface**: Hosts a webserver on the ESP32 to display the kitchen status.
- **Real-time Updates**: Provides real-time updates on kitchen availability.
- **Low Power Consumption**: Efficiently monitors activity with minimal power usage.
  
![WIN_20240827_11_28_26_Pro](https://github.com/user-attachments/assets/0f185d23-f518-45b7-a478-7a24ccc66a7e)


## Description

> An Esp32 embedded project that runs a web server
> on a local network which can be accessed with a private ip **( SEE SECURITY CONSIDERATIONS BELOW )**.
> Once a user connects via the private ip, the device responds with html and js
> that display minutes until last activity so they user can get a better idea
> of how to plan around their meals / meal prep. 


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

4. **Configuration**

    - The ip for the fetch callback must be configured after getting the ip from the Serial terminal
    - The activity timeout can be reconfigured in the js, default is to show green after 5 minutes.
5.  **Security Considerations**
>   Running an esp32 device with this code 
>   means that anyone with your ssid and pw 
>   will be able to view the webpage. 
>
## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

- Inspired by various ESP32 and PIR sensor tutorials available online.
- Special thanks to the open-source community for their contributions.
