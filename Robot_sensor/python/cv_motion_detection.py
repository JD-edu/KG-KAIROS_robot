import cv2
import numpy as np
import time 

# 카메라 열기
cap = cv2.VideoCapture(0)

# 움직임 감지 알고리즘
def motion_detection(frame_prev, frame_cur):
    try:
        # 이전 프레임과 현재 프레임의 차이를 계산합니다.
        diff = cv2.absdiff(frame_prev, frame_cur)

        # 차이가 일정 수준 이상이면 움직임이 감지된 것으로 간주합니다.
        threshold = 100
        ret, thresh = cv2.threshold(diff, threshold, 255, cv2.THRESH_BINARY)

        # 움직임 영역을 찾습니다.
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # 움직임 영역이 있으면 출력합니다.
        if len(contours) > 0:
            print("움직임 감지됨")
            cv2.drawContours(frame_cur, contours, -1, (0, 255, 0), 2)
    except:
        pass

# 프레임 읽기
ret, frame = cap.read()
time.sleep(0.1)
frame_prev = frame.copy()

while True:
    # 현재 프레임을 읽습니다.
    ret, frame = cap.read()

   
    # 두 이미지 간의 차이 계산
    #diff = cv2.absdiff(frame, frame_prev) 
    
    

    # 결과 이미지 출력
    #cv2.imshow("Difference", diff)

    # 움직임 감지
    motion_detection(frame_prev, frame)
    
    # 이전 프레임을 저장합니다.
    frame_prev = frame.copy()

    # 화면에 출력합니다.
    cv2.imshow("frame", frame)

    # 키보드 입력을 확인합니다.
    key = cv2.waitKey(1)
    if key == 27:
        break

# 카메라 닫기
cap.release()
cv2.destroyAllWindows()