#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include<vector>
#include<cstdlib>

using namespace sf;

class Missle {
public:
	CircleShape missle;
	Missle(int x, int y, int rad) {
		missle.setRadius(rad);
		missle.setFillColor(Color::Blue);
		missle.setPosition(x, y);
	}

	void missle_draw(RenderWindow& wind) {
		wind.draw(missle);
	}
private:
	int x;
	int y;
};

class MissleHeavy :public Missle {
public:
	int life = 2;
	MissleHeavy() 
	{

	}

	bool isDead() {
		if (life <= 0)
			return true;
		else
			return false;
	}

};



int main()
{
	VideoMode vd(640, 480);
	RenderWindow window(vd, "Conner Jeong");

	window.setFramerateLimit(60);

	// 아군 우주선 
	Vector2f vf(100.f, 100.f);
	RectangleShape player(vf);
	player.setFillColor(Color::Green);
	int x = 100;
	int y = 100;
	player.setPosition(x, y);

	int enemyCool = 0;

	// 적군 
	//CircleShape enemy(20.f);
	//enemy.setFillColor(Color::Red);
	//enemy.setPosition(Vector2f(200.f, 200.f));
	Texture enemyTex;
	Sprite enemySprite;
	enemyTex.loadFromFile("./Textures/enemy.png");
	enemySprite.setTexture(enemyTex);
	enemySprite.setPosition(100, 100);
	enemySprite.setScale(Vector2f(0.2f, 0.2f));
	enemySprite.setRotation(-90);

	std::vector<Missle> mss;
	std::vector<Sprite> enemies;

	MissleHeavy mh(100, 100, 30);

	while (window.isOpen())
	{
		srand(time(NULL));
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left)) && (x > 0)) {
			x -= 5;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Right)) && (x < 540)) {
			x += 5;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (y > 0)) {
			y -= 5;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Down)) && (y < 380)) {
			y += 5;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			//CircleShape missle(10.f);
			//missle.setFillColor(Color::Blue);
			//missle.setPosition(x, y);
			Missle ms(x, y, 5);
			mss.push_back(ms);
			std::cout << mss.size() << std::endl;

		}

		// 적군 랜덤 생성 
		enemyCool++;
		if (enemyCool > 50) {
			enemySprite.setPosition(rand() % 640, 0);
			enemies.push_back(enemySprite);
			enemyCool = 0;
		}
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].move(0, 5.f);
		}

		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].getPosition().y < 0) {
				enemies.erase(enemies.begin() + i);
			}
		}

		for (int i = 0; i < mss.size(); i++) {
			mss[i].missle.move(0, -5.f);
		}

		for (int i = 0; i < mss.size(); i++) {
			if (mss[i].missle.getPosition().y < 0) {
				mss.erase(mss.begin() + i);
			}
		}

		player.setPosition(x, y);

		window.clear(Color::Black);
		window.draw(player);

		for (int i = 0; i < mss.size(); i++) {
			//window.draw(mss[i].missle);
			mss[i].missle_draw(window);
		}

		for (int i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i]);
		}

		//window.draw(enemySprite);
		window.display();
	}
}