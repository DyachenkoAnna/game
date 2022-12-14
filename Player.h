#ifndef __Player_h__
#define __Player_h__

#include "Entity.h"
#include "Constants.h"
/*
Класс игрок. Главный герой

Переменные от родителя:
float dx, dy, x, y, speed, moveTimer;
int w, h, health;
bool life, isMove;
sf::Texture texture;
sf::Sprite sprite;
sf::String name;
*/

class Player :protected Entity {
public:
	Player(sf::Image& image, float X, float Y, int W, int H, sf::String Name);
	bool isAlive() { return life; };
	sf::FloatRect GetRect() { return sf::FloatRect(x+5, y+5, w-5, h-5); };
	float GetRotation() { return gunrotation; };//берем направление пушки
	int Getscore() { return score; };
	void Addscore(int SCR) { score += SCR; };
	int Gethealth() { return health; };
	//?? GetXY() {  }; // возвращение позиции спрайта героя
	//?? GetgunXY();// возвращение позиции конца пушки
	//void struck(int damage);
	//void draw(sf::RenderTarget& target);
private:
	// Будет вызываться внутри
	int control(sf::Event event);
	int checkCollisionWithMap(float, float, sf::String TileMap[HEIGHT_MAP]);//Проверка столкновений с картой
	sf::Sprite wheelR;//правые колеса
	sf::Sprite wheelL;//левые
	sf::Sprite gun;//пушка
	sf::Sprite frame;//рамка
	float gunrotation;
	int score;
	float struckTimer;//для анимации нанесения урона
	//void animation();
};

#endif