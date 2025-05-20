# Smart Motion Detection and Alert System

## Overview
This project uses an Arduino MKR1000 and a PIR sensor to detect motion and send alerts via MQTT over Wi-Fi. Alerts are published to an MQTT broker (e.g., HiveMQ) and displayed on a Node-RED dashboard. A buzzer provides local audio alerts and a LED diode is activated.

## Components
- Arduino MKR1000
- PIR sensor (HC-SR501)
- Buzzer
- LED diode
- Breadboard and jump wires
- MQTT broker (e.g., `broker.hivemq.com`)
- Node-RED (for dashboard and email notifications)

## Wiring
- PIR VCC → MKR1000 5V
- PIR GND → MKR1000 GND
- PIR OUT → MKR1000 Pin 2
- Buzzer Positive → MKR1000 Pin 3
- Buzzer Negative → MKR1000 GND

## Setup Instructions
1. **Install Arduino IDE** and libraries: `WiFi101`, `PubSubClient`.
2. **Configure Wi-Fi**: Create `credentials.h` with your `ssid` and `password`.
3. **Set up MQTT Broker**:
   - Use `broker.hivemq.com` (port 1883) or a local Mosquitto broker.
4. **Verify MQTT Messages**:
   - Run: `mosquitto_sub -h broker.hivemq.com -t home/motion/entry`
   - Expected: “MOTION DETECTED” or “NO MOTION” on sensor state changes.
5. **Set up Node-RED Dashboard**:
   - Install Node-RED: `npm install -g node-red`
   - Install `node-red-dashboard`.
   - Import the provided flow and access at `http://localhost:1880/ui`.
   - Access from another PC: Use `http://<host-pc-ip>:1880/ui` (e.g., `http://192.168.1.100:1880/ui`).
6. **Set up Email Notifications**:
   - Install `node-red-node-email` and configure with Gmail SMTP (use App Password).
7. **Upload Code**: Use `motion_detector.ino`.
8. **Test**: Trigger the PIR sensor and check the dashboard/emails.

## MQTT Topics
- `home/motion/entry`: Publishes "MOTION DETECTED" or "NO MOTION" based on sensor state.

## Code Details
- File: `motion_detector.ino`
- Features:
  - Wi-Fi connection via `credentials.h`.
  - MQTT publishing with 5-second debounce.
  - PIR sensor on pin 2, buzzer on pin 3, diode on pin 4.
  - Publishes both motion and no-motion states.

## Dashboard
- A Node-RED dashboard at `http://localhost:1880/ui` displays motion status with timestamps.
- Accessible on the local network via `http://<host-pc-ip>:1880/ui`.


## Troubleshooting
- **Wi-Fi**: Verify credentials in `credentials.h`.
- **MQTT**: Ensure broker is reachable (`ping broker.hivemq.com`).
- **Dashboard Disconnection**:
  - Restart Node-RED: `node-red` in Command Prompt.
  - Check MQTT broker settings in the MQTT In node.
  - Verify internet connectivity and firewall settings (ports 1880, 1883).
  - Add a status node to monitor MQTT connection.
- **Access from Another PC**:
  - Use `http://<host-pc-ip>:1880/ui`.
  - Ensure firewall allows TCP port 1880.
  - Verify both PCs are on the same network (`ping <host-pc-ip>`).
- **PIR**: Adjust sensitivity/delay on HC-SR501 to reduce false triggers.

## License
MIT License