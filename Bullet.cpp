//тут будет реализация методов класса пуля
#include "Bullet.h"

Bullet::Bullet(sf::Image& image, float X, float Y, int W, int H, float rotation, sf::String Name, int DMG) :Entity(image, X, Y, W, H, Name)
{
	//
	sprite.setOrigin(w / 2, h / 2);
	rotationPer = rotation;
	rotationPer -= 90;
	speed = 2;

	dx = cos(rotationPer / 180 * 3.14159265) * 0.1;
	dy = sin(rotationPer / 180 * 3.14159265) * 0.085;
	// направление движения от угла
	sprite.setPosition(x + w / 2, y + w / 2);

}

void Bullet::update(float time, sf::String TileMap[HEIGHT_MAP])
{
	moveTimer += time;
	x += dx * time * speed;

	y += dy * time * speed;

	if (life)
	{
		sprite.setPosition(x + w / 2, y + h / 2);
	}
	else
	{
		return;
	}

}

sf::FloatRect Bullet::GetRect()
{
	sf::FloatRect BufRect;
	BufRect.height = h;
	BufRect.width = w;
	return BufRect;
}