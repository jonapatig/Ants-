'''
The magic line:
ser = serial.Serial('/dev/ttyACM0', 9600)
'''
import serial
import time
import cv2
# Load an image from file
image_path = 'Schermafbeelding 2023-11-08 222452.png'  # Replace with the actual path to your image file
image = cv2.imread(image_path)

if image is None:
    print("Error: Could not load image.")
else:
    print("Image loaded successfully.")

    # Convert the image to grayscale
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    print("Image converted to grayscale.")

    # Display the original image
    cv2.imshow('Original Image', image)
    cv2.waitKey(0)

    # Display the grayscale image
    cv2.imshow('Grayscale Image', gray_image)
    cv2.waitKey(0)

    # Close all OpenCV windows
    cv2.destroyAllWindows()
    
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