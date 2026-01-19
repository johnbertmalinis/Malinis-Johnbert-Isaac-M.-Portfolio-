import serial
import requests
import time

class IoTApiClient:
    def __init__(self, port, baud_rate, base_url):
        self.port = port
        self.baud_rate = baud_rate
        self.base_url = base_url.rstrip('/')
        self.serial_connection = None

    def connect(self):
        try:
            self.serial_connection = serial.Serial(self.port, self.baud_rate, timeout=1)
            print(f"[*] Connected to Arduino on {self.port}")
        except Exception as e:
            print(f"[!] Error connecting to Serial: {e}")
            exit()

    def trigger_api(self, group_number):
        # Normalize and format the endpoint
        endpoint = f"{self.base_url}/led/group/{group_number}/toggle"
        
        print("-" * 30)
        print(f"Group number received: {group_number}")
        print(f"Endpoint called: {endpoint}")
        
        try:
            response = requests.get(endpoint) # Or .post() depending on server requirements
            if response.status_code == 200:
                print(f"API Response: Success ({response.status_code})")
            else:
                print(f"API Response: Error ({response.status_code})")
        except requests.exceptions.RequestException as e:
            print(f"API Response: Failed to connect to server ({e})")

    def run(self):
        self.connect()
        print("[*] Listening for button presses...")
        
        try:
            while True:
                if self.serial_connection.in_waiting > 0:
                    raw_data = self.serial_connection.readline().decode('utf-8').strip()
                    if raw_data:
                        clean_data = raw_data.lower()
                        self.trigger_api(clean_data)
                
                time.sleep(0.01) 
        except KeyboardInterrupt:
            print("\n[*] Shutting down client...")
        finally:
            if self.serial_connection:
                self.serial_connection.close()

if __name__ == "__main__":

    SERIAL_PORT = 'COM9'
    BAUD_RATE = 9600
    API_BASE_URL = "http://172.20.10.3:8000" # Replace with provided URL
    # API_BASE_URL = "127.0.0.1:8000" # Replace with provided URL


    client = IoTApiClient(SERIAL_PORT, BAUD_RATE, API_BASE_URL)
    client.run()