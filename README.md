# Cycling Sensors
### By Thomas Stubbs

## Project Overview
The goal of this project is to use the STM32L4 Discover Board and peripheral sensors to gather and display data from a bicycle that is pertinent to the cyclist. Specifically, the cyclist’s speed, pedal cadence, and brake temperature will be read and displayed on the Discovery Board’s built in LCD. 
Speed and cadence will be measured in the same way, with two-piece proximity sensors to measure revolution speed. One part of the sensor will be mounted on the bicycle frame and its counterpart will be mounted on the wheel in the case of speed measurement, and on the pedal crank arm in the case of cadence measurement. Both of these peripherals will be interfaced with UART to communicate with the microcontroller.
Brake temperature will be measured using the TC-74 temperature mounted on the bicycle frame in close proximity to the brake rotor. This information will help inform the cyclist whether or not it’s safe to touch the brake system if any maintenance is required. Much in the same way as was done in Lab 4, this peripheral will communicate with the microcontroller through I2C serial interfacing.
These three measurements will be displayed on the Discovery Board’s LCD, with the joystick allowing the cyclist to page through them.

## Block Diagram
![Block Diagram](/images/CyclingSensorsBlockDiagram.jpeg)

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/stubbshub/ECE153B_Final_Project/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
