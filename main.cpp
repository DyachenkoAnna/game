#include <ctime>
#include "interaction.h"

/*
Здесь вход в программу.
используем для вектора тип sf::Vector2f
*/

int main()
{
	srand(unsigned(time(0)));
	Engine* level = new Engine();//Создали объект = запусьтли игру
	level->play(0);//Вдальнейшем будет возможность ставить на паузу
	delete level;// Удалили объект (игру)
}
