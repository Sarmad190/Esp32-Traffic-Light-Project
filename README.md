Esp32-Traffic-Light-Project
Smart ESP32 traffic light with pedestrian button, built in C using state machine logic.

Created by: Sarmad Shabbir, Embedded System Engineer 

Project Overview  
This project implements a traffic light control system using an ESP32 and three LEDs (Red, Yellow, Green).  
A push button acts as a pedestrian request button, instantly resetting the light sequence back to **Red** when pressed.

The logic is implemented using the State Machine programming concept, making the system clean, modular, and easy to expand.


 Features  
Traffic Light Sequence: Red → Green → Yellow → Repeat  
Pedestrian Button: Immediately resets to Red for safe crossing  
Non-blocking Delay: Uses `smart_delay()` to check button status without freezing the system  
State Machine Logic: Organizes light states clearly for easy debugging and upgrades  
ESP-IDF (Pure C): No Arduino dependency — runs directly on ESP32 SDK  


What I Learned  
This project was a great practical example for learning and applying State Machines in embedded systems:  

A State Machine ensures that the program only operates in one state at a time.  
The system switches states based on events (like button press) or timeout.  
This makes the logic predictable, readable, and **easy to maintain**.  



Hardware Required  
| Component      | Quantity | Notes |
|---------------|----------|-------|
| ESP32 Dev Board | 1 | Any ESP32 board works |
| Red LED       | 1 | Traffic stop light |
| Yellow LED    | 1 | Caution light |
| Green LED     | 1 | Go light |
| Push Button   | 1 | Pedestrian request |
| 20Ω Resistor | 3 | Current limiting for LEDs |
| Breadboard + Jumper Wires | - | For connections |



 Pin Connections  

| ESP32 Pin  | Component  |
|------------|------------|
| GPIO 2     | Red LED    |
| GPIO 16    | Yellow LED |
| GPIO 26    | Green LED  |
| GPIO 4     | Button (active-low) |

Button Wiring: 
- One side → **GPIO 4**  
- Other side → **GND**  
- Internal pull-up enabled in code (`gpio_pullup_en`)  



