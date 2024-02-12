#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
using namespace sf;
int main()
{
    VideoMode vd(640, 480);
    RenderWindow window(vd, "KG-KAIROS");
    // 프레임 속도 제한 설정
    window.setFramerateLimit(60);
    // object setting 
    CircleShape cs(20);
    Color cr(255, 0, 0);
    
    //cs.setFillColor(cr);
    float cy = 0;
    cs.setFillColor(Color::Blue);
    Vector2f uga(100, cy);
    cs.setPosition(uga);
    

    RectangleShape rs(uga);
    float rx = 320;
    rs.setSize(Vector2f(30, 30));
    rs.setPosition(rx, 400);
    rs.setFillColor(Color::Cyan);

    std::vector<int> nums;
    
    int count = 0;
    while (window.isOpen())
    {
        nums.push_back(count++);
        std::cout << nums.size() << std::endl;
        // event processing 
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            // Left arrow key 
            rx += 5;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            // Left arrow key 
            rx -= 5;
        }
        // object moving 
        cy += 5;
        cs.setPosition(0, cy);
        if (cy > 480) {
           cy = 0;  
        }
        rs.setPosition(rx, 400);
        // collision 
        //FloatRect t1; // Rect<float>
        //FloatRect t2;
        //t1 = cs.getGlobalBounds();
        //
// t2 = rs.getGlobalBounds();
        if (rs.getGlobalBounds().intersects(cs.getGlobalBounds())) {
            std::cout << "collision" << std::endl;
        }
        // draw 
        window.clear(Color::Black);
        window.draw(cs);
        window.draw(rs);
        window.display();

    }
}