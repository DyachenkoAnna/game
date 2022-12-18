#include "interaction.h"
#include "map.h"

Engine::Engine()
{
	//загрузили изображения
	clock.restart(); //перезагружает время
	//Создаем объект героя
	Hero = new Player(allImage, 500, 500, 70, 80, "hero");
}

Engine::~Engine()
{
	delete Hero;
	enemies.clear();
	//очищаем память, за собой нужно убирать
}

int Engine::play(int number)
{
	float timerspaun = 0;//таймер для появления врагов
	float gunTimer = 0;//для контроля выстрелов гг
	float spaunlvl = 5000;//время нужное спауна
	float timerLVLup = 0;//повышаем уровень, со временем

	//Нужно реализовать вывод окна с картой и игроком
}