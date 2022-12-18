#pragma once
#include "Entity.h";
#include "Constants.h"

class Enemy :public Entity {
public:
	//�������� ��� �� ������ �����, ���� ��� ����� �� ����������� ������ ��� ������� �������
	Enemy(sf::Image& image, float X, float Y, int W, int H, sf::String Name, sf::String TileMapEnemy[HEIGHT_MAP]);
	int update(float time);		//����� �������, ������� ���������� � �������� ���������
	int SetAim(sf::Vector2f);	//������������� ��������� ��������
	sf::Vector2f GetXY() { return sf::Vector2f(x, y); };	//���������� ������� ������� Enemy
	void SetStatus(sf::String St) { status = St; };
	void struck(int damage);
	sf::FloatRect GetRect();	//�������������� �������, ����� ��������� �������
	void draw(sf::RenderTarget& target);	//��� ��� ����� ����� �� ��� ����������, �� ������� � ��������� �����	
	//����� ������ get � set ��� bossdamagetimer?
private:
	//����� ���������� ������, ��� ��� ������������ �������
	float BOSSdamagetimer;
	sf::Sprite BossPart;		//���� ������� �� 2� ������: ������ � ����
	sf::Sprite healthSprite;	//������ ��� ������� HP
	sf::Vector2f XYAim;			//���������� ������� ������
	sf::String status;
	int action(float);			//�������� ������
	void animation();
	void SetDirection();		//���������� ����������� �� �����������, ������ � SetAim
	int checkCollisionWithMap(float, float);
	sf::Vector2f SpaunTarget();		//������� ��� ���� ������ �� �����
	sf::String TileMap[HEIGHT_MAP];	//�����
};
