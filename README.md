# MOSFET-Controller
This repository contains all relevant files for my custom MOSFET controller. It includes hardware designs,
schematics, and code. This project is solely developed by Brady Girard. 

If anyone reads this, thank you for looking at my projects. I make them for niche personal uses, but they let me
learn new things and improve my electronics skills.

# Purpose
The purpose of this project was to control a DC motor using a MOSFET and microcontroller (MCU). The MCU
interrupts power flow to the motor to control the number of revolutions. It does notT control the speed of
the motor. This project is applicable to, but not limited to, small pump controls, solenoid driving, 
remote-controlled devices, and DC motor control.

# Implementation
The MCU currently used is an ATtiny85. It works by staying in sleep mode until the trigger signal is detected, where it 
wakes and proceeds to one of two scenarios:
1. Start the motor, and count milliseconds until desired time is reached. This allows for precise revolution control.
2. Start the motor, and keep rotating until trigger signal goes inactive. (Acts like a buffer)

The MOSFET was not driven directly from the ATtiny85, as this could damage it. Instead, a MOSFET driver chip was used.
This allows for a higher power MOSFET to be driven, from the same MCU. It was desired to keep the PCB size small, as the
space restriction was tight. However, a bigger circuit board will allow for a more powerful MCU (STM32, ESP32, etc),
higher power FETs, and higher continuous current flow.
For a bill of materials, see the [hardware folder](/hardware). This folder also contains the schematics and layouts.

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
