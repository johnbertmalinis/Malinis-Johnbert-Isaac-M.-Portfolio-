import serial
import time
from fastapi import FastAPI, HTTPException
import uvicorn

app = FastAPI()


SERIAL_PORT = 'COM3'  
BAUD_RATE = 9600

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  
    print(f"Connected to Arduino on {SERIAL_PORT}")
except Exception as e:
    print(f"Error: Could not connect to Serial Port {SERIAL_PORT}. {e}")
    ser = None

def send_command(char: str):
    if ser and ser.is_open:
        ser.write(char.encode())
    else:
        raise HTTPException(status_code=503, detail="Arduino not connected")

# --- API ENDPOINTS ---

@app.get("/led/{color}")
async def control_led(color: str):
    color = color.lower()
    if color == "red":
        send_command('1')
        return {"status": "Red toggled"}
    elif color == "green":
        send_command('2')
        return {"status": "Green toggled"}
    elif color == "blue":
        send_command('3')
        return {"status": "Blue toggled"}
    else:
        
        raise HTTPException(status_code=400, detail="Invalid color. Use red, green, or blue.")

@app.get("/led/on")
async def all_on():
    send_command('a')
    return {"status": "All LEDs turned ON"}

@app.get("/led/off")
async def all_off():
    send_command('o')
    return {"status": "All LEDs turned OFF"}

if _name_ == "_main_":
    uvicorn.run(app, host="127.0.0.1", port=8000)
