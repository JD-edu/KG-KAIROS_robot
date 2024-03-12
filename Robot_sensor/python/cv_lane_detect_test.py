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

'''
1. importing necessary modules
'''
import cv2
import time 
import os 
from jd_opencv_lane_detect import JdOpencvLaneDetect

'''
2. Creating object from classes
  1) OpenCV lane detecting object from JdOpencvLaneDetect class 
'''

# OpenCV line detector object
cv_detector = JdOpencvLaneDetect()

'''
3. Creating camera object and setting resolution of camera image
cv2.VideoCapture() function create camera object.  
'''
# Camera object: reading image from camera 
cap = cv2.VideoCapture("car_video.avi")
# Setting camera resolution as 320x240
cap.set(3, 320)
cap.set(4, 240)

'''
4. Perform real driving
In this part, we perform real OpenCV lane detecting driving.
When you press 'q' key, it stp deepThinkCar.
While on driving, driving is recorded. 
'''
# real driving routine 
while True:
    time.sleep(0.1)
    ret, img_org = cap.read()
    if ret:
        # Find lane angle
        lanes, img_lane = cv_detector.get_lane(img_org)
        angle, img_angle = cv_detector.get_steering_angle(img_lane, lanes)
        if img_angle is None:
            print("can't find lane...")
            pass
        else:
            cv2.imshow('lane', img_angle)
            print(angle)
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        print("cap error")
'''
5. Finishing the driving
Releasing occupied resources
'''
cap.release()
cv2.destroyAllWindows()


