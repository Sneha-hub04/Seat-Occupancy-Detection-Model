# ESP32 Seat Occupancy Monitoring System
ESP32-based seat occupancy system using IR sensors and OLED display with register-level GPIO control, visualizing a real-time 4×4 seat matrix.

## Features

- **Real-time Monitoring**: Instant detection of seat occupancy using IR sensors  
- **Low-level GPIO Control**: Register-level programming for fast and deterministic sensor reading  
- **OLED Visualization**: Displays a real-time **4×4 seat matrix**  
- **Efficient Firmware**: Minimal latency and direct hardware interaction  
- **Scalable Design**: Can be extended to larger seat matrices  
- **Embedded Systems Focus**: No dependency on high-level GPIO libraries  

## Hardware Components

- **Microcontroller**: ESP32 Development Board (ESP32-WROOM-32) 
- **Display**: OLED Display (I2C)  
- **Sensors**: IR Proximity Sensors (4×)  
- **GPIO Configuration**:  
  - 3 IR sensors connected directly to OLED logic  
  - 1 IR sensor connected to **GPIO15** of ESP32 using register-level access  
- **Power Supply**: 5V USB / External Adapter
- 
## System Architecture
| IR Sensors | ---> | ESP32 | ---> | OLED Display |
| (GPIO + I2C)| | (Register | | (4×4 Seat Matrix)|
| | | Level GPIO)| 
## Seat Matrix Representation

- Each block in the OLED represents a seat  
- Occupied seats are highlighted  
- Vacant seats remain unmarked
[ ■ ■ □ □ ]
[ □ ■ ■ □ ]
[ □ □ ■ □ ]
[ ■ □ □ ■ ]

- 3 IR sensors interface directly with the OLED logic  
- 1 IR sensor is connected to **GPIO15** of ESP32 using **register-level programming**  
- ESP32 processes sensor data and updates the OLED display in real time  

## Pin Configuration

| Component      | ESP32 Pin | Description                              |
|---------------|----------|------------------------------------------|
| IR Sensor 1   | GPIO Conn | Seat occupancy input (direct)            |
| IR Sensor 2   | GPIO Conn | Seat occupancy input (direct)            |
| IR Sensor 3   | GPIO Conn | Seat occupancy input (direct)            |
| IR Sensor 4   | GPIO 15   | Register-level controlled IR sensor      |
| OLED SDA      | GPIO 21   | I2C data line                             |
| OLED SCL      | GPIO 22   | I2C clock line                            |
| VCC           | 3.3V      | Power supply                             |
| GND           | GND       | Common ground                            |

---

## Installation

### 1. Hardware Setup

1. **Connect IR sensors**
   - IR Sensor 1–3 → OLED interface  
   - IR Sensor 4 OUT → **GPIO15 (ESP32)**  
   - VCC → 3.3V  
   - GND → GND  

2. **Connect OLED Display**
   - SDA → GPIO 21  
   - SCL → GPIO 22  
   - VCC → 3.3V  
   - GND → GND  

3. Place IR sensors under seats facing upward

4. Adjust IR sensor sensitivity using onboard potentiometers

---

## Seat Matrix Display Logic

- OLED displays a **4×4 seat matrix**
- Each cell represents one seat
- Occupied seats are highlighted
- Display updates dynamically based on IR sensor input



## Software Details

- **Programming Language**: Embedded C  
- **GPIO Handling**: Direct register access (no HAL / Arduino GPIO APIs)  
- **Display Interface**: I2C communication with OLED  
- **Focus Area**: Embedded firmware, low-level hardware control  

## Applications

- Smart classrooms  
- Auditoriums  
- Library seat tracking  
- Embedded systems learning projects  

## Future Improvements

- Wi-Fi based data transmission  
- Web dashboard visualization  
- Database integration  
- Power optimization using sleep modes  


