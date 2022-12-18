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
    std::vector<Enemy> enemies;// вектор врагов
    // вектор пули, когда будет готов код
    sf::Clock clock;// аппаратный таймер
    //далее текстуры и карта
    //также необходимо реализовать меню и выход из игры
};