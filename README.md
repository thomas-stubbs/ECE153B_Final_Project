# Cycling Sensors
### By Thomas Stubbs

## Project Overview
  The goal of this project is to use the STM32L4 Discover Board and peripheral sensors to gather and display data from a bicycle that is pertinent to the cyclist. Specifically, the cyclist’s speed, pedal cadence, and brake temperature are read by the peripheral sensors and displayed on the Discovery Board’s built in LCD.
  
  Speed and cadence is measured in the same way, with two-piece proximity sensors to measure revolution speed. One part of the sensor is mounted on the bicycle frame and its counterpart is mounted on the wheel in the case of speed measurement, and on the pedal crank arm in the case of cadence measurement. Both of these peripherals are interfaced with UART to communicate with the microcontroller.
  
  Brake temperature is measured using the TC-74 temperature mounted on the bicycle frame in close proximity to the brake rotor. This information helps inform the cyclist whether or not it’s safe to touch the brake system, if, for instance, any maintenance is required. This peripheral communicates with the microcontroller through I2C serial interfacing.
  
  These three measurements are displayed on the Discovery Board’s LCD, with the built in joystick allowing the cyclist to page through them.

## Block Diagram
![Block Diagram](/images/CyclingSensorsBlockDiagram.jpeg)

## Weekly Updates
#### Week of 02/22/2021 - 02/28/2021

- [x] Discuss with TA's/Instructors about appropriate proximity sensors for this project.
- [ ] Order required equipment (proximity sensors, wires)
- [ ] Explore Soldering for implementation

  Still looking into hall effect sensor vs reed switch for measuring speed/cadence. From what I gather, they're a simpler type of sensor than I anticipated, interfacing with voltage/current pulses rather than digital data interfacing. I'll need to explore other ideas with this project in order to meet the required 2 different serial communication protocols. Next week will be focused on finishing up more detailed research on how to implement this project under the requirements and establishing the project organization.
  
#### Week of 03/01/2021 - 03/07/2021

- [x] Finish reseaching appropriate proximity sensor
- [x] Finalize project plan to satisfy requirements
- [x] Establish project organization
- [x] Order all necessary parts

  Decided to implement the speed and cadence sensors with simple reed swithces mounted to the bicycle frame with magnets attatched to the spoke/pedal crank arm. Both of these will communicate with the STM32L476VG Discovery Board using the microcontroller's built in timer channels operating in the capture mode. Since this is not a serial communication protocol, I've also purchased an additional HC-05 Bluetooth module to see if I can get the sensors to interface with the microcontroller wirelessly via UART and Bluetooth.
![Parts Order](/images/parts-order.png)

#### Week of 03/08/2021 - 03/14/2021

- [ ] Import and adapt project code
- [ ] Debug TC74 Temperature sensor interface
- [ ] Research how to interface reed switches and Discovery Board via Bluetooth
