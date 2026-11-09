---
title: "Autonomous base station"
author: "a_bot"
created_at: "2026-11-01"
---

# 2026-11-09: Badddddd newsssssssss

**Total time spent: 4.5 hours**

Ayoooooooo so the -z axis of the  upper level motor was not rotating at all like stalleddddd so the probelm was the limit swich of the same side level oppsite was sending a 5v out to the esp which was making a probelm for us so we tried to made a voltage divider as esp needsa only 3.3v so we need 1k plus 2.2k accross 1k and gnd to get about 3.345v lets try buit the problem was also in code the code fecthed the value procesed the value sends to esp and then esp command to other which delay the work by a lot so im planning to keep arduino in command and the esp will act as a manager so the working will be fast eas and also significant 
![image.png](https://cdn.hackclub.com/01a1c057-d5d6-7416-911d-5338676adf4c/image.png)
![image.png](https://cdn.hackclub.com/01a1c058-4b56-7420-8811-914fc75d6de4/image.png)

# 2026-11-09: testing of the base station

**Total time spent: 7 hours**

after completing the assembly and wiring we started testing the complete base station. we checked whether all four rods were moving properly and whether the limit switches were stopping them at the right positions. we also tested how the first two rods align the drone towards the center and how the other two rods make contact through the copper plates for charging. during testing we faced a few issues with rod alignment and timing so we had to make small changes in the code and adjust the positions.
![image.png](https://cdn.hackclub.com/01a1c04d-1fce-7ea9-9aad-1636343f22ad/image.png)
we also checked whether the rods were opening properly after the charging process so that the drone could take off again. we repeated the tests multiple times to make sure the mechanism was working as expected. this was one of the most important stages because we were finally testing everything together instead of testing individual components separately. seeing all the parts work together after so many errors and changes was honestly a very satisfying moment for us.
![image.png](https://cdn.hackclub.com/01a1c04d-a7f6-778c-a8fa-40f09f602ae5/image.png)

# 2026-11-09: making the base station activate automatically

**Total time spent: 5 hours**

after completing the copper plate charging setup we moved on to making the base station work automatically. we started working on the communication between the drone and the esp32. the idea is that whenever the drone gets a land command it should also send a signal to the esp32. the esp32 will then wait for some time so the drone gets enough time to land properly and after that it will start the base station mechanism. we are still working on making this process reliable because we dont want the rods to start moving before the drone has landed. this is an important part because we want the whole process to happen on its own without someone having to manually start the base station every time.
![image.png](https://cdn.hackclub.com/01a1c030-4157-7e3c-8037-8c0ad82725ed/image.png)


also a code in jetson or any on board comp u use will be like a socketio which fetches data and sends it to the eso on the wifi network 

import socket

ESP_IP = "192.168.1.100"
PORT = 4210

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def send_status(status):
    sock.sendto(
        status.encode(),
        (ESP_IP, PORT)
    )

send_status("LANDING")

send_status("LANDED")


# 2026-11-03: Copper Plate Charging 

**Total time spent: 2h 10m**

We have successfully completed the setup using the copper plate charging dock, and the system is now functioning as expected. The charging mechanism is working effectively, and we have observed that the device continues to charge even when the alignment between the copper plate and the charging dock is not 100% precise. This is a promising result, as it indicates that the setup has a certain degree of tolerance for misalignment while maintaining a reliable charging connection. The successful demonstration confirms that the current configuration is viable and provides a strong foundation for further testing and optimization to improve alignment accuracy, charging efficiency, and overall system performance.

![image.png](https://cdn.hackclub.com/01a1a186-4a72-76bc-a8bb-7e3c1419c333/image.png)


# 2026-11-03: Changing Charging System

**Total time spent: 3h 20mins**

We are now changing our charging system based on the problems we found during testing. Earlier, we were using XT60 connectors on the docking rods, but we realized that getting a proper connection every time could be difficult. Even if the drone was slightly off from the exact position, there was a chance that the XT60 connectors would not properly meet and the charging connection might not happen. To make the system more tolerant to small alignment errors, we decided to shift to copper plates. Instead of needing two connectors to meet at one exact point, the copper plates will provide a larger contact area, so even if the drone is slightly shifted up, down or sideways, the charging contacts can still touch and charging can happen. We are currently cutting four copper plates into rectangular shapes and will place them at the required charging points on the docking mechanism. This change should make the docking and charging process more reliable and reduce the need for extremely precise alignment.

![image.png](https://cdn.hackclub.com/01a1a182-9cb8-7fb4-8125-4fea28d0efad/image.png)

# 2026-11-03: Testing limit Switches And Debugging 

**Total time spent: 6h**


Once the switch is detected as pressed, the code immediately stops the movement of that particular motor. This means the motor does not continue pushing the rod even if the code had originally told it to move further. For example, if a rod is moving towards the limit switch and the switch gets clicked, the Arduino receives the signal, stops sending movement commands to that motor and the rod stops at that physical position. We use the same idea for the other rods so that each rod can find its own position independently.

This was difficult to implement because initially the motors would sometimes continue moving even after the switch was pressed, or one motor would stop while the other was still moving. We had to debug the switch wiring, HIGH and LOW states and the motor control conditions in the code. We also had to make sure that pressing one limit switch only stopped the motor connected to that switch and did not affect the other motors. After repeated testing and debugging, we were able to make the limit switches work as reliable stopping points and position references for our rods.

![image.png](https://cdn.hackclub.com/01a1a176-ff0b-7608-bd6c-431758e1b510/image.png)
https://drive.google.com/file/d/1LIQHpnA33uq011xdq--t_leklULsa00M/view?usp=sharing
![image.png](https://cdn.hackclub.com/01a1a179-5073-7f73-bb06-61d98c048030/image.png)
https://drive.google.com/file/d/1ZKhE3Rh7OpexD3rlbLMr4Ccp3lAhQizk/view?usp=sharing

# 2026-11-03: Removing HardCode

**Total time spent: 6h**

Currently, we are using hardcoded positions in the stepper motor code, which means the motor is told to move a fixed number of steps. The problem with this is that the actual position of the rod can sometimes be different because of small errors in the motor movement, slipping, or changes during assembly. To make the system more reliable, we are using limit switches as a reference point. Instead of depending completely on a fixed number of steps, we can start the rod from position 0 and keep moving it until the limit switch is pressed. Once the switch is pressed, the system knows that the rod has reached its actual end position and can use that point as a reference. This can help us get a more accurate starting position every time.

The limit switches are especially useful during **initial calibration**, where the rods need to find their exact starting position, and during **automatic docking**, where all four rods need to reach their correct positions for the drone to align properly. They also provide a safety point so that the motors do not keep moving beyond the physical limit of the mechanism. This will make the system more reliable than depending only on hardcoded step values.



![image.png](https://cdn.hackclub.com/01a1a12f-ac58-7717-9148-7e79f5bc2533/image.png)

so wiring might be confusing but its too simple cnc shield goes directly above the arduino add the drv driver 4x in the slots and near them are slots for steppers where stepper wires goes and the limit switches goes to z+ and z- simpleeeee
![image.png](https://cdn.hackclub.com/01a1a126-db85-76a0-ac28-64ba031e3a5e/image.png)


also we made the cad stande for limit switchess as we have 2 levels of elevation so we need to make of different dimensions
![image.png](https://cdn.hackclub.com/01a1a137-27a8-73c2-89cf-6c48998884d8/image.png)
![image.png](https://cdn.hackclub.com/01a1a137-fde6-7ef8-a4bf-2001fd9cc9e1/image.png)

# 2026-11-03: Switching to ESP32

**Total time spent: 4h**

During testing, we found that using the load sensor to detect the drone had several loopholes. Changes in weight, vibrations and small movements on the base could sometimes give incorrect signals, so we started looking for a more reliable way to know when the drone was actually coming back to land. For this, we decided to use an ESP32 on the same network as the drone. Whenever the drone receives the command to land, it will also send an additional command to the ESP32 telling it that the drone is now in the landing process. After receiving this command, the ESP32 will wait for a fixed amount of time, giving the drone enough time to land properly, and then activate the base station alignment mechanism. This makes the process more predictable because the base station is not trying to guess whether the drone has landed — it already knows that the drone has been instructed to land. We can also make this system more reliable by combining the landing command with LiDAR height data, so the ESP32 can check both the drone's landing state and its height above the base before activating the rods. This gives us a better way to make the docking process fully autonomous and reduces the chances of the base station activating at the wrong time.

![image.png](https://cdn.hackclub.com/01a1a151-04a8-7160-8055-c0bbd2ddbf6e/image.png)
![image.png](https://cdn.hackclub.com/01a1a151-2d21-73c6-ac2c-5fe1caf63d64/image.png)

# 2026-11-03: Autonomous Drone Detection 

**Total time spent: 4h**

After testing the alignment system, we thought about how to make the whole process more autonomous. Instead of manually giving the command to start the rods, we decided to add a load sensor to detect when the drone has actually landed on the base station. The load sensor will be placed under the landing area and will detect the increase in weight when the drone lands. We will set a suitable resistance and threshold so that the system can differentiate between the empty base station and the drone being present. Once the sensor detects that the drone has arrived, it will send a signal to the controller. This signal will act as the command saying that the drone has arrived, so the first two rods can start moving and bring the drone towards the center. After the drone is properly aligned, the other two rods containing the XT60 connectors will move in and make the charging connection. Basically, the load sensor will act as the starting point for the whole automatic process drone arrives, sensor detects it, rods align it, and the charging rods dock with it.

![image.png](https://cdn.hackclub.com/01a1a145-2a90-76fe-b250-dfcc13921e5c/image.png)


![image.png](https://cdn.hackclub.com/01a1a148-2ea8-7532-840c-61d01b8129a0/image.png)

# 2026-11-03: Rearranging Rods

**Total time spent: 4h**

While testing the four-rod mechanism, we realized that having all four rods move together was not the best way to align and dock the drone. So we changed the alignment process and divided it into two steps. First, the initial two rods move towards the drone and bring it towards the center of the base station. Their main job is to correct the drone's position and make sure it is properly aligned. Once the drone is centered, the other two rods move in and come towards the drone. These two rods have the XT60 connectors attached to them, so their job is to make the final connection and dock with the drone for charging. This change made the mechanism more controlled because instead of all four rods trying to align and dock the drone at the same time, we separated the alignment and charging process into two stages.


![image.png](https://cdn.hackclub.com/01a1a13f-1da9-7baf-a50c-4df3230c99d8/image.png)

https://drive.google.com/file/d/1jlFHutuenr1tWWqVS0hxjQhul5LEWD-u/view?usp=sharing

# 2026-11-03: Power Wiring

**Total time spent: 4h**

For the power system, we kept the Arduino and the motors on separate power supplies because the motors require much more current than the Arduino. The stepper motors can draw around 2.5A, while the Arduino only needs around 1A for its operation. If we used the same power source for both, the motors could cause voltage drops or fluctuations which could affect the Arduino and make the system unstable. So we used one power supply for the motors and a separate power supply for the Arduino. The Arduino handles the control signals while the motor supply provides the required power for the motors. Keeping them separate made the system more stable and reliable during testing.

![image.png](https://cdn.hackclub.com/01a1a11f-1114-7209-834c-58cbec87a575/image.png)

![image.png](https://cdn.hackclub.com/01a1a11f-47e1-7eeb-831f-ced316a85f65/image.png)

![image.png](https://cdn.hackclub.com/01a1a11f-750d-7031-8b69-95fbdb6658eb/image.png)

# 2026-11-03: Charging system 1

**Total time spent: 3h**

Since the main goal of our base station was to automatically charge the drone after it returned, we needed a reliable way to connect the drone with the charging supply after alignment. For this we used four XT60 connectors on the upper rods. The idea was that once the four rods move and bring the drone into the correct position, these connectors come into contact with the charging points of the drone and provide the connection needed for charging.

We chose XT60 connectors because they can handle the current required for our charging setup and also provide a strong and reliable connection. We mounted the connectors on the upper rods so that their position could change along with the rods. During testing, we first checked the alignment without power and made adjustments until the connectors were reaching the correct position.

![image.png](https://cdn.hackclub.com/01a1a11b-9df6-7518-9d8e-1607b1a2899b/image.png)

https://drive.google.com/file/d/1OL0yxfSZL1xKSxZZuia5QRw0S-qHKbxp/view?usp=sharing

# 2026-11-03: Test 2 

**Total time spent: 6h**

In the second testing stage we worked on getting all four rods to work together. This was one of the most difficult parts of the project because all four rods had to move in sync and reach the correct position at almost the same time. Even a small difference in the motor movement or alignment could make one rod move slightly differently from the others, which affected the whole mechanism.

We faced many problems with motor timing, speed, wiring and the code controlling all the motors together. Sometimes one rod would reach the position earlier while another was still moving, and sometimes the rods would not stay properly aligned. We had to repeatedly test the mechanism, find where the mismatch was happening and make changes in both the code and the physical setup.

After a lot of debugging, adjustments and testing we finally got all four rods working together. Seeing all four rods move and align properly was a big moment for us because we had struggled a lot to reach this stage. It also gave us confidence that our base station mechanism could actually work as we had planned.


![image.png](https://cdn.hackclub.com/01a1a107-4986-7087-88f2-8e9a2d081c11/image.png)
![image.png](https://cdn.hackclub.com/01a1a105-1e6f-7cac-b1a3-db3b5cf1cda0/image.png)
https://drive.google.com/file/d/1udDG64r4s_04X87JpaZYO77ZvJ0TG6u5/view?usp=sharing

# 2026-11-03: 1st test

**Total time spent: 3h**

After completing the first setup we started testing the mechanism. At the beginning we faced a lot of errors and the system was not working the way we expected. We had to debug the code, check the wiring and research different problems to understand what was going wrong. We kept testing and making small changes until we were finally able to move one rod properly. Even though it was just one rod, it gave us a lot of motivation because we knew that the basic mechanism was working. This gave us confidence to continue working on the other rods and improve the whole system step by step.

![image.png](https://cdn.hackclub.com/01a1a0fa-175a-7b61-a2eb-c5e3608990ee/image.png)


https://drive.google.com/file/d/1KylNIebtJbbAUDfoTxKKafZ_owlrRS3R/view?usp=sharing

# 2026-11-03: Coding For Rods 

**Total time spent: 5h**

For the upper charging rod we used a similar motor control system where the stepper motors move the rod towards the drone and then bring it back after charging. The Arduino controls the movement of the motors and limit switches are used to know when the rod has reached its required position. When the rod reaches the charging position the motors stop and the drone stays in that position for the charging time. In our code we kept a fixed charging wait time of 30 seconds and after that the motors automatically start moving back to their original position. This makes the charging rod work automatically without needing someone to manually open or close it.
![image.png](https://cdn.hackclub.com/01a1a147-473c-756d-bcaa-fe7fd644a89b/image.png)
![image.png](https://cdn.hackclub.com/01a1a0ea-6324-7c63-8219-8648e0a8ab17/image.png)


we could not find any software that's why we made a rough wiring diagram in free form and uploaded here.

# 2026-11-03: Fixing Rods

**Total time spent: 3h**

After fixing the motors we started attaching the four rods to the mechanism. We had to make sure the rods were properly aligned and could move smoothly when the motors were running. We used screws to fix the rods with the moving parts and also made small models first to check for errors before doing the final fixing. This helped us find small alignment and fitting issues and correct them before assembling the final version. After making the required changes we finally fixed all four rods.

![image.png](https://cdn.hackclub.com/01a1a0c3-2e02-7c6d-84b0-40f3a52e3b90/image.png)
![image.png](https://cdn.hackclub.com/01a1a0c3-419b-71b5-88be-471c5a15aa12/image.png)
![image.png](https://cdn.hackclub.com/01a1a0cb-8949-7ff3-8f3c-d5bef69a9c59/image.png)

# 2026-11-03: Firbishing and components addition 

**Total time spent: 5h**

After the main wooden structure was ready we started with the finishing part. We painted the base station and then started adding the main components like the stepper motors and their holders. We painted the top layers and the side layers were left some parts open because we still had to do the wiring and didn't want the paint to make that work difficult

For the stepper motor screw rod holders we had initially made a rough CAD design just to understand how the motor would fit and where it should be placed. After the base was ready and we had the actual components with us we made the final holder more accurately according to the real measurements. Then we fixed the motors and holders onto the base and checked if everything was fitting and moving properly

![image.png](https://cdn.hackclub.com/01a1a0a9-8604-7625-8f9d-82308e2ab735/image.png)
![image.png](https://cdn.hackclub.com/01a1a0bb-407d-75dc-b5c8-26f219931a43/image.png)


# 2026-11-03: Wood Cutting

**Total time spent: 6h**

The next major step was making our CAD design into the actual base station. We used 12mm plywood for the base because it was strong and could handle the force from the motors and the moving parts and at the same time it was easy for us to work with
![image.png](https://cdn.hackclub.com/01a1a069-bd07-7d81-86c7-0b3644bf1586/image.png)
![image.png](https://cdn.hackclub.com/01a1a06a-fdc5-7c79-a780-4367b04c2c1a/image.png)
A lot of time went into cutting the wood and making all the different parts. We first measured everything properly and marked where we had to cut and drill. After cutting we started to coat it with a layer of primer
![image.png](https://cdn.hackclub.com/01a1a06e-78c2-75c3-9aa4-d248b7d07e10/image.png)
This part took a lot of time and energy because even a small mistake in cutting or drilling could affect the whole mechanism. We had to keep checking if everything was fitting properly and sometimes make changes again

It was honestly very different from what we had made in CAD because in CAD everything looks perfect but when we actually started building it we found many small problems which we had to fix one by one

After a lot of cutting drilling screwing and adjusting we finally had the physical base station ready

# 2026-11-03: CAD MODELLING 2

**Total time spent: 2h**

![image.png](https://cdn.hackclub.com/01a1a055-9468-7989-95b0-fca807ab1462/image.png)

At this stage of the CAD design we made a rough estimation of the nut’s elevation and the mounting point of the nut on the moving mechanism. Since we were working with physical T8 components we used these initial dimensions to understand how the nut screw rod and joint would fit together and then refined the design during the later iterations.

# 2026-11-03: CAD MODELLING 

**Total time spent: 2 h**

once we had finalized the basic components for our base station, the next challenge was turning the idea into an actual design. We started with CAD modelling but this was where we faced one of our first major practical difficulties.
We knew the components we wanted to use like NEMA 17 stepper motors, couplers, T8 screw rods, T8 nuts, aluminium rods and the supporting structure but finding accurate CAD models for every component was surprisingly difficult. Components like T8 nuts and screw assemblies are not as commonly available in standard CAD libraries, so we couldn't simply download every part and start assembling them.


We had to first understand the exact dimensions of the components we were going to physically use and then figure out how to represent them accurately enough in CAD.


![image.png](https://cdn.hackclub.com/01a1a04d-3f9a-7897-9189-edb5e93daf70/image.png)
![image.png](https://cdn.hackclub.com/01a1a04d-61c1-7e5a-82ce-73ee8fcb3b0d/image.png)

# 2026-11-03: Components Finalizing 

**Total time spent: 3 h**

In the beginning one of the biggest challenges for us was actually deciding what components and what mechanism we should use for the base station.
We knew what we wanted the final system to do the drone should be able to land, get centered automatically, charge itself and then leave again. But deciding how to physically achieve that was not straightforward.
After exploring for 3 hours we ended up on the following components:

Nema 17 stepper motor - As they provide precise and repeatable movement which is important for centring the drone.
coupler- To connect stepper motor shaft to t8 screw rods and to transfer motor rotation smoothly to screw.
t8 screw rods - to convert motor rotational movement into controlled linear movement. 
t8 nuts - As they fit with to screws.
aluminium rods- they are lightweight but strong making them suitable for building the alignment structure without adding unnecessary weight.
nema 17 stepper motor holders 
arduino uno- as the main controller because it is reliable and easy to program
CNC shield - as an interface between the Arduino and the motor drivers, making it easier to connect and control multiple stepper motors in an organized way.
![image.png](https://cdn.hackclub.com/01a1a045-b473-7fdb-be7e-3d0654aa4adc/image.png)
![image.png](https://cdn.hackclub.com/01a1a046-2a5d-7af8-bcd6-bb577c6a0b1c/image.png)

# 2026-11-03: Ideation

**Total time spent: 3 hours**

so the initial idea actually started with a very simple question: what happens when an autonomous drone needs to recharge. we knew that our drone would be flying on its own so we didn't want a person to manually bring it back to the position and connect a charger every time the battery became low. 
So initially our first idea was to use a belt and pulley mechanism to move and position the drone. We explored that approach because it could provide smooth movement and good control.
But when we looked at the overall cost and the practical requirements of our project, we felt that this approach would make the system more expensive and complicated than necessary.
![image.png](https://cdn.hackclub.com/01a1a02d-532e-76fd-be1c-da3d98147f27/image.png)
![image.png](https://cdn.hackclub.com/01a1a02d-d37d-740e-9483-f7536a5fe4f3/image.png)

but we ended up using rod system stepper motor or you can say screw driver system 
![image.png](https://cdn.hackclub.com/01a1a02f-1c50-7e7c-a7e5-8be45486b754/image.png)
because it was more cost effective and more reliable to use as it saved a lot of time , cost efficiency.

