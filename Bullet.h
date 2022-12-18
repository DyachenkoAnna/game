#pragma once
//тут будет описание класса пуль
#pragma once
#include  "Entity.h";
#include  "Constants.h"
class : public Entity
{
public:
	Bullet(sf::Image& image, float X, float Y, int W, int H, float rotation, sf::String Name, int);
	void update(float time, sf::String TileMap[HEIGHT_MAP]);
	sf::FloatRect GetRect();

private:
	float rotationPer;// ѕоворот пули
};
