#include "Player.h"
#include "Constants.h"

// Конструктор
Player::Player(sf::Image &image, float X, float Y,int W,int H, sf::String Name):Entity(image,X,Y,W,H,Name)
{
	score = 0;
	struckTimer = 0;
    state = up;
	frame.setTexture(texture);
	wheelL.setTexture(texture);
	wheelR.setTexture(texture);
	gun.setTexture(texture);

	wheelL.setScale(0.9, 1);
	wheelR.setScale(0.9, 1);
	frame.setScale(0.9, 0.9);
	gun.setScale(0.9, 0.9);
	//размеры
	wheelL.setTextureRect(sf::IntRect(1, 80, 19, 77));
	wheelL.setOrigin(w / 2 + 10, h / 2);

	wheelR.setTextureRect(sf::IntRect(20, 81, 19, 77));
	wheelR.setOrigin(- w / 2 +10, h / 2);

	frame.setTextureRect(sf::IntRect(84,80,70,80));
	frame.setOrigin(w / 2, h / 2);
	
	gun.setTextureRect(sf::IntRect(181, 81, 36, 78));
	gun.setOrigin(18, 58);
	//позиция-центр спрайтов
	frame.setPosition(x, y);
	wheelL.setPosition(x, y);
	wheelR.setPosition(x, y);
	gun.setPosition(x, y);
	gunrotation = 0;
}

 //Для определения движения
int Player::control(sf::Event event)
{
	state = stay;
	sf::Vector2i DXY = sf::Mouse::getPosition();
	//sf::Vector2i DXY = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
	
	//fix release 1.0 ++
	//gunrotation = atan2(-y + DXY.y, -x + DXY.x) * 180 / 3.14159265 + 90;
	gunrotation = atan2(-y + DXY.y - 40, -x + DXY.x - 35) * 180 / 3.14159265 + 90;
	//fix release 1.0 --

	if (sf::Keyboard::isKeyPressed) {//если нажата клавиша
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			state = left; speed = 0.1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			state = right; speed = 0.1;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
			state = up; speed = 0.085;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			state = down; speed = 0.085;
		}
	}
	
	return 0;
}

int Player::checkCollisionWithMap(float Dx, float Dy, sf::String TileMap[HEIGHT_MAP])
{
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0' || TileMap[i][j] == 'b')
			{
				if (Dy > 0) { y = i * 32 - h;  dy = 0; }//столкновение с нижним краем карты
				if (Dy < 0) { y = i * 32 + 32;  dy = 0; }//с верхним краем карты
				if (Dx > 0) { x = j * 32 - w; }//с правым краем карты
				if (Dx < 0) { x = j * 32 + 32; }// с левым краем карты
			}
			if (TileMap[i][j] == 'h' && state == stay && moveTimer > 1000)
			{
				health += 10;
				//Если встали и стоим на хил поинте, то прибавляем здоровье
				moveTimer = 500;
				if (health > 500)
				{
					health = 500;
				}
			}
		}
	
	return 0;
}

//Анимация
void Player::animation()
{
	if (state != stay)
	{
		if (moveTimer < 100)
		{
			wheelL.setTextureRect(sf::IntRect(1, 80, 19, 77));
			wheelR.setTextureRect(sf::IntRect(20, 81, 19, 77));
		}
		else if (moveTimer < 200)
		{
			wheelL.setTextureRect(sf::IntRect(40, 82, 19, 77));
			wheelR.setTextureRect(sf::IntRect(59, 82, 19, 77));
		}
		else
		{
			moveTimer = 0;
		}
		//Движение колес
	}
	gun.setRotation(gunrotation);
	switch (state)
	{
	case Entity::left:
		frame.setRotation(-90);
		wheelL.setRotation(-90);
		wheelR.setRotation(-90);
		break;
	case Entity::right:
		frame.setRotation(90);
		wheelL.setRotation(90);
		wheelR.setRotation(90);
		break;
	case Entity::up:
		frame.setRotation(0);
		wheelL.setRotation(0);
		wheelR.setRotation(0);
		break;
	case Entity::down:
		frame.setRotation(180);
		wheelL.setRotation(180);
		wheelR.setRotation(180);
		break;
	default:
		break;
	}
	//повернули спрайты по направлению движения
	if (struckTimer > 0)
	{
		gun.setColor(sf::Color::Red);
		frame.setColor(sf::Color::Red);
		wheelL.setColor(sf::Color::Red);
		wheelR.setColor(sf::Color::Red);
	}
	else
	{
		gun.setColor(sf::Color::White);
		frame.setColor(sf::Color::White);
		wheelL.setColor(sf::Color::White);
		wheelR.setColor(sf::Color::White);
	}//Красим при уроне
	return;
}

