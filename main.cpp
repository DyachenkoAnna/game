//release-1.0

#include <ctime>
#include "interaction.h"

/*
����� ���� � ���������.
���������� ��� ������� ��� sf::Vector2f
*/

int main()
{
	srand(unsigned(time(0)));
	int way = 2;//��� ����������� �������� ��� ���������� ����
	while (way != 0)
	{
		Engine* level = new Engine();//������� ������ = ��������� ����
		way = level->play(way);//�������� ����
		delete level;// ������� ������ (����)
	}

	return 0;
}