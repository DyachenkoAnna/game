#ifndef __Entity__
#define __Entity__

#include <SFML/Graphics.hpp>

class Entity {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect GetRect() {return sf::FloatRect(x,y,w,h);};//пр€моугольник дл€ поиска пересечени€ объектов
	Entity(sf::Image& image, float X, float Y, int W, int H, sf::String Name) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;//dx и dy - на сколько мен€ть позицию
		life = true; isMove = false;
		texture.loadFromImage(image);//установка текстуры 
		sprite.setTexture(texture);//вырезка спрайта из текстуры
		sprite.setOrigin(w / 2, h / 2);//координаты в центре спрайта
	}
	bool isAlive() { return life; };//возвращает позицию спрайта
protected:
	
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove;
	sf::String name;//враги по именам
	enum { left, right, up, down, stay, fly } state; //тип пересечение - состо€ние объекта
};

#endif