//Движение главного игрока
int Player::update(float time, sf::String TileMap[HEIGHT_MAP], sf::Event event)
{
	if (!life)
	{
		return 0;
	}
	if (struckTimer > 0)
	{
		struckTimer -= time;
	}
	moveTimer += time;
	control(event);
	animation();
	switch (state)//тут делаются различные действия в зависимости от состояния
	{
	case right: dx = speed; dy = 0; break;//состояние идти вправо
	case left: dx = -speed; dy = 0; break;//состояние идти влево
	case up: dx = 0; dy = -speed; break;// состояние поднятия наверх 
	case down: dx = 0; dy = speed; break;// состояние во время спуска  
	case stay: dx = 0; dy = 0; break;//стоим		
	}
	x += dx * time;
	checkCollisionWithMap(dx, 0, TileMap);//обрабатываем столкновение по Х
	y += dy * time;
	checkCollisionWithMap(0, dy, TileMap);//обрабатываем столкновение по Y
	frame.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта 
	wheelL.setPosition(x + w / 2, y + h / 2);
	wheelR.setPosition(x + w / 2, y + h / 2);
	gun.setPosition(x + w / 2, y + h / 2);
	if (health <= 0) { life = false; }
	speed = 0;
	return 0;
}

//fix release 1.0 ++
//переработка углов, изменение условий под них
//Положение пушки
sf::Vector2f Player::GetgunXY()
{
	sf::Vector2f buf = gun.getPosition();
	//std::cout << "угол: " << gunrotation << std::endl;
	if (gunrotation >= -45 && gunrotation < 45)
	{
	    //верхний угол
		buf.x += 80 * cos((gunrotation - 90) / 180 * 3.14159265) + (70/4);
		buf.y += 80 * sin((gunrotation - 90) / 180 * 3.14159265) - (80/4);
	}
	else if (gunrotation >= 45 && gunrotation < 135)
	{
	    //правый
		buf.x += 80 * cos((gunrotation - 90) / 180 * 3.14159265) - (80/4);
		buf.y += 80 * sin((gunrotation - 90) / 180 * 3.14159265) + (80/4);
	}
	else if (gunrotation >= 135 && gunrotation < 225)
	{
        //нижний
		buf.x += 80 * cos((gunrotation - 90) / 180 * 3.14159265) - (80/2);
		buf.y += 80 * sin((gunrotation - 90) / 180 * 3.14159265) - (70/4);
	}
	else if ((gunrotation >= 225 && gunrotation <= 270)||(gunrotation >= -90 && gunrotation < -45))
	{
        //левый
		buf.x += 80 * cos((gunrotation - 90) / 180 * 3.14159265);
		buf.y += 80 * sin((gunrotation - 90) / 180 * 3.14159265) - (80/2);
	}

	return buf;
}
//fix release 1.0 --


//Окрашивание при нанесении урона
void Player::struck(int damage)
{
	health -= damage;
	struckTimer = 200;//на 200мс в красный цвет
}

//отрисовка
void Player::draw(sf::RenderTarget& target)
{
	target.draw(wheelL);
	target.draw(wheelR);
	target.draw(frame);
	target.draw(gun);
}
