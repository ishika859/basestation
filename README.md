# Autonomous Drone Charging Base Station

This is the complete build documentation for our **Autonomous Drone Charging Base Station**
The main idea behind this project was to make a base station where an autonomous drone can land whenever its battery gets low, get automatically aligned towards the center and charge itself without requiring any manual help.
One of the biggest problems we wanted to solve was that the drone might not land exactly at the center of the base station every time. To solve this, we designed a four-rod centering mechanism using **NEMA 17 stepper motors and T8 lead screws**.
The first two rods move towards the drone and bring it towards the center. Once the drone is aligned, the other two rods move towards it and connect through copper charging plates. After charging is completed, the rods move back and the drone can take off again.
The base station uses Arduino Uno, CNC shields, DRV8825 drivers and an ESP32-based communication system to control the complete mechanism.
<img width="1198" height="1164" alt="image" src="https://github.com/user-attachments/assets/15af1bee-e4b8-4d50-a295-ff0d71ce3058" />


## Features

- Automatic drone alignment after landing
- Four-rod centering mechanism
- NEMA 17 stepper motors for controlled movement
- T8 lead screw mechanism for linear motion
- Limit switches for accurate rod positioning
- Copper plate-based charging connection
- Arduino Uno for motor control
- CNC Shield with DRV8825 drivers
- Separate power supplies for motors and Arduino
- ESP32-based wireless communication with the drone
- Automatic docking and charging sequence
- Expandable system with LiDAR-based landing confirmation

## BOM – Bill of Materials

