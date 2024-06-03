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
import threading 

# 타이머 쓰래드 구현 
def startTimer(iTimeSec,isRepeated):
    print("setTimer")
    timer_thread1 = threading.Timer(iTimeSec, timerCallBack,[iTimeSec,isRepeated])
    timer_thread1.daemon = True
    timer_thread1.start()

def timerCallBack(iTimeSec, isRepeated):
    global count 
    count += 1
    print(count)
    if isRepeated == True:
        timer_thread1 = threading.Timer(iTimeSec, timerCallBack,[iTimeSec,isRepeated])
        timer_thread1.daemon = True
        timer_thread1.start()
count = 0
startTimer(0.1, True)

while True:
    pass 
