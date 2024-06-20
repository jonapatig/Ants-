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

track_1 = pg.mixer.Sound("VideoControls/Techno1.wav")
track_2 = pg.mixer.Sound("VideoControls/Techno2.wav")
track_3 = pg.mixer.Sound("VideoControls/Techno3.wav")

sfx = [pg.mixer.Sound("VideoControls/sfxTest1.wav"), pg.mixer.Sound("VideoControls/sfxTest2.wav"), pg.mixer.Sound("VideoControls/sfxTest3.wav")]

pg.mixer.set_num_channels(50)

pg.mixer.find_channel().play(track_1, loops=-1)
pg.mixer.find_channel().play(track_2, loops=-1)
pg.mixer.find_channel().play(track_3, loops=-1)

volume_1 = 1.0
volume_2 = 1.0
volume_3 = 1.0

channel_1_on = True
channel_2_on = True
channel_3_on = True

def play_video_segment(video, start_frame, end_frame, fps, offset, volume_1, volume_2, volume_3, channel_1_on, channel_2_on, channel_3_on, previous_segment):
    cap = cv2.VideoCapture(video)
    cap.set(cv2.CAP_PROP_POS_FRAMES, start_frame + offset)

    ##########################################
    # Arduino serial as input
    # ser = serial.Serial(COMPORT, BAUDRATE, timeout=int(1000 / fps)) # ALL CAPS VARIABLES SHOULD BE DEFINED
    ##########################################

    while cap.isOpened():
        if channel_1_on:
            if volume_1 < 1.0:
                volume_1 += 0.01
        else:
            if volume_1 > 0.0:
                volume_1 -= 0.01
        
        if channel_2_on:
            if volume_2 < 1.0:
                volume_2 += 0.01
        else:
            if volume_2 > 0.0:
                volume_2 -= 0.01

        if channel_3_on:
            if volume_3 < 1.0:
                volume_3 += 0.01
        else:
            if volume_3 > 0.0:
                volume_3 -= 0.01


        track_1.set_volume(volume_1)
        track_2.set_volume(volume_2)
        track_3.set_volume(volume_3)

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
            return int(current_frame), int(chr(current_phase)) - 1, volume_1, volume_2, volume_3, channel_1_on, channel_2_on, channel_3_on, previous_segment
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
        #         return int(current_frame), current_phase - 1, volume_1, volume_2, volume_3, channel_1_on, channel_2_on, channel_3_on
        ##########################################
            
    
    cap.release()
    cv2.destroyAllWindows()
    return None

video_path = 'VideoControls/testVideo.mp4'
fps = 100

segment_index = 0
start_frame, end_frame = segments[segment_index]
start_offset = 0

while True:
    result = play_video_segment(video_path, start_frame, end_frame, fps, start_offset, volume_1, volume_2, volume_3, channel_1_on, channel_2_on, channel_3_on, segment_index)
    if result is None:
        break

    frame_ended, segment_index, volume_1, volume_2, volume_3, channel_1_on, channel_2_on, channel_3_on, previous_segment = result

    if segment_index != previous_segment:
        pg.mixer.find_channel().play(sfx[segment_index])

    if segment_index == 0:
        channel_1_on = True
        channel_2_on = True
        channel_3_on = True

    if segment_index == 1:
        channel_1_on = True
        channel_2_on = False
        channel_3_on = True

    if segment_index == 2:
        channel_1_on = True
        channel_2_on = False
        channel_3_on = False

    print(f"Volume 1: {volume_1}, Volume 2: {volume_2}, Volume 3: {volume_3}")

    start_offset = frame_ended - start_frame
    
    start_frame, end_frame = segments[segment_index]

    print(f"Segment {segment_index} played from frame {start_offset} to {end_frame}")
    if start_offset + start_frame > end_frame:
        start_offset = 0