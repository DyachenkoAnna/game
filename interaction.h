#pragma once
#include "Enemy.h"//файл с врагами
#include "Player.h"//файл с игроком
#include "Bullet.h"//Файл с пулей
class Engine {
public:
    Engine();//конструктор
    ~Engine();//деструктор
    int play(int number);//метод игры

private:
    Player* Hero;//объуект игры
    std::vector<Bullet> bullets;// вектор пуль
    std::vector<Enemy> enemies;// вектор врагов
    sf::Clock clock;// аппаратный таймер, время процесса игры
    float time;// основное время, отвечает за скорость игры
    sf::Image map_image;//объект изображения для карты
    sf::Image allImage;//Все изображения, которые исполузуются поверх карты
    sf::Sprite s_map;//спрайт для карты
    sf::Sprite Health;//для здоровья
    sf::Sprite GunDamage;//для уровня заряда пушки
    sf::Texture map;//текстура карты
    bool GameOver;//тригер для окончания игры
    int MainMenu(sf::RenderWindow& target);//меню при старте
    int RestartMenu(sf::RenderWindow& target);//меню внутри игры
};
