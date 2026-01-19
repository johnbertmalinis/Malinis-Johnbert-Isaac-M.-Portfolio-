import serial
import time
import os
import sys

# ==========================================
# CONFIGURATION
# CHECK YOUR ARDUINO IDE -> TOOLS -> PORT
# Windows Example: 'COM3'
# Mac/Linux Example: '/dev/ttyUSB0' or '/dev/ttyACM0'
# ==========================================
SERIAL_PORT = 'COM9' 
BAUD_RATE = 9600

def initialize_serial():
    """Establishes connection with Arduino"""
    try:
        print(f"Connecting to {SERIAL_PORT}...")
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        time.sleep(2) # Wait for Arduino to reset/reboot upon connection
        
        # Check if Arduino sent a "System Ready" message
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            print(f"Arduino says: {line}")
            
        return ser
    except serial.SerialException as e:
        print(f"CRITICAL ERROR: Could not open port {SERIAL_PORT}")
        print(f"Details: {e}")
        print("Hint: Close the Arduino Serial Monitor and try again.")
        sys.exit(1)

def clear_screen():
    """Clears terminal screen based on OS"""
    os.system('cls' if os.name == 'nt' else 'clear')

def print_menu():
    """Prints the user interface"""
    print("=============================")
    print("   ARDUINO LED CONTROLLER    ")
    print("=============================")
    print("[R] Red ON/OFF")
    print("[G] Green ON/OFF")
    print("[B] Blue ON/OFF")
    print("[A] All ON")
    print("[O] All OFF")
    print("[X] Exit")
    print("=============================")

def read_arduino_response(ser):
    """Reads all available lines from Arduino"""
    # Give Arduino a tiny moment to process and reply
    time.sleep(0.1) 
    
    if ser.in_waiting > 0:
        while ser.in_waiting > 0:
            try:
                # Read line, decode bytes to string, remove whitespace
                line = ser.readline().decode('utf-8').strip()
                if line:
                    print(f">> {line}")
            except:
                pass

def main():
    arduino = initialize_serial()
    print_menu()

    while True:
        # clear_screen()

        
        user_input = input("Enter selection: ").strip()
        
        # Handle empty input
        if not user_input:
            continue

        # Case Insensitivity: Convert to lowercase
        command = user_input.lower()
    
        # Exit Logic
        if command == 'x':
            print("Closing connection...")
            arduino.close()
            print("Goodbye!")
            break
        
        # Valid commands
        if command in ['r', 'g', 'b', 'a', 'o']:
            # 1. Send Command
            arduino.write(command.encode())
            
            # 2. Read Response from Arduino (The Logging)
            read_arduino_response(arduino)
            
            
        else:
            print("Error: Invalid selection. Use R, G, B, A, or O.")
            time.sleep(1)

if __name__ == "__main__":
    main()