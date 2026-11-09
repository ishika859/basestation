# Autonomous Drone Charging Base Station
This is the full build documentation for our Autonomous Drone Charging Base Station.

The idea is simple. When the drone's battery gets low it comes and lands on the base station, the station centers it by itself, and then it charges without anyone touching it.

The problem we kept thinking about was that the drone will almost never land exactly in the middle. So we made a four-rod centering mechanism using NEMA 17 stepper motors and T8 lead screws. Two rods push the drone towards the center. Once it's aligned, the other two rods come in and touch the drone through copper charging plates. When charging is done everything moves back and the drone can take off again.

For control we used Arduino Uno, CNC shields, DRV8825 drivers and an ESP32 for talking to the drone.

<img width="1198" height="1164" alt="image" src="https://github.com/user-attachments/assets/15af1bee-e4b8-4d50-a295-ff0d71ce3058" />

## Features
- Drone gets aligned automatically after landing
- Four-rod centering mechanism
- NEMA 17 steppers for controlled movement
- T8 lead screws for linear motion
- Limit switches so the rods stop at the right position
- Copper plates for the charging connection
- Arduino Uno for motor control
- CNC Shield with DRV8825 drivers
- Separate power supplies for motors and Arduino
- ESP32 for wireless communication with the drone
- Automatic docking and charging sequence
- Can be expanded later with LiDAR for landing confirmation

