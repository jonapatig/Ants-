import pygame as pg
import cv2
import serial

# Initialize Pygame
pg.mixer.init()
pg.init()

# Initialize video capture
cap = cv2.VideoCapture('testVideo.mp4')

# Serial setup
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

# Define segments
segments = [
    (0, 144),
    (145, 351),
    (352, 601),
    (0, 144)
]

# Load sounds
sounds = [
    pg.mixer.Sound("nature1.wav"),
    pg.mixer.Sound("antPicked2.wav"),
    pg.mixer.Sound("antsInvading3.wav"),
    pg.mixer.Sound("natureToLayer.wav"),
    pg.mixer.Sound("countryRisingSFX.wav"),
    pg.mixer.Sound("antsToQueenSFX.wav"),
    pg.mixer.Sound("queenEatingSFX.wav")
]

# Function to play video segment
def play_video_segment(start_frame, end_frame):
    cap.set(cv2.CAP_PROP_POS_FRAMES, start_frame)

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        # Display frame using Pygame or CV2 as needed
        cv2.imshow('Video', frame)
        cv2.waitKey(1)  # Adjust waitKey delay if necessary for smoother playback

        # Serial input handling
        if ser.in_waiting > 0:
            data = ser.readline().decode().strip()
            current_phase = int(data)
            if current_phase in range(8):
                return current_phase

        current_frame = cap.get(cv2.CAP_PROP_POS_FRAMES)
        if current_frame > end_frame:
            break

    cap.release()
    cv2.destroyAllWindows()
    return None

# Main loop
segment_index = 0
while segment_index < len(segments):
    start_frame, end_frame = segments[segment_index]
    phase = play_video_segment(start_frame, end_frame)

    # Handle phase transition
    if phase is not None:
        if phase == 0:
            pg.mixer.Channel(0).play(sounds[0], loops=-1)
        elif phase in [1, 2, 3]:
            pg.mixer.Channel(1).play(sounds[1], loops=-1)
        elif phase in [4, 5, 6]:
            pg.mixer.Channel(2).play(sounds[2], loops=-1)
        elif phase == 7:
            pg.mixer.Channel(3).play(sounds[3], loops=-1)

        # Move to next segment
        segment_index += 1

# Cleanup
pg.quit()
