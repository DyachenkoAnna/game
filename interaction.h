#pragma once
#include "Enemy.h"
#include "Player.h"
class Engine {
public:
    Engine();
    ~Engine();
    int play(int number);

private:
    Player* Hero;
    std::vector<Enemy> enemies;// ������ ������
    // ������ ����, ����� ����� ����� ���
    sf::Clock clock;// ���������� ������
    //����� �������� � �����
    //����� ���������� ����������� ���� � ����� �� ����
};