## BOM – Bill of Materials
| Component | Qty. | Purpose | Price (USD/unit) | Purchase link |
|---|---:|---|---:|---|
| NEMA 17 Stepper Motor | 8 | Moves the four alignment rods | $9.03 | [FlyRobo](https://www.flyrobo.in/nema-17-stepper-motor-42x47mm-0.48nm) |
| T8 Lead Screw Rod (400mm) | 4 | Turns motor rotation into linear movement | $3.20 | [Invento Sales](https://www.inventosales.com/) |
| T8 Nuts | 4 | Moves along the lead screws | $0.59 | [Amazon India](https://www.amazon.in/) |
| Shaft Couplers (5mm–8mm) | 8 | Connects motor shafts to lead screws | $0.82 | [Robokits India](https://robokits.co.in/) |
| Aluminium Rods | 4 | The main moving alignment rods | $1.49 | [Ubuy India](https://www.ubuy.co.in/) |
| NEMA 17 Motor Holders | 8 | Holds the stepper motors in place | $2.15 | [Quartz Components](https://quartzcomponents.com/) |
| Arduino Uno R3 | 2 | Controls the motor mechanism | $2.47 | [Amazon India](https://www.amazon.in/) |
| CNC Shield V3 | 2 | Connects motor drivers to the Arduino | $1.18 | [AM Electronics](https://amelectronics.in/product/cnc-shield-v3-arduino-uno-mega-compatible/) |
| DRV8825 Drivers | 8 | Drives the stepper motors | $1.71 | [Quartz Components](https://quartzcomponents.com/) |
| Limit Switches | 4 | Detects the end position of the rods | $0.27 | [Probots](https://probots.co.in/micro-switch.html) |
| ESP32 Development Board | 1 | Talks to the drone | $4.25 | [Partsly](https://partsly.in/product/esp32-devkit-v1) |
| Copper Plates | 4 | Electrical contact for charging | $2.70 | [Amazon India](https://www.amazon.in/dp/B0D9J6QK5X) |
| 12mm Plywood | As required | Main base structure | $22.84/sheet | [Plyneer](https://plyneer.com/) |
| Screws and Nuts | As required | Fixing everything together | $2.65/kit | [GSK CUT](https://gskcut.in/) |
| Power Supply (12V 10A) | As required | Powers the motors and electronics | $8.51 | [Electronic Spices](https://electronicspices.com/product/12v-10a-120watt-dc-output-smps-metal-case-power-supply-ac-to-dc/) |

## Circuit Diagram
<img width="1586" height="1214" alt="image" src="https://github.com/user-attachments/assets/2d832c4b-0667-496d-ba41-9ab372668acc" />

Start by putting the CNC Shield V3 on top of the Arduino Uno R3. It plugs straight into the pin headers and gives you slots for the stepper drivers.

Then push the DRV8825 drivers into the shield sockets. Match the pin orientation with the markings on the shield, this is easy to get wrong. Each driver is for one motor axis and the steppers go to the matching output terminals.

The four limit switches go to the end-stop inputs on the shield. They tell us when a rod has reached its end so it doesn't keep going past it.

The 12V supply goes to the motor power input of the CNC shield. The Arduino gets its own power separately, either USB or a regulated supply.

The ESP32 is connected to the Arduino with communication and control wires. It talks to the drone and passes the commands on to the motor side.

Last, the copper plates go to the charging circuit so they give contact when the drone is in the charging position. Before switching anything on, check all the grounds and power connections once more.

Things to keep in mind while wiring:
- Check the DRV8825 orientation before inserting it
- Set the driver current limit according to your stepper motor specs
- Use proper thick wiring for the motor power
- ESP32 and Arduino need a common ground if you are using signal connections
- Check limit switch logic and motor directions before running the whole mechanism

**Super Important:** A CNC Shield V3 only supports 4 stepper drivers. We have 8 motors so we split them across two Arduino + shield setups. Also test the ESP32 wiring and the charging circuit separately before powering everything together.

## Mechanical Design
There are four moving rods around the landing area. At first we thought about a belt and pulley system, but we moved to lead screws because of cost and also because we wanted better control over the movement.

Every motor is connected to a T8 lead screw with a coupler. When the motor turns, the screw turns and the T8 nut moves forward or backward. The nut is attached to the part that carries the alignment rod.

The movement happens in two stages:

**Stage 1 – Drone alignment**
The first two rods move in and slowly push the drone to the center of the base.

**Stage 2 – Docking and charging**
After the drone is centered, the other two rods (the ones with the copper plates) move in and touch the drone's charging points.

Doing it in two stages made the whole thing a lot easier to control.

## Electronics and Components
### Arduino Uno R3
The Arduino is the main controller for the motors. We use two boards so each side of the base station can be controlled on its own. It has an ATmega328P microcontroller, runs on 5V and the clock speed is 16MHz.

### CNC Shield
It sits on top of the Arduino and holds the stepper drivers. Mainly it keeps the motor connections neat and easier to manage. It works with Arduino Uno, supports both A4988 and DRV8825 drivers, and can hold up to 4 stepper drivers per shield.

### DRV8825
These sit between the Arduino and the steppers. They handle the stepping sequence and the motor current. They work from 8.2V to 45V, can do microstepping up to 1/32, and are controlled with just STEP and DIR signals.

### NEMA 17 Stepper Motor
We went with NEMA 17 because we needed movement that is controlled and repeatable. The step angle is 1.8° (so 200 steps per revolution) and the shaft diameter is 5mm.

### Limit Switches
In the beginning we just used fixed step values in the code for the rod positions. But the real position was sometimes different from what the code thought, so we added limit switches. When a rod presses a switch the signal changes and the Arduino stops that motor.

### ESP32
The ESP32 handles communication between the drone and the base station. When the drone gets the landing command it also sends a message to the ESP32. Once landing is confirmed, the ESP32 triggers the base station through the Arduino.

## Charging System
We first planned to use XT60 connectors for charging. But while testing we saw that making the connectors meet at exactly the right spot every single time was really hard.

So we changed to copper plates.

There are four rectangular copper plates as the charging contacts. They have a bigger contact area, so even if the drone is a little off, the connection still works.

The plates are fixed at the contact positions and wired to the charging circuit. When the drone is aligned and docked, the plates touch and charging can start.

## Power Supply
We kept the Arduino power and the motor power separate.

Steppers pull a lot more current than an Arduino, and if both are on the same supply you can get voltage drops and the controller becomes unstable.

So the Arduino only does the control signals and the other supply runs the motors.

## How the System Works
1. The drone keeps checking its battery while flying autonomously.
2. When the battery is low it gets a command to return and land.
3. The drone sends its landing status to the ESP32.
4. The ESP32 waits for the landing confirmation before starting the base station.
5. First two rods move in and align the drone to the center.
6. The other two rods move in with the copper plates.
7. When proper electrical contact is there, charging starts.
8. After charging, the rods go back to their starting position.
9. The drone takes off and continues its flight.

## How to Build This...
### Step 1: Picking components
We first decided all the components we needed. We thought of a belt and pulley mechanism at first, but went with T8 lead screws and NEMA 17 motors in the end.

### Step 2: CAD modelling
We started on the CAD model of the whole base station. Finding proper models for T8 nuts and some other parts was a bit annoying since they weren't easy to find online. So we made rough models first to understand the dimensions, then fixed them later with the real measurements.

### Step 3: Wooden base
We used 12mm plywood for the base because it's strong enough to take the forces from the moving mechanism.

A lot of time went into measuring, cutting, drilling and screwing all the wooden parts together.

### Step 4: Motor holders
First we made rough CAD models of the holders just to see how the motors fit. Later we made proper ones using the real motor measurements and fixed them to the base.

### Step 5: Rod assembly
After the motors and holders were fixed, we put on the T8 lead screws, nuts and all four aluminium rods. We also made some small test models to check for fitting errors before fixing the final parts.

### Step 6: Motor wiring
The steppers are connected to the DRV8825 drivers through the CNC shields. We tested each motor alone first before trying multiple motors together.

### Step 7: Limit switches
We added the limit switches to detect when the rods reach their position. They work like physical stoppers, so we don't depend on fixed step values anymore.

### Step 8: Charging plates
We used XT60 connectors at first but then changed to four rectangular copper plates. We cut them, fixed them at the charging positions and tested the contact.

### Step 9: ESP32 communication
We started working on the wireless communication between the drone and the ESP32. The plan is, when the drone gets the landing command it also messages the ESP32, which then starts the base station after confirming the landing.

### Step 10: Final testing
At the end we tested the whole thing, rod movement, alignment, limit switches and charging contacts. We changed the code and the mechanical positions a lot of times to get it all working together.

## Testing and Debugging
Testing took way more time than we expected.

In the first test only one rod was moving properly. We had problems with wiring, motor movement and the code logic all at once.

After that we tested two motors together, and then slowly worked up to all four rods.

Getting all four rods aligned was one of the hardest parts. Even a tiny difference in how they move can mess up the whole mechanism.

We also had trouble with hardcoded motor positions, which is why we added the limit switches.

Another big change was going from XT60 connectors to copper plates, since we wanted a charging connection that's more reliable.

Whenever something failed we had to go back, check the code or the mechanical setup and change stuff. Lots of trial and error, but it made the design better.

## Known Issues and Future Improvements
1. Landing detection needs to be more accurate
2. ESP32 communication with the drone flight controller is not finished yet
3. Add LiDAR height data for better landing confirmation
4. Better homing system for more accurate rod positions
5. Test the full docking process with many repeated landings
6. Make the charging contact more reliable
7. Add more safety checks so rods don't move at the wrong time
8. Make the whole charging and takeoff process fully autonomous

## Code
The Arduino code controls the stepper motors and the ESP32 code handles communication with the drone.

What we used:

- `AccelStepper.h` for controlling the steppers
- `Wire.h` for I2C wherever needed
- Arduino digital input/output for the limit switches
- WiFi and UDP for the ESP32
- STEP and DIR signals for the DRV8825 drivers

The motor code moves the rods, checks the limit switches and handles forward and backward movement.

The ESP32 part receives the drone's landing status and sends an activation signal to the Arduino.

## CAD Models
The CAD files have the wooden base layout, motor holders, rod arrangement and the other mechanical parts of the base station.
<img width="901" height="550" alt="image" src="https://github.com/user-attachments/assets/99bfa72f-2456-483c-9bcc-827eca630b0d" />
<img width="1205" height="476" alt="image" src="https://github.com/user-attachments/assets/a43675df-d45e-4d49-b024-4e54863ea9ae" />
<img width="1005" height="649" alt="image" src="https://github.com/user-attachments/assets/10ce7a67-f83b-43a1-b1e3-3e6b7c884ebf" />

## Final Thoughts
This project was a lot of trial and error. We started with a simple idea, centering and charging a drone automatically, but while building it we ran into problems with parts, CAD, motor alignment, wiring and code.

Many times we had to change the original design because something that looked fine in CAD just didn't work in real life.

Going from getting one rod to move to working on a full four-rod docking mechanism taught us a lot about mechanical design, electronics and debugging.

The goal was always a base station where the drone doesn't need a perfect landing and still gets aligned and charged on its own.

And that's what we're working towards!
