#pragma once
#include "Entity.h";
#include "Constants.h"

class Enemy :public Entity {
public:
	//�������� ��� �� ������ �����, ���� ��� ����� �� ����������� ������ ��� ������� �������
	Enemy(sf::Image& image, float X, float Y, int W, int H, sf::String Name, sf::String TileMapEnemy[HEIGHT_MAP]);
	sf::Vector2f GetXY() { return sf::Vector2f(x, y); }; // ���������� ������� ������� Enemy
	void SetStatus(sf::String St) { status = St; };
	sf::FloatRect GetRect();// �������������� �������, ����� ��������� �������
	void draw(sf::RenderTarget& target);// ��� ��� ����� ����� �� ��� ����������, �� ������� � ��������� �����	
private:
	// ����� ���������� ������, ��� ��� ������������ �-��
	sf::Sprite BossPart;//���� ������� �� 2� ������: ������ � ����
	sf::Sprite healthSprite;//������ ��� ������� HP
	sf::String status;
	sf::Vector2f SpaunTarget();// ������� ��� ���� ������ �� �����
	sf::String TileMap[HEIGHT_MAP];// �����
};
