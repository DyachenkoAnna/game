#include "Bullet.h"

Bullet::Bullet(sf::Image& image, float X, float Y, int W, int H, float rotation, sf::String Name, int DMG) :Entity(image, X, Y, W, H, Name)
{
	damage = DMG;
	TTL = 5000;//Время жизни, ограничивает дальность полета пули
	sprite.setOrigin(w / 2, h / 2);
	rotationPer = rotation;
	rotationPer -= 90;
	if (name == "HeroBullet")
	{
		if (damage > 20)
		{
			sprite.setScale(0.1 * (damage / 10), 0.1 * (damage / 10));
			//Размер пули зависит от damage
		}
		else
		{
			sprite.setScale(0.2, 0.2);
		}
		speed = 2;
		sprite.setTextureRect(sf::IntRect(0, 160, 49, 80));
		sprite.setRotation(rotationPer - 180);
	}


	dx = cos(rotationPer / 180 * 3.14159265) * 0.1;
	dy = sin(rotationPer / 180 * 3.14159265) * 0.085;
	// направление движения от угла
	sprite.setPosition(x + w / 2, y + w / 2);

}

void Bullet::update(float time, sf::String TileMap[HEIGHT_MAP])
{
	moveTimer += time;
	x += dx * time * speed;
	checkCollisionWithMap(dx, 0, TileMap);
	y += dy * time * speed;
	checkCollisionWithMap(0, dy, TileMap);
	//Скорость регулируется отдельной переменной
	//Проверка на столкновения
	TTL -= time;
	if (TTL <= 0)
	{
		life = false;
	}
	if (life)
	{
		sprite.setPosition(x + w / 2, y + h / 2);
	}
	else
	{
		animation();
		return;
	}
	animation();

}

int Bullet::GetDamage()
{
	life = false;//Проверка, что пуля достигла цели
	return damage;
}

sf::FloatRect Bullet::GetRect()
{
	sf::FloatRect BufRect;

	BufRect.left = x - w * (cos((rotationPer + 90) / 180 * 3.14159265));
	BufRect.top = y - h * (sin((rotationPer + 90) / 180 * 3.14159265));
	//Квадрат вписали в пулю

	BufRect.height = h;
	BufRect.width = w;
	return BufRect;
}

void Bullet::animation()
{
	if (name == "HeroBullet")
	{
		if (moveTimer < 100)
		{
			sprite.setTextureRect(sf::IntRect(0, 160, 49, 80));
		}
		else if (moveTimer < 200)
		{
			sprite.setTextureRect(sf::IntRect(49, 160, 47, 80));
		}
		else if (moveTimer < 300)
		{
			sprite.setTextureRect(sf::IntRect(95, 160, 48, 80));
		}
		else if (moveTimer < 400)
		{
			sprite.setTextureRect(sf::IntRect(142, 160, 48, 80));
		}
		else if (moveTimer < 500)
		{
			sprite.setTextureRect(sf::IntRect(189, 160, 48, 80));
		}
		else if (moveTimer < 600)
		{
			sprite.setTextureRect(sf::IntRect(237, 160, 48, 80));
			moveTimer = 0;
		}
		else if (moveTimer < 700)
		{
			sprite.setTextureRect(sf::IntRect(219, 80, 48, 80));
			moveTimer = 0;
		}
		else if (moveTimer < 800)
		{
			sprite.setTextureRect(sf::IntRect(266, 80, 48, 80));

		}
		else
		{
			moveTimer = 0;
		}
	}
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