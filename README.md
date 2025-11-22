# ATMega16 Password Security System

A secure password-based access control system using ATmega16 microcontroller with LCD display and keypad input.

## Features
- 🔐 4-digit password authentication
- 📟 16x2 LCD display for user interface
- ⌨️ 4x3 matrix keypad for input
- 💾 EEPROM storage for persistent passwords
- 🔄 Password change functionality
- ⏰ Timeout after multiple failed attempts
- 🎯 Proteus simulation ready

## Hardware Requirements
- ATmega16 Microcontroller
- LM016L 16x2 LCD Display
- 4x3 Matrix Keypad
- 16MHz Crystal Oscillator
- 5V Power Supply
##Prerequisites
- AVR GCC Toolchain
- AVRDude (for flashing)
- Proteus 8 Professional (for simulation)
- vscode or any c software 
## Pin Configuration

### LCD Connections (PORTA)
- PA0 → LCD RS
- PA1 → LCD RW (can be grounded)
- PA2 → LCD E
- PA3 → LCD D4
- PA4 → LCD D5
- PA5 → LCD D6
- PA6 → LCD D7

### Keypad Connections (PORTD)
- PD0-PD2 → Keypad Rows
- PD3-PD6 → Keypad Columns

## Default Password
- **Initial Password**: `1234`
- **Master Code to Change Password**: `0000`

## Simulation
The project includes Proteus simulation files in the `simulation/` folder.

## Building
```bash
make all