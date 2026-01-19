import serial
import time

PORT = "COM3"      # CHANGE THIS
BAUD = 9600

ser = serial.Serial(PORT, BAUD, timeout=0.1)
time.sleep(2)  # Allow Arduino reset

print("Listening to Arduino...")

while True:
    if ser.in_waiting:
        data = ser.readline().decode().strip().upper()

        if data == "R":
            ser.write(b"1")
            print("R received -> sent 1")
        elif data == "G":
            ser.write(b"2")
            print("G received -> sent 2")
        elif data == "B":
            ser.write(b"3")
            print("B received -> sent 3")

