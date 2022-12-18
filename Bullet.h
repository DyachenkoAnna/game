#pragma once
#include  "Entity.h";
#include  "Constants.h"
class : public Entity
{
public:
	Bullet(sf::Image& image, float X, float Y, int W, int H, float rotation, sf::String Name, int);
	void update(float time, sf::String TileMap[HEIGHT_MAP]);
	int GetDamage();
	sf::FloatRect GetRect();
private:
	int damage;
	float rotationPer;// Поворот пули
	void checkCollisionWithMap(float Dx, float Dy, sf::String TileMap[HEIGHT_MAP]);
};
