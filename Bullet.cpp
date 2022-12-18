#include "Bullet.h"

Bullet::Bullet(sf::Image& image, float X, float Y, int W, int H, float rotation, sf::String Name, int DMG) :Entity(image, X, Y, W, H, Name)
{
	//
	damage = DMG;

	if (damage > 20)
	{
		sprite.setScale(0.1 * (damage / 10), 0.1 * (damage / 10));
		//размер пули зависит от damage
	}
	else
	{
		sprite.setScale(0.2, 0.2);
	}
	speed = 2;
	sprite.setTextureRect(sf::IntRect(0, 160, 49, 80));
	sprite.setRotation(rotationPer - 180);

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

int Bullet::GetDamage()
{
	life = false;//Проверка, что пуля достигла цели
	return damage;
}

sf::FloatRect Bullet::GetRect()
{
	sf::FloatRect BufRect;
	BufRect.height = h;
	BufRect.width = w;
	return BufRect;
}

void Bullet::checkCollisionWithMap(float Dx, float Dy, sf::String TileMap[HEIGHT_MAP])
{
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0' || TileMap[i][j] == 'b')
			{
				life = false;
				// Столкнулись = пуля врезалась
			}
		}
	return;
}