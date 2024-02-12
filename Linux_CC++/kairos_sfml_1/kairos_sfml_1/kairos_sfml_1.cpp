#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
using namespace sf;

class Enemy {
public:
    int x;
    int y;
    CircleShape cs;
    Enemy(float x, float y);
    void update();

private:

};

Enemy::Enemy(float x_, float y_)
{
    x = x_;
    y = y_;
    cs.setRadius(20);
    cs.setPosition(x, y);
    cs.setFillColor(Color::Blue);
}

class EnemyBoss: public Enemy {
public:
    EnemyBoss(float x, float y) : Enemy(x, y) {};
    int life = 3;
    int getLife();
    int reduceLife();
    void setBossSize();
};

int EnemyBoss::getLife()
{
    return life;
}

int EnemyBoss::reduceLife() {
    life--;
    if (life < 0) {
        return -1;
    }
    else {
        return 1;
    }
}

void EnemyBoss::setBossSize() {
    cs.setRadius(40);
    cs.setFillColor(Color::Yellow);
}

void Enemy::update()
{
    y += 1;
    if (y > 480) {
        x = rand() % 640;
        y = 0;
    }
    cs.setPosition(x, y);     
}
int main()
{
    RenderWindow window(VideoMode(640, 480), "this is test");
    window.setFramerateLimit(60);
    CircleShape cr(30);
    float cy = 0;
    cr.setPosition(100, cy);
    cr.setFillColor(Color::Red);
    Vector2f vf(30, 30);
    RectangleShape rc(vf);
    float rx = 320;
    rc.setPosition(rx, 400);

    Enemy en(100, 0);
    EnemyBoss eb(100, 0);
    eb.setBossSize();
    
    /*Texture tx;
    Sprite sp;
    tx.loadFromFile("./Textures/enemy.png");
    sp.setTexture(tx);
    sp.setScale(0.1, 0.1);
    sp.setPosition(200, 200);
    std::vector<Sprite> cps;*/
    while (window.isOpen())
    {
        Event event;
        //sp.setPosition(rand() % 640, rand() % 480);
        //cps.push_back(sp);
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        //Color cr(0, 0, 0);
        //window.clear(cr);
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            rx++;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            rx--;
        }

        cy++;
        if (cy > 480)
            cy = 0;
        cr.setPosition(100, cy);
        rc.setPosition(rx, 400);
        FloatRect t1 = cr.getGlobalBounds();
        FloatRect t2 = rc.getGlobalBounds();
        if (t1.intersects(t2)) {
            std::cout << "collide" << std::endl;
        }
        en.update();
        eb.update();
        window.clear(Color::Black);
        window.draw(cr);
        window.draw(rc);
        window.draw(en.cs);
        window.draw(eb.cs);
        //for(int i=0;i<cps.size();i++)
        //    window.draw(cps[i]);
        window.display();

    }
}