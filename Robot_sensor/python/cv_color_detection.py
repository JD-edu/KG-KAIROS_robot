'''
MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.
'''
import cv2
import numpy as np

# 웹캠을 엽니다.
cap = cv2.VideoCapture(0)

while True:
    # 프레임을 읽어옵니다.
    ret, frame = cap.read()

    # BGR 색상 공간을 HSV로 변환합니다.
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 빨간색의 범위를 정의합니다.
    lower_red = np.array([0, 100, 100])
    upper_red = np.array([40, 255, 255])

    # 정의한 범위 내의 픽셀을 찾습니다.
    red_mask = cv2.inRange(hsv_frame, lower_red, upper_red)

    # 빨간색 픽셀에 해당하는 부분만 추출합니다.
    red_objects = cv2.bitwise_and(frame, frame, mask=red_mask)

    # 결과 프레임을 출력합니다.
    cv2.imshow('Red Objects Tracking', red_objects)
    cv2.imshow('mask', red_mask)
    cv2.imshow('hsv', hsv_frame)

    # 'q' 키를 누르면 루프를 종료합니다.
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 웹캠을 해제하고 창을 닫습니다.
cap.release()
cv2.destroyAllWindows()
