
#include <iostream>

class Rectangle {
public:
	Rectangle();
	int getArea();
	int getWidth();
private:
	int width, height;
};

Rectangle::Rectangle() {

}

int Rectangle::getArea() {
	return width * height;
}

int Rectangle::getWidth() {
	return width;
}


int main() {
	Rectangle rt;
	int w = rt.getWidth();
	std::cout << rt.getArea() << std::endl;
}