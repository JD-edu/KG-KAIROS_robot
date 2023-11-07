import cv2

# 얼굴 감지용 Haar Cascade 분류기 로드
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# 카메라 열기 (0은 기본 카메라를 의미)
cap = cv2.VideoCapture(0)

while True:
    # 카메라에서 프레임 읽기
    ret, frame = cap.read()

    try:
        # 흑백 이미지로 변환
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # 얼굴 찾기
        faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

        # 찾은 얼굴에 사각형 그리기
        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
    except:
        pass

    # 화면에 프레임 표시
    cv2.imshow('Face Detection', frame)

    # 'q' 키를 누르면 루프 종료
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 카메라 해제 및 창 닫기
cap.release()
cv2.destroyAllWindows()