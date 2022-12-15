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
	gunrotation = atan2(-y + DXY.y, -x + DXY.x) * 180 / 3.14159265 + 90;
	
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
//дописать анимацию
//void Player::animation()

//положение пушки
//?? Player::GetgunXY()

//окрашивание цветом при уроне
//void Player::struck(int damage)

//отрисовка
//void Player::draw(sf::RenderTarget& target)
