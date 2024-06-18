"""
First video: frame 0-144 or 00:00:00-00:01:44
Second video: frame 145-351 or 00:01:45-00:03:51
Third video: frame 352-601 or 00:03:52-00:06:01
"""

import cv2
import pygame as pg
import serial

segments = [
    (0, 144),    # 00:00:00 - 00:01:44
    (145, 351),  # 00:01:45 - 00:03:51
    (352, 601)   # 00:03:52 - 00:06:01
]

pg.mixer.init()
pg.init()

track1 = pg.mixer.Sound("VideoControls/Techno1.wav")
track2 = pg.mixer.Sound("VideoControls/Techno2.wav")
track3 = pg.mixer.Sound("VideoControls/Techno3.wav")

pg.mixer.set_num_channels(3)

pg.mixer.find_channel().play(track1, loops=-1)
pg.mixer.find_channel().play(track2, loops=-1)
pg.mixer.find_channel().play(track3, loops=-1)

volume1 = 1.0
volume2 = 1.0
volume3 = 1.0

channel1On = True
channel2On = True
channel3On = True

def play_video_segment(video, start_frame, end_frame, fps, offset, volume1, volume2, volume3, channel1On, channel2On, channel3On):
    cap = cv2.VideoCapture(video)
    cap.set(cv2.CAP_PROP_POS_FRAMES, start_frame + offset)

    ##########################################
    # Arduino serial as input
    # ser = serial.Serial(COMPORT, BAUDRATE, timeout=int(1000 / fps)) # ALL CAPS VARIABLES SHOULD BE DEFINED
    ##########################################

    while cap.isOpened():
        if channel1On:
            if volume1 < 1.0:
                volume1 += 0.01
        else:
            if volume1 > 0.0:
                volume1 -= 0.01
        
        if channel2On:
            if volume2 < 1.0:
                volume2 += 0.01
        else:
            if volume2 > 0.0:
                volume2 -= 0.01

        if channel3On:
            if volume3 < 1.0:
                volume3 += 0.01
        else:
            if volume3 > 0.0:
                volume3 -= 0.01


        track1.set_volume(volume1)
        track2.set_volume(volume2)
        track3.set_volume(volume3)

        ret, frame = cap.read()
        if not ret:
            break

        current_frame = cap.get(cv2.CAP_PROP_POS_FRAMES)
        if current_frame > end_frame:
            cap.set(cv2.CAP_PROP_POS_FRAMES, start_frame)
        
        cv2.imshow('Video', frame)

        ##########################################
        # Keyboard as input
        current_phase = cv2.waitKey(int(1000 / fps))

        if current_phase in [ord('1'), ord('2'), ord('3')]:
            cap.release()
            return int(current_frame), int(chr(current_phase)) - 1, volume1, volume2, volume3, channel1On, channel2On, channel3On
        if current_phase == ord('q'):
            break
        ##########################################

        ##########################################
        # Arduino serial as input
        # data = ser.readline().decode().strip()
        # if data:
        #     current_phase = int(data)
        #     if current_phase in [1, 2, 3]:
        #         cap.release()
        #         return int(current_frame), current_phase - 1, volume1, volume2, volume3, channel1On, channel2On, channel3On
        ##########################################
            
    
    cap.release()
    cv2.destroyAllWindows()
    return None

video_path = 'VideoControls/testVideo.mp4'
fps = 100

current_segment = 0
start_frame, end_frame = segments[current_segment]
start_offset = 0

while True:
    result = play_video_segment(video_path, start_frame, end_frame, fps, start_offset, volume1, volume2, volume3, channel1On, channel2On, channel3On)
    if result is None:
        break

    frame_ended, segment_index, volume1, volume2, volume3, channel1On, channel2On, channel3On = result

    if segment_index == 0:
        channel1On = True
        channel2On = True
        channel3On = True

    if segment_index == 1:
        channel1On = True
        channel2On = False
        channel3On = True

    if segment_index == 2:
        channel1On = True
        channel2On = False
        channel3On = False

    print(f"Volume 1: {volume1}, Volume 2: {volume2}, Volume 3: {volume3}")

    start_offset = frame_ended - start_frame
    
    start_frame, end_frame = segments[segment_index]

    print(f"Segment {segment_index} played from frame {start_offset} to {end_frame}")
    if start_offset + start_frame > end_frame:
        start_offset = 0