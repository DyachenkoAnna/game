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
    std::vector<Enemy> enemies;
    sf::Clock clock;

    //������� �����������, � ������� ����� ���������� ����� + ������ ������ � �������� ��� ����� 
    sf::Image map_image;//������ ����������� ��� �����
    sf::Image allImage;//��� �����������, ������� ������������ ������ �����
    sf::Sprite s_map;//������ ��� �����
    sf::Texture map;//��������

    int MainMenu(sf::RenderWindow& target);//меню при старте
    bool GameOver; //проверка на конец игры

};