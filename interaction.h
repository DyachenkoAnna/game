#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
class Engine {
public:
    Engine();
    ~Engine();
    int play(int number);

private:
    Player* Hero;
    std::vector<Bullet> bullets;// вектор пуль
    std::vector<Enemy> enemies;// вектор врагов
    sf::Clock clock;// аппаратный таймер
    float time;// основное время, отвечает за скорость игры
    sf::Image map_image;//объект изображения для карты
    sf::Image allImage;//Все изображения, которые исполузуются поверх карты
    sf::Sprite s_map;//спрайт для карты
    sf::Texture map;
    bool GameOver;//тригер для окончания игры
    int MainMenu(sf::RenderWindow& target);//меню при старте
    int RestartMenu(sf::RenderWindow& target);//меню внутри игры
};