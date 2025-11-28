#!/usr/bin/env python3
"""
USB Rubber Ducky Bridge - Receives commands from STM32 via UART and simulates keyboard
Requires: pip install pyserial pyautogui
"""

import serial
import time
import pyautogui
import sys

# Configuration
SERIAL_PORT = 'COM14'  # Change to your port (COM3, COM4, etc. on Windows)
BAUD_RATE = 115200

# Keyboard modifier keys (matching STM32 definitions)
KEY_CTRL_LEFT = 0x01
KEY_SHIFT_LEFT = 0x02
KEY_ALT_LEFT = 0x04
KEY_GUI_LEFT = 0x08

# HID keycode to pyautogui key mapping
HID_TO_KEY = {
    0x04: 'a', 0x05: 'b', 0x06: 'c', 0x07: 'd', 0x08: 'e', 0x09: 'f',
    0x0A: 'g', 0x0B: 'h', 0x0C: 'i', 0x0D: 'j', 0x0E: 'k', 0x0F: 'l',
    0x10: 'm', 0x11: 'n', 0x12: 'o', 0x13: 'p', 0x14: 'q', 0x15: 'r',
    0x16: 's', 0x17: 't', 0x18: 'u', 0x19: 'v', 0x1A: 'w', 0x1B: 'x',
    0x1C: 'y', 0x1D: 'z',
    0x1E: '1', 0x1F: '2', 0x20: '3', 0x21: '4', 0x22: '5',
    0x23: '6', 0x24: '7', 0x25: '8', 0x26: '9', 0x27: '0',
    0x28: 'enter', 0x29: 'esc', 0x2A: 'backspace', 0x2B: 'tab',
    0x2C: 'space', 0x2D: '-', 0x2E: '=', 0x2F: '[', 0x30: ']',
    0x31: '\\', 0x33: ';', 0x34: "'", 0x35: '`', 0x36: ',',
    0x37: '.', 0x38: '/', 0x39: 'capslock',
    0x3A: 'f1', 0x3B: 'f2', 0x3C: 'f3', 0x3D: 'f4', 0x3E: 'f5',
    0x3F: 'f6', 0x40: 'f7', 0x41: 'f8', 0x42: 'f9', 0x43: 'f10',
    0x44: 'f11', 0x45: 'f12',
}

def parse_modifier(modifier_byte):
    """Convert modifier byte to list of modifier keys"""
    modifiers = []
    if modifier_byte & KEY_CTRL_LEFT:
        modifiers.append('ctrl')
    if modifier_byte & KEY_SHIFT_LEFT:
        modifiers.append('shift')
    if modifier_byte & KEY_ALT_LEFT:
        modifiers.append('alt')
    if modifier_byte & KEY_GUI_LEFT:
        modifiers.append('win')  # Windows key
    return modifiers

def execute_keypress(key_code, modifier_byte):
    """Execute a keypress with modifiers"""
    key = HID_TO_KEY.get(key_code)
    if not key:
        print(f"Unknown key code: 0x{key_code:02X}")
        return
    
    modifiers = parse_modifier(modifier_byte)
    
    if modifiers:
        # Press with modifiers
        modifier_str = '+'.join(modifiers + [key])
        print(f"Pressing: {modifier_str}")
        pyautogui.hotkey(*modifiers, key)
    else:
        # Simple keypress
        print(f"Pressing: {key}")
        pyautogui.press(key)

def execute_string(text):
    """Type a string"""
    print(f"Typing: {text}")
    pyautogui.write(text, interval=0.05)  # Small delay between chars

def execute_enter():
    """Press Enter key"""
    print("Pressing: Enter")
    pyautogui.press('enter')

def execute_delay(ms):
    """Delay for specified milliseconds"""
    seconds = ms / 1000.0
    print(f"Delaying: {seconds}s")
    time.sleep(seconds)

def process_command(line):
    """Process a command from STM32"""
    line = line.strip()
    if not line.startswith('CMD:'):
        return
    
    parts = line[4:].split(':', 2)  # Remove 'CMD:' prefix and split
    
    if len(parts) < 1:
        return
    
    cmd_type = parts[0]
    
    try:
        if cmd_type == 'KEY' and len(parts) >= 3:
            # CMD:KEY:0x15:0x08
            key_code = int(parts[1], 16)
            modifier = int(parts[2], 16)
            execute_keypress(key_code, modifier)
            
        elif cmd_type == 'STR' and len(parts) >= 2:
            # CMD:STR:Hello World
            text = parts[1]
            execute_string(text)
            
        elif cmd_type == 'ENTER':
            # CMD:ENTER
            execute_enter()
            
        elif cmd_type == 'DELAY' and len(parts) >= 2:
            # CMD:DELAY:1000
            delay_ms = int(parts[1])
            execute_delay(delay_ms)
            
        else:
            print(f"Unknown command: {line}")
            
    except Exception as e:
        print(f"Error processing command '{line}': {e}")

def main():
    """Main function - connect to serial and process commands"""
    import serial
    print("=" * 60)
    print("USB Rubber Ducky Bridge - UART to Keyboard")
    print("=" * 60)
    print(f"Connecting to {SERIAL_PORT} at {BAUD_RATE} baud...")
    
    # Small delay to allow focus on target window
    pyautogui.PAUSE = 0.05
    
    ser = None  # Initialize to None
    
    try:
        # Open serial port
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Connected! Waiting for commands...\n")
        
        # Clear any initial garbage
        time.sleep(0.5)
        ser.reset_input_buffer()
        
        # Main loop
        while True:
            if ser.in_waiting > 0:
                try:
                    line = ser.readline().decode('utf-8', errors='ignore')
                    if line:
                        process_command(line)
                except UnicodeDecodeError:
                    pass  # Ignore decode errors
                    
    except serial.SerialException as e:
        print(f"Serial error: {e}")
        print(f"\nAvailable ports:")
        import serial.tools.list_ports
        ports = serial.tools.list_ports.comports()
        for port in ports:
            print(f"  {port.device} - {port.description}")
        sys.exit(1)
        
    except KeyboardInterrupt:
        print("\n\nExiting...")
        if ser and ser.is_open:
            ser.close()
        sys.exit(0)

if __name__ == '__main__':
    main()