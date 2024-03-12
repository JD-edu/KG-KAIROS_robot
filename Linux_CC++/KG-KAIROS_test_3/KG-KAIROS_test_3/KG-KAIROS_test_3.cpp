#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
using namespace sf;

class Enemy {
public:
    int x;
    int y;
    float rad;
    CircleShape cs;
    Enemy(float radian);
    void update();
    void draw(RenderWindow& win);
private:
};

Enemy::Enemy(float radian)
{
    rad = radian;
    x = rand() % 640;
    y = 0;
    cs.setRadius(rad);
    cs.setFillColor(Color::Red);
    cs.setPosition(x, y);
}
void Enemy::update() {
    y++;
    cs.setPosition(x, y);
}
void Enemy::draw(RenderWindow& win) {
    win.draw(cs);
}

class EnemyBoss : public Enemy {
    EnemyBoss(float radian):Enemy(radian) {

    }
};

std::vector<Enemy> enemies;
int main()
{
    EnemyBoss eb(30);
    RenderWindow window(VideoMode(640, 480), "this is test");
    int coolDown = 0;
    while (window.isOpen())
    {
        coolDown++;
        if (coolDown > 240) {
            Enemy en(30);
            enemies.push_back(en);
            coolDown = 0;
        }
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
    
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].update();
        }
        window.clear(Color::Black);
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].draw(window);
        }
        window.display();
    }
}
