#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::VideoMode vd(800, 600);
    std::string uga = "SFML 기본 윈도우";
    sf::RenderWindow window(vd, uga);

    // 윈도우가 열려있는 동안 루프를 반복합니다.
    // 빨간색 공을 만듭니다.
    sf::CircleShape circle(50.f);
    sf::Color cr(255, 255, 0, 127);
    circle.setFillColor(cr);
    // sf::Color::Red
    // 공의 초기 위치를 설정합니다.
    sf::Vector2f vf(100, 100);
    circle.setPosition(vf);

    // 화면 아래쪽에 사각형을 만듭니다.
    sf::RectangleShape rectangle(sf::Vector2f(100.f, 50.f));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(sf::Vector2f(100.f, 500.f));
    float x = rectangle.getPosition().x;

    
    while (window.isOpen()) {
        // 이벤트 처리
        sf::Event event;
        while (window.pollEvent(event)) {
            // 닫기 버튼을 클릭하면 윈도우를 닫습니다.
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // 화살표 좌우키 입력 처리
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    rectangle.move(-5.f, 0.f);
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    rectangle.move(5.f, 0.f);
                }
            }
        }

        // 충돌 감지
        //if (circle.getGlobalBounds().intersects(rectangle.getGlobalBounds())) {
        //    std::cout << "collide" << std::endl;
        //}

        sf::FloatRect r1 = circle.getGlobalBounds();
        sf::FloatRect r2 = rectangle.getGlobalBounds();
        bool result = r2.intersects(r1);
        std::cout << result << std::endl;


        // 윈도우를 지웁니다.
        window.clear();

        circle.move(0.f, 1.f);
        // 공을 그립니다.
        window.draw(circle);

        // 사각형을 그립니다.
        window.draw(rectangle);

        // 윈도우를 표시합니다.
        window.display();
    }

    return 0;
}
