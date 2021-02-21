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
#### Week of 02/22/2021 - 03/01/2021
