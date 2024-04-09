#include <SFML/Graphics.hpp>
#include <vector>

class Enemy {
public:
    float x, y;
    sf::CircleShape cs;
    Enemy(float a, float b) {
        x = a;
        y = b;
        cs.setPosition(x, y);
        cs.setRadius(30);
    }
    void update(sf::RenderWindow &win) {
        y++;
        if (y > 600) {
            y = 0;
            x = rand() % 800;
        }
        cs.setPosition(x, y);
        win.draw(cs);
    }
};
std::vector<Enemy> enemies;

int main() {
    // 800x600 크기의 윈도우 생성
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 윈도우");

    // 윈도우가 열려있는 동안 계속 실행
    while (window.isOpen()) {
        // 이벤트 처리
        sf::Event event;
        while (window.pollEvent(event)) {
            // 닫기 버튼 클릭 시 종료
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        Enemy e1(rand()%800, 0);
        enemies.push_back(e1);
        // 윈도우 지우기
        window.clear();
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].update(window);
        }
        for (int i = 0; i < enemies.size(); i++) {
            //rect 적군, rect 아군 -> 충돌 체크 
        }
        
        //window.draw(e1.cs);
        // 여기에 게임 코드 추가

        // 윈도우 표시
        window.display();
    }

    return 0;
}
