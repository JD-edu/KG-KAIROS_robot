#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(800, 600), "this is test");

    Texture enemy_tx;
    Sprite enemy_sp;
    enemy_tx.loadFromFile("./Textures/enemy.png");
    enemy_sp.setTexture(enemy_tx);
    enemy_sp.setScale(0.1, 0.1);

    std::vector<Sprite> enemies;
  
    while (window.isOpen())
    {
        enemy_sp.setPosition(rand()%800, rand()%600);
        enemies.push_back(enemy_sp);
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        for (int i = 0; i < enemies.size(); i++)
            window.draw(enemies[i]);
        window.draw(enemy_sp);
        window.display();
    }
}
