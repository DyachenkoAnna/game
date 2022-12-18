#ifndef __Entity__
#define __Entity__

#include <SFML/Graphics.hpp>

class Entity {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect GetRect() {return sf::FloatRect(x,y,w,h);};
	Entity(sf::Image& image, float X, float Y, int W, int H, sf::String Name) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
	bool isAlive() { return life; }; 
protected:
	
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove;
	sf::String name;
	enum { left, right, up, down, stay, fly } state;
};

#endif