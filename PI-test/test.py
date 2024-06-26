'''
The magic line:
ser = serial.Serial('/dev/ttyACM0', 9600)
'''
import serial
import time

try:
    ser = serial.Serial('/dev/ttyACM0', 9600)  # Update with correct device name and baud rate
    time.sleep(2)  # Wait for the connection to establish

    if ser.is_open:
        print("Serial port is open")
        ser.write(b'Hello Arduino!\n')
        response = ser.readline()
        print(f"Response from Arduino: {response.decode('utf-8')}")
    else:
        print("Failed to open serial port")

except serial.SerialException as e:
    print(f"Serial error: {e}")

finally:
    if ser.is_open:
        ser.close()
        print("Serial port closed")