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
