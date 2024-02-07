#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(640, 480), "this is test");
    CircleShape enemy(20.f);
    enemy.setFillColor(Color::Red);
    enemy.setPosition(Vector2f(320.f, 0.f));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        enemy.move(0, 1);

        window.clear(Color::Black);
        window.draw(enemy);
        window.display();
    }
}