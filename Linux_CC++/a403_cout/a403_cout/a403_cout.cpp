#include <iostream>

using namespace std;

class Calc {
public:
	// 생성자
	Calc();
	void calcuation(int op); // 1: 더하기 2 빼기 3 나누기 4 곱하기 
	void setValue(int x, int y);
	static void show_x();
private:
	int x, y;
};

Calc::Calc(): x(0), y(0) {
	cout << "Calc start" << endl;
}

void Calc::setValue(int x_, int y_) {
	x = x_;
	y = y_;
}

void Calc::show_x() {
	cout << "test" << endl;
}

void Calc::calcuation(int op) {
	switch (op) {
		case 1:
			cout << x + y << endl;
			break;
		case 2:
			cout << x - y << endl;
			break;
		case 3:
			cout << x * y << endl;
			break;
		case 4:
			cout << x / y << endl;
			break;
	}		
}

int main() {
	Calc c1;
	c1.setValue(4, 5);
	c1.calcuation(1);
	Calc::show_x();
	Calc::setValue(4, 5);

}
