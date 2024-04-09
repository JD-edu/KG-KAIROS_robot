#include <SFML/Graphics.hpp>

int main() {
    // 800x600 크기의 윈도우 생성
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 윈도우");

    sf::CircleShape cs1(100);
    cs1.setFillColor(sf::Color::Red);
    cs1.setPosition(200, 200);

    // 윈도우가 열려있는 동안 반복
    while (window.isOpen()) {
        // 이벤트 처리
        sf::Event event;
        while (window.pollEvent(event)) {
            // 닫기 버튼 클릭 시 종료
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        
        // 윈도우 지우기
        window.clear();
        window.draw(cs1);
        // 윈도우에 내용 그리기
        // ...

        // 윈도우 표시
        window.display();
    }

    return 0;
}
