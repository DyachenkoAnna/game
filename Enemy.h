#pragma once
#include "Entity.h";
#include "Constants.h"

class Enemy :public Entity {
public:
	//Передаем так же строку карты, чтоб все время не создавалась память при вызовах функций
	Enemy(sf::Image& image, float X, float Y, int W, int H, sf::String Name, sf::String TileMapEnemy[HEIGHT_MAP]);
	int SetAim(sf::Vector2f);	//Устанавливает положение движения
	sf::Vector2f GetXY() { return sf::Vector2f(x, y); };	//Возвращает позицию спрайта Enemy
	void SetStatus(sf::String St) { status = St; };
	void struck(int damage);
	sf::FloatRect GetRect();	//Переопределили функцию, чтобы подвинуть хитбокс
	void draw(sf::RenderTarget& target);	//Так как нужно много за раз нарисовать, то вынесем в отдельный метод	

	int action(float);			//действия врагов
	void SetDirection();		//вычисление направления по координатам, взятых с SetAim
private:
	//Будет вызываться внутри, так что инкапсулирую ф-ии
	sf::Sprite BossPart;		//босс состоит из 2х частей: голова и пилы
	sf::Sprite healthSprite;	//спрайт для полоски HP

	sf::Vector2f XYAim;			//координата спрайта игрока
	sf::String status;

	int checkCollisionWithMap(float, float);
	sf::Vector2f SpaunTarget();		//смотрим где наши спауны на карте
	sf::String TileMap[HEIGHT_MAP];	//карта
};