| Component | Qty. | Purpose | Price (USD/unit) | Purchase link |
|---|---:|---|---:|---|
| NEMA 17 Stepper Motor | 8 | Moves the four alignment rods | $9.03 | [FlyRobo](https://www.flyrobo.in/nema-17-stepper-motor-42x47mm-0.48nm) |
| T8 Lead Screw Rod (400mm) | 4 | Converts motor rotation into linear movement | $3.20 | [Invento Sales](https://www.inventosales.com/) |
| T8 Nuts | 4 | Moves along the lead screws | $0.59 | [Amazon India](https://www.amazon.in/) |
| Shaft Couplers (5mm–8mm) | 8 | Connects motor shafts to lead screws | $0.82 | [Robokits India](https://robokits.co.in/) |
| Aluminium Rods | 4 | Used as the main moving alignment rods | $1.49 | [Ubuy India](https://www.ubuy.co.in/) |
| NEMA 17 Motor Holders | 8 | Holds the stepper motors in position | $2.15 | [Quartz Components](https://quartzcomponents.com/) |
| Arduino Uno R3 | 2 | Controls the motor mechanism | $2.47 | [Amazon India](https://www.amazon.in/) |
| CNC Shield V3 | 2 | Interfaces motor drivers with Arduino | $1.18 | [AM Electronics](https://amelectronics.in/product/cnc-shield-v3-arduino-uno-mega-compatible/) |
| DRV8825 Drivers | 8 | Controls the stepper motors | $1.71 | [Quartz Components](https://quartzcomponents.com/) |
| Limit Switches | 4 | Detects the rod's end position | $0.27 | [Probots](https://probots.co.in/micro-switch.html) |
| ESP32 Development Board | 1 | Handles communication with the drone | $4.25 | [Partsly](https://partsly.in/product/esp32-devkit-v1) |
| Copper Plates | 4 | Provides electrical contact for charging | $2.70 | [Amazon India](https://www.amazon.in/dp/B0D9J6QK5X) |
| 12mm Plywood | As required | Main base station structure | $22.84/sheet | [Plyneer](https://plyneer.com/) |
| Screws and Nuts | As required | Fixing different components | $2.65/kit | [GSK CUT](https://gskcut.in/) |
| Power Supply (12V 10A) | As required | Provides power to motors and electronics | $8.51 | [Electronic Spices](https://electronicspices.com/product/12v-10a-120watt-dc-output-smps-metal-case-power-supply-ac-to-dc/) |


## Circuit Diagram
<img width="1586" height="1214" alt="image" src="https://github.com/user-attachments/assets/2d832c4b-0667-496d-ba41-9ab372668acc" />

The wiring process starts by mounting the CNC Shield V3 onto the Arduino Uno R3. The shield is connected directly to the Arduino's pin headers, allowing it to control the stepper motors through dedicated driver slots.
Next, the DRV8825 stepper motor drivers are inserted into the CNC Shield's driver sockets, making sure their pin orientations match the shield's markings. Each driver is assigned to a motor axis, and the stepper motors are connected to the corresponding output terminals.
The four limit switches are connected to the appropriate end-stop inputs on the CNC Shield to detect the alignment rods' end positions and prevent them from moving beyond their limits.
The 12V power supply is connected to the CNC Shield's motor power input to provide power to the stepper motors. The Arduino receives power separately through USB or a suitable regulated supply.
The ESP32 development board is connected to the Arduino through suitable communication and control connections. It handles communication with the drone and sends the required commands to the motor-control system.

Finally, the copper plates are connected to the charging circuit to provide electrical contact when the drone reaches the charging position. All grounds and power connections are checked before switching on the system.

Important wiring considerations:
- Check the DRV8825 driver orientation before inserting it.
- Set the motor driver's current limit according to the stepper motor specifications.
- Use suitable power wiring for the motors.
- Ensure the ESP32 and Arduino share a common ground when using signal connections.
- Verify the limit switch logic and motor directions before running the complete mechanism.
  
Super Important : The CNC Shield V3 normally supports up to four stepper drivers, so with eight motors and two Arduino/shield setups, divide the motors between the two shields. Also, verify the ESP32 communication wiring and charging circuit separately before powering everything.

## Mechanical Design

The mechanical design is based on four moving rods placed around the landing area. We initially thought of using a belt and pulley mechanism but later shifted to lead screws because of the cost and the way we wanted to control the movement.

Each motor is connected to a T8 lead screw using a coupler. When the motor rotates, the lead screw rotates along with it and the T8 nut moves forward or backward. The nut is connected to the moving mechanism which carries the alignment rod.

We divided the movement into two stages:

**Stage 1 – Drone Alignment**

The first two rods move towards the drone and gradually push it towards the center of the base station.

**Stage 2 – Docking and Charging**

Once the drone is centered, the other two rods containing copper charging plates move towards the drone and make contact with its charging points.

This two-stage movement makes the alignment and docking process more controlled.

## Electronics and Components

### Arduino Uno R3

Arduino Uno is used as the main controller for the motor mechanism. We use two Arduino boards so that each side of the base station can be controlled independently.

**Specifications:**
- Microcontroller: ATmega328P
- Operating Voltage: 5V
- Clock Speed: 16MHz

### CNC Shield

The CNC shield is mounted on top of the Arduino and is used to connect the stepper motor drivers. It makes the motor connections more organized and easier to manage.

**Specifications:**
- Compatible with Arduino Uno
- Supports A4988 and DRV8825 drivers
- Supports up to 4 stepper motor drivers per shield

### DRV8825

DRV8825 drivers are used between the Arduino and stepper motors. They control the stepping sequence and motor current.

**Specifications:**
- Operating Voltage: 8.2V–45V
- Microstepping: Up to 1/32
- Control Interface: STEP and DIR

### NEMA 17 Stepper Motor

We selected NEMA 17 motors because we needed controlled and repeatable movement for the rods.

**Specifications:**
- Step Angle: 1.8°
- Steps per Revolution: 200
- Shaft Diameter: 5mm

### Limit Switches

Initially we were using fixed step values in the code to control the rod positions. But we realized that the actual position could sometimes be different. So we added limit switches which tell the Arduino when a rod has reached its required position.

When a rod presses the switch, the electrical signal changes and the Arduino stops that particular motor.

### ESP32

The ESP32 is being used for communication between the drone and the base station. Whenever the drone receives a landing command, it can send a message to the ESP32. After receiving the landing confirmation, the ESP32 can trigger the base station mechanism through the Arduino.

## Charging System

Initially we planned to use XT60 connectors for charging. However, during testing we realized that getting the connectors to meet at exactly the right position every time could be difficult.

So we decided to shift towards copper plates.

We are using four rectangular copper plates as charging contacts. The main advantage is that they provide a larger contact area, so small positioning errors are less likely to prevent the electrical connection.

The plates are mounted at the required contact positions and connected to the charging circuit. Once the drone is aligned and docked, the copper plates make contact and charging can begin.

## Power Supply

We decided to keep the Arduino and motor power supplies separate.

The stepper motors require much more current than the Arduino, so using the same supply could cause voltage drops and make the controller unstable.

The Arduino handles the control signals while the separate motor supply provides power to the stepper motors.

## How the System Works

The complete working process is divided into different steps:

1. The drone monitors its battery level while flying autonomously.
2. When the battery gets low, the drone receives a command to return and land.
3. The drone sends a landing status message to the ESP32.
4. The ESP32 waits for landing confirmation before activating the base station.
5. The first two rods move towards the drone and align it towards the center.
6. The other two rods move in with the copper charging plates.
7. Once proper electrical contact is established, charging begins.
8. After charging is completed, the rods move back to their original position.
9. The drone can then take off and continue its autonomous flight.

## How to Build This...

### Step 1: Component Selection

First we selected all the components required for the base station. We initially considered a belt and pulley mechanism but later decided to use T8 lead screws and NEMA 17 motors.

### Step 2: CAD Modelling

We started making the CAD model of the complete base station. Finding accurate models of T8 nuts and other components was a little difficult because they were not easily available. We first made rough models to understand the dimensions and later corrected them using the actual measurements.

### Step 3: Wooden Base Preparation

We used 12mm plywood for the main base because it was strong enough for the structure and could handle the forces produced by the moving mechanism.

We spent a lot of time measuring, cutting, drilling and screwing all the wooden parts together.

### Step 4: Motor Holder Design

Initially we made rough CAD models of the motor holders to understand how the motors would fit. Later we made more accurate holders according to the actual motor measurements and fixed them onto the base.

### Step 5: Rod Assembly

After fixing the motors and holders, we attached the T8 lead screws, nuts and all four aluminium rods. We also made small models to check fitting errors before fixing the final parts.

### Step 6: Motor Wiring

We connected the stepper motors to the DRV8825 drivers through the CNC shields. Each motor was tested individually before trying to operate multiple motors together.

### Step 7: Limit Switch Installation

We added limit switches to detect when the rods reach their required positions. These switches act as physical stopping points and help reduce dependency on fixed step values.

### Step 8: Charging Plate Installation

We initially used XT60 connectors but later changed the design to four rectangular copper plates. We cut and fixed the plates at the required charging positions and tested the electrical contact.

### Step 9: ESP32 Communication

We started working on wireless communication between the drone and ESP32. The idea is that when the drone receives the landing command, it also sends a message to the ESP32 which then activates the base station after confirming landing.

### Step 10: Final Testing

Finally we tested the complete mechanism, including rod movement, alignment, limit switches and charging contacts. We made several changes in the code and mechanical positioning to get everything working together.

## Testing and Debugging

The testing part took a lot more time than we initially expected.

During our first test we were only able to move one rod properly. We faced multiple issues with wiring, motor movement and code logic.

After that we started testing two motors together and then worked towards getting all four rods to move properly.

One of the biggest difficulties was aligning all four rods. Even a small difference in their movement could affect the complete mechanism.

We also faced problems with hardcoded motor positions, which is why we added limit switches.

Another major change was shifting from XT60 connectors to copper plates because we wanted a more reliable charging connection.

Every time something failed, we had to go back, check the code or mechanical setup and make changes. This process involved a lot of trial and error but helped us improve the design.

## Known Issues and Future Improvements

1. Improve the accuracy of drone landing detection.
2. Complete ESP32 communication with the drone flight controller.
3. Add LiDAR height data for better landing confirmation.
4. Improve the homing system for more accurate rod positioning.
5. Test the complete docking process with repeated drone landings.
6. Improve charging contact reliability.
7. Add better safety checks to prevent rods from moving at the wrong time.
8. Make the complete charging and takeoff process fully autonomous.

## Code

The base station uses Arduino code for controlling the stepper motors and ESP32 code for communication with the drone.

The main libraries and features used include:

- `AccelStepper.h` for controlling stepper motors
- `Wire.h` for I2C communication wherever required
- Arduino digital input/output for limit switches
- Wi-Fi and UDP communication for ESP32
- STEP and DIR signals for DRV8825 motor drivers

The motor code controls the movement of the rods, checks the limit switches and manages the forward and backward movement.

The ESP32 communication system is designed to receive the drone's landing status and send an activation signal to the Arduino.

## CAD Models

The CAD files include the wooden base layout, motor holders, rod arrangement and other mechanical parts used in the base station.
<img width="901" height="550" alt="image" src="https://github.com/user-attachments/assets/99bfa72f-2456-483c-9bcc-827eca630b0d" />
<img width="1205" height="476" alt="image" src="https://github.com/user-attachments/assets/a43675df-d45e-4d49-b024-4e54863ea9ae" />
<img width="1005" height="649" alt="image" src="https://github.com/user-attachments/assets/10ce7a67-f83b-43a1-b1e3-3e6b7c884ebf" />


## Final Thoughts

This project involved a lot of trial and error. We started with a simple idea of automatically centering and charging a drone but while building it we faced many problems with component selection, CAD modelling, motor alignment, wiring and code.

There were multiple times when we had to change our original design because something that looked fine in CAD did not work properly in real life.

From getting one rod to move to working towards a complete four-rod docking mechanism, the project taught us a lot about mechanical design, electronics and debugging.

The main goal was to make a base station where the drone doesn't need a perfect landing every time and can still get aligned and charged automatically.

And that is what we are working towards!
