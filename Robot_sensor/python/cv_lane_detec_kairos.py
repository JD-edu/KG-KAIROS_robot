'''
1. car_video.avi 재생하는 파이썬 CV 코드를 써라 
2. 이 코드에 jd_opencv_lane_detect 모듈을 써서 차선을 인식하는 코드를 더해라 
3. 참조할 것은 cv_lane_detect.py 
4. 교육목적은 외부 모듈을 사용해 보기 
'''
import cv2
from jd_opencv_lane_detect import JdOpencvLaneDetect

# 동영상 파일 경로
video_path = "car_video.avi"

# 동영상 불러오기
cap = cv2.VideoCapture(video_path)

# 검출기 객체 
cv_detect = JdOpencvLaneDetect()

# 동영상 재생
while True:
    # 프레임 읽기
    ret, frame = cap.read()

    # 프레임이 올바르게 읽히지 않으면 종료
    if not ret:
        break

    lanes, img_lane = cv_detect.get_lane(frame)
    angle, img_angle = cv_detect.get_steering_angle(img_lane, lanes)
     

    # 프레임 표시
    cv2.imshow("동영상", img_angle)

    # 키 입력 처리
    key = cv2.waitKey(1) & 0xFF

    # 'q' 키를 누르면 종료
    if key == ord("q"):
        break

# 동영상 종료
cap.release()

# 모든 창 닫기
cv2.destroyAllWindows()
