#include "Enemy.h";
//#include <iostream> //была для отладки

Enemy::Enemy(sf::Image& image, float X, float Y, int W, int H, sf::String Name, sf::String TileMapEnemy[HEIGHT_MAP]) :Entity(image, X, Y, W, H, Name)
{
	speed = 0.1; //при 0,5, оказывается, тоже очень быстро, лучше много медленных врагов)
	BOSSdamagetimer = 0;
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
		health = 500; //500 хп боссу
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
}

int Enemy::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
			{
				isMove = false;
				SetDirection();
			}
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


int Enemy::SetAim(sf::Vector2f XY)
{
	if (!isMove) {
		if (name == "flybot")
		{
			XYAim = XY; // а флайботы - камикадзе :)
		}
		else if (name == "BOSSbot")
		{
			XYAim = SpaunTarget();
			//Пункт назначения - спаун
		}
	}
	return 0;
}


int Enemy::animation()
{
	if (name == "flybot")
	{	
		//fix release 1.0 ++
		//healthSprite.setTextureRect(sf::IntRect(0, 0, 9 + health / 4, 8));//health ('max = 100') / 4 = 25
		if (status != "anikilled")
		{
			healthSprite.setTextureRect(sf::IntRect(0, 0, 9 + health / 4, 8));//health ('max = 100') / 4 = 25
		}
		//fix release 1.0 --
		if (status == "anikilled")
		{	
			//fix release 1.0 ++
			healthSprite.setTextureRect(sf::IntRect(0, 0, 0, 0)); //убираем полоску здоровья совсем, если бот начинает умирать
			//fix release 1.0 --

			if (moveTimer < 100)
			{
				sprite.setTextureRect(sf::IntRect(240, 1, 80, 80));
			}
			else if (moveTimer < 200)
			{
				sprite.setColor(sf::Color::Red);
			}
			else
			{
				status = "killed";
			}
		}
		else if (moveTimer < 200)
		{
			sprite.setTextureRect(sf::IntRect(12, 6, 57, 68));
		}
		else if (moveTimer < 400)
		{
			sprite.setTextureRect(sf::IntRect(172, 5, 56, 69));
		}
		else if (moveTimer < 600)
		{
			sprite.setTextureRect(sf::IntRect(92, 5, 58, 72));
		}
		else if (moveTimer < 800)
		{
			sprite.setTextureRect(sf::IntRect(172, 5, 56, 69));
		}
		else
		{
			moveTimer = 0;
		}
	}
	else if (name == "BOSSbot")
	{
		healthSprite.setTextureRect(sf::IntRect(2, 252, 24 + health / 3.5, 25));	//хп ('max = 500') / 3,5 = 142
		if (status == "anikilled")
		{

			if (moveTimer < 200)
			{
				sprite.setTextureRect(sf::IntRect(240, 1, 80, 80));
				sprite.setScale(4, 4);
			}
			else if (moveTimer < 300)
			{
				sprite.setColor(sf::Color::Red);
				BossPart.setColor(sf::Color::Red);
			}
			else if (moveTimer < 400)
			{
				sprite.setColor(sf::Color::Yellow);
				BossPart.setColor(sf::Color::Black);
			}
			else if (moveTimer < 500)
			{
				status = "killed";
			}
			//there is coming a big bang
		}
		else if (moveTimer < 2000)
		{
			sprite.rotate(0.5);
		}
		else if (moveTimer < 4000)
		{
			sprite.rotate(-0.5);
		}
		else
		{
			moveTimer = 0;
		}
	}
	return 0;
}


int Enemy::update(float time)
{	
	if (!life)
	{
		return 0;
		//мертв. сов7
	}
	if (speed < 1)
	{
		speed += 0.001;// Наращиваем скорость, чтоб сразу после спауна не врезаться
	}

	moveTimer += time;
	BOSSdamagetimer += time;
	animation();
	action(time);
	if (status == "killed")
	{
		life = false;
	}
	else if (health <= 0 && status != "anikilled") {
		status = "anikilled";
		state = stay;
		moveTimer = 0;
		if (name == "BOSSbot")
		{
			sprite.setOrigin(40, 50);
			sprite.setRotation(0);
			//Далее меняем спрайт. для плавности
		}
	}
	return 0;
}


void Enemy::SetDirection()
{
	float rotation = (atan2(XYAim.y - y, XYAim.x - x)); // вращение по радианам
	dx = cos(rotation) * 0.1;// 
	dy = sin(rotation) * 0.08;//Изза разницы размеров по x & y умножаем соответсвенно
}


//Для определения действия врага
int Enemy::action(float time)
{
	if (!isMove)
	{
		isMove = true;
		SetDirection();	//Если не двигаемся, то начинаем
						//а то че стоять тут
	}
	else
	{
		if (state == stay)
		{
			return 0;
			//стоим
		}
		x += dx * time * speed;
		checkCollisionWithMap(dx, 0);
		y += dy * time * speed;
		checkCollisionWithMap(0, dy);
		//подвинули и проверили на столкновение
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта
		if (name == "BOSSbot")
		{
			BossPart.setPosition(x + w / 2 - 5, y + h / 2 - 10);
			healthSprite.setPosition(x, y - 20);
		}

		else if (name == "flybot")
		{
			healthSprite.setPosition(x + 10, y - 10);
		}

		if (abs(XYAim.x - x) < w && abs(XYAim.y - y) < h)
		{
			isMove = false;
			dx = 0;
			dy = 0;
			//Достигли точки назначения. Пора искать новую цель.
		}
	}
	return 0;
}


void Enemy::struck(int damage)
{
	health -= damage;
}
