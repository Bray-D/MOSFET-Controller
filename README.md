# MOSFET-Controller
This repository contains all relevant files for my custom MOSFET controller. It includes hardware designs,
schematics, and code. This project is solely developed by Brady Girard. 

If anyone reads this, thank you for looking at my projects. I make them for niche personal uses, but they let me
learn new things and improve my electronics skills.

# Purpose
The purpose of this project was to control a DC motor using a MOSFET and microcontroller (MCU). The MCU
interrupts power flow to the motor to control the number of revolutions. It does NOT control the speed of
the motor. This project is applicable to, but not limited to, small pump controls, solenoid driving, 
remote-controlled devices, and lighting control (can only control power flow, not lighting colours).

# Electrical Characteristics
- The controller works with batteries from 6V to 20V. Any voltage higher than 20V will damage the MOSFET.
Any voltage lower than 6V will not power the MCU correctly. 
- In low power mode, current draw is 300 uA.
- Two wire input (one ground, one trigger) allows for stable triggering and external ground reference.
- Input voltage should not exceed 5V. At least 4V is recommended for stability.
- Input signal wakes MCU on falling edge.
- High power design allows PCB to withstand 15A of continuous current.
- Able to withstand ~25A of peak current during motor startup.
- Programmed through SPI.
