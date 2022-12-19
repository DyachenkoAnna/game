#include <ctime>
#include "interaction.h"

/*
����� ���� � ���������.
���������� ��� ������� ��� sf::Vector2f
*/

int main()
{
	srand(unsigned(time(0)));
	Engine* level = new Engine();//������� ������ = ��������� ����
	level->play(0);//����������� ����� ����������� ������� �� �����
	delete level;// ������� ������ (����)
}