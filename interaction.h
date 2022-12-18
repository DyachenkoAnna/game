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

    //создаем изображения, в которые будем подгружать файлы + созаем спрайт и текстуру для карты 
    sf::Image map_image;//объект изображения для карты
    sf::Image allImage;//Все изображения, которые исполузуются поверх карты
    sf::Sprite s_map;//спрайт для карты
    sf::Texture map;//текстуры

   
};