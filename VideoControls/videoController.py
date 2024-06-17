"""
First video: frame 0-144 or 00:00:00-00:01:44
Second video: frame 145-351 or 00:01:45-00:03:51
Third video: frame 352-601 or 00:03:52-00:06:01
"""

import cv2

segments = [
    (0, 144),    # 00:00:00 - 00:01:44
    (145, 351),  # 00:01:45 - 00:03:51
    (352, 601)   # 00:03:52 - 00:06:01
]

def play_video_segment(video, start_frame, end_frame, fps, offset):
    cap = cv2.VideoCapture(video)
    cap.set(cv2.CAP_PROP_POS_FRAMES, start_frame + offset)

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        current_frame = cap.get(cv2.CAP_PROP_POS_FRAMES)
        if current_frame > end_frame:
            cap.set(cv2.CAP_PROP_POS_FRAMES, start_frame)
        
        cv2.imshow('Video', frame)
        key_pressed = cv2.waitKey(int(1000 / fps))
        if key_pressed in [ord('1'), ord('2'), ord('3')]:
            cap.release()
            return int(current_frame), int(chr(key_pressed)) - 1
        if key_pressed == ord('q'):
            break
    
    cap.release()
    cv2.destroyAllWindows()
    return None

video_path = 'VideoControls/testVideo.mp4'
fps = 100

current_segment = 0
start_frame, end_frame = segments[current_segment]
start_offset = 0

while True:
    result = play_video_segment(video_path, start_frame, end_frame, fps, start_offset)
    if result is None:
        break

    frame_ended, segment_index = result

    start_offset = frame_ended - start_frame
    
    start_frame, end_frame = segments[segment_index]

    print(f"Segment {segment_index} played from frame {start_offset} to {end_frame}")
    if start_offset + start_frame > end_frame:
        start_offset = 0