#include <iostream>
#include "map.h"
#include "Enemy.h"
#include <stdlib.h>
#include <SFML/Graphics.hpp>

//Файл с главной функцией

int main()
{	
	sf::Image img;
	sf::Sprite s_bot;
	sf::Texture bot;
	img.loadFromFile("images/robots.png");
	bot.loadFromImage(img);
	s_bot.setTexture(bot);
	Enemy* anotherEnemy = new Enemy(img, 200, 200, 45, 65, "flybot", TileMapMy);
	Enemy* anotherEnemy1 = new Enemy(img, 200, 200, 45, 65, "flybot", TileMapMy);
	Enemy* BossEnemy = new Enemy(img, 200, 200, 120, 90, "BOSSbot", TileMapMy);

	//Далее идет мой отладочный код. Он выводит карту на экран.
	//Пусть пока что будет, потом сделаем этот файл красивым
	sf::Image map_image;
	sf::Sprite s_map;
	sf::Texture map;
	map_image.loadFromFile("images/map.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);
	//sf::RenderWindow window(sf::VideoMode(1280, 800), "Game", sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(1280, 800), "Game");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMapMy[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
				else if (TileMapMy[i][j] == '0')  s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
				else if (TileMapMy[i][j] == 'b') s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
				else if (TileMapMy[i][j] == 'p') s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
				else if (TileMapMy[i][j] == 'h') s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));
				else s_map.setTextureRect(sf::IntRect(160, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
				anotherEnemy->draw(window);
				anotherEnemy1->draw(window);
				BossEnemy->draw(window);

				anotherEnemy->moveTimer+=0.05;
				anotherEnemy->action(0.1);
				anotherEnemy->animation();
				BossEnemy->action(0.1);
			}
		window.display();
	}
	return 0;
}
