# ATmega16 Password Security System
## Project video
<div align="center">
  <a href="https://www.youtube.com/watch?v=PrcLQZHcu2s">
    <img src="https://img.youtube.com/vi/PrcLQZHcu2s/0.jpg" alt="Watch the video" width="600"></a>
  <br><br>
  <a href="https://www.youtube.com/watch?v=PrcLQZHcu2s"><b><u>▶ Click the image above to watch the full system demonstration on YouTube</u></b></a>
</div>

## Introduction
A secure password-based access control system using an ATmega16 microcontroller, featuring an interactive 16x2 LCD display and a 4x3 matrix keypad for user input.

## Features
*   **4-Digit Authentication:** Secure PIN entry system.
*   **Persistent Storage:** Utilizes EEPROM storage to retain passwords even after power cycles.
*   **Dynamic Security:** Master code functionality allows for real-time password changes.
*   **Intruder Prevention:** System timeout triggers after multiple failed access attempts.
*   **Simulation Ready:** Full Proteus simulation included for virtual testing.

## Hardware Requirements
*   ATmega16 Microcontroller
*   LM016L 16x2 LCD Display
*   4x3 Matrix Keypad
*   16MHz Crystal Oscillator
*   5V Power Supply

## Prerequisites
*   AVR GCC Toolchain
*   AVRDude (for flashing the microcontroller)
*   Proteus 8 Professional (for simulation)
*   VS Code (or any C/C++ IDE)

## Pin Configuration

**LCD Connections (PORTA):**
*   `PA0` → LCD RS
*   `PA1` → LCD RW (can be grounded)
*   `PA2` → LCD E
*   `PA3` → LCD D4
*   `PA4` → LCD D5
*   `PA5` → LCD D6
*   `PA6` → LCD D7

**Keypad Connections (PORTD):**
*   `PD0 - PD2` → Keypad Rows
*   `PD3 - PD6` → Keypad Columns

## Default Passwords
*   **Initial User Password:** `1234`
*   **Master Code (To Change Password):** `0000`

## Repository Structure
*   `src/`: Contains all C source code and header files.
*   `hex/`: Compiled binary files ready to be flashed to the ATmega16.
*   `Simulation using proteus/` & `PROJECT.pdsprj`: Proteus workspace and simulation files.
*   `docs/`: Project documentation and reference materials.
*   `Makefile`: Build automation script.

## Building the Project
To compile the source code and generate the `.hex` file, run the following command in your terminal:
```bash
make all
````
---
Author: Mohamed Ahmed Abdulhamid Abdellah

Contact: mohamed.abdulhamid404@gmail.com
