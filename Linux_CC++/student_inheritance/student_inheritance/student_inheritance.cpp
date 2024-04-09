#include <iostream>  // python import 

// class 
class Point {
    int x, y;
public:
    void set(int a, int b) {
        x = a, y = b;
    }
    void showPoint() {
        std::cout << x << "  " << y << std::endl;
    }
    void uga() {
        std::cout << "uga" << std::endl;
    }
};

class ColorPoint : public Point { // 2차원 평면에서 컬러 점을 표현하는 클래스 ColorPoint. Point를 상속받음
    std::string color;// 점의 색 표현
public:
    void setColor(std::string color) { this->color = color; }
    void showColorPoint();
    void uga() {
        std::cout << "siva" << std::endl;
        std::cout << "joto" << std::endl;
    }
};

void ColorPoint::showColorPoint() {
    std::cout << color << ":";
    showPoint(); // Point의 showPoint() 호출
}


int main()
{
    Point p1;
    ColorPoint p2;
    p1.set(100, 100);
    p1.showPoint();
    p2.set(200, 200);
    p2.showPoint();
    p2.setColor("희끼무리");
    p2.showColorPoint();
    p2.uga();
    p1.uga();
}
