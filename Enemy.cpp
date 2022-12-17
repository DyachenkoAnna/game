#include "Enemy.h";
#include <iostream>

Enemy::Enemy(sf::Image& image, float X, float Y, int W, int H, sf::String Name, sf::String TileMapEnemy[HEIGHT_MAP]) :Entity(image, X, Y, W, H, Name)
{
	speed = 1;
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		TileMap[i] = TileMapEnemy[i];
	}//Скопировали карту
	isMove = false;
	status = "WTFBOT";
	state = fly;
	sf::Vector2f XY = SpaunTarget();// находим начальные координаты
	x = XY.x;
	y = XY.y;
	healthSprite.setTexture(texture);
	if (name == "flybot")
	{
		sprite.setTextureRect(sf::IntRect(12, 5, 57, 68)); //w = 45; h = 63
		//Подрезали спрайт
		healthSprite.setTextureRect(sf::IntRect(0, 0, 34, 8));
		//Подрезали спрайт
		healthSprite.setPosition(XY.x + 10, XY.y - 10);
		//Поставили в точку
	}
	else if (name == "BOSSbot")
	{	
		//w = 160; h = 60
		health = 100;
		BossPart.setTexture(texture);
		BossPart.setTextureRect(sf::IntRect(754, 216, 145, 128));
		sprite.setTextureRect(sf::IntRect(320, 0, 325, 292));

		healthSprite.setTextureRect(sf::IntRect(2, 252, 167, 25));
		healthSprite.setScale(0.5, 0.5);
		BossPart.setScale(0.5, 0.5);
		sprite.setScale(0.5, 0.5);// Уменьшили картинку в 2 раза
		BossPart.setOrigin(64, 72);
		sprite.setOrigin(162, 146);// Нашли центр методом научного тыка и поставили спрайту
		BossPart.setPosition(XY.x + W / 2 - 5, XY.y + H / 2 - 10);
	}
	sprite.setPosition(XY.x + W / 2, XY.y + H / 2);
	std::cout << "Object has been created.\n";
}

int Enemy::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
				isMove = false;
		}
	return 0;
}

void Enemy::draw(sf::RenderTarget& target)
{
	target.draw(sprite);
	if (name == "BOSSbot")
	{
		target.draw(BossPart);
	}
	target.draw(healthSprite);
}

sf::Vector2f Enemy::SpaunTarget()
{
	int countOfSpauns = 0;
	float Sy = 100;
	float Sx = 100;
	for (int i = 0; i < HEIGHT_MAP; i++)//проходимся по элементам карты
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == 's')//если элемент наш тайлик земли, то
			{
				countOfSpauns++;// Посмотрели сколько там спаунов
			}
		}
	if (countOfSpauns != 0)
	{
		//Sx = 150;
		//Sy = 150;
		int** SpaunsCoordinate = new int* [countOfSpauns];
		for (int i = 0; i < countOfSpauns; ++i)
		{
			SpaunsCoordinate[i] = new int[2];
		}
		int randSpaun = rand() % countOfSpauns;
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == 's')
				{
					countOfSpauns--;
					SpaunsCoordinate[countOfSpauns][0] = i;
					SpaunsCoordinate[countOfSpauns][1] = j;
					//Выбрали случайный спаун
				}
			}
		Sy = SpaunsCoordinate[randSpaun][0] * 32;// 32(х32). Именно такая площадь у одной координаты
		Sx = SpaunsCoordinate[randSpaun][1] * 32;
	}
	return sf::Vector2f(Sx, Sy);
}


sf::FloatRect Enemy::GetRect()
{
	sf::FloatRect BufRect;
	if (name == "BOSSbot")
	{
		BufRect.left = x;
		BufRect.top = y;
		BufRect.width = w;
		BufRect.height = h;
	}
	if (name == "flybot")
	{
		BufRect.left = x + 5;
		BufRect.top = y + 5;
		BufRect.width = w - 5;
		BufRect.height = h - h / 4;
	}
	return BufRect;
}

void Enemy::struck(int damage)
{
	health -= damage;
}