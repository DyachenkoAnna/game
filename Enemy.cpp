#include "Enemy.h";
#include <iostream>

Enemy::Enemy(sf::Image& image, float X, float Y, int W, int H, sf::String Name, sf::String TileMapEnemy[HEIGHT_MAP]) :Entity(image, X, Y, W, H, Name)
{
	speed = 1;
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		TileMap[i] = TileMapEnemy[i];
	}//����������� �����
	isMove = false;
	status = "WTFBOT";
	state = fly;
	sf::Vector2f XY = SpaunTarget();// ������� ��������� ����������
	x = XY.x;
	y = XY.y;
	healthSprite.setTexture(texture);
	if (name == "flybot")
	{
		sprite.setTextureRect(sf::IntRect(12, 5, 57, 68)); //w = 45; h = 63
		//��������� ������
		healthSprite.setTextureRect(sf::IntRect(0, 0, 34, 8));
		//��������� ������
		healthSprite.setPosition(XY.x + 10, XY.y - 10);
		//��������� � �����
	}
	else if (name == "BOSSbot")
	{
		//��� ��� �����
	}
	sprite.setPosition(XY.x + W / 2, XY.y + H / 2);
	std::cout << "Object has been created.\n";
}



void Enemy::draw(sf::RenderTarget& target)
{
	target.draw(sprite);
	if (name == "BOSSbot")
	{
		target.draw(BossPart);
	}
}



sf::Vector2f Enemy::SpaunTarget()
{
	int countOfSpauns = 0;
	float Sy = 100;
	float Sx = 100;
	for (int i = 0; i < HEIGHT_MAP; i++)//���������� �� ��������� �����
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == 's')//���� ������� ��� ������ �����, ��
			{
				countOfSpauns++;// ���������� ������� ��� �������
			}
		}
	if (countOfSpauns != 0)
	{
		Sx = 150;
		Sy = 150;
	}
	return sf::Vector2f(Sx, Sy);
}


sf::FloatRect Enemy::GetRect()
{
	sf::FloatRect BufRect;
		
	BufRect.left = x;
	BufRect.top = y;
	BufRect.width = w;
	BufRect.height = h;

	return BufRect;
}