#pragma once
#include "Entity.h";
#include "Constants.h"

class Enemy :public Entity {
public:
	//передаем так же строку карты, чтоб все время не создавалась память при вызовах функций
	Enemy(sf::Image& image, float X, float Y, int W, int H, sf::String Name, sf::String TileMapEnemy[HEIGHT_MAP]);
	sf::Vector2f GetXY() { return sf::Vector2f(x, y); }; // Возвращает позицию спрайта Enemy
	void SetStatus(sf::String St) { status = St; };
	sf::FloatRect GetRect();// Переопределили функцию, чтобы подвинуть хитбокс
	void draw(sf::RenderTarget& target);// Так как нужно много за раз нарисовать, то вынесем в отдельный метод	
private:
	// Будет вызываться внутри, так что инкапсулирую ф-ии
	sf::Sprite BossPart;//босс состоит из 2х частей: голова и пилы
	sf::Sprite healthSprite;//Спрайт для полоски HP
	sf::String status;
	sf::Vector2f SpaunTarget();// смотрим где наши спауны на карте
	sf::String TileMap[HEIGHT_MAP];// карта
};
