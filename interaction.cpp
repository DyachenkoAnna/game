#include "interaction.h"
#include "map.h"

Engine::Engine()
{
    //загрузили изображения

    clock.restart(); //перезагружает время

    //карта
    map_image.loadFromFile("images/map.png");//загружаем файл для карты
    map.loadFromImage(map_image);//заряжаем текстуру картинкой
    s_map.setTexture(map);//заливаем текстуру спрайтом

    //это для отрисовки танка
    allImage.loadFromFile("images/robots.png");

    //Создаем объект героя
    Hero = new Player(allImage, 500, 500, 70, 80, "hero");
    GameOver = false;
}

Engine::~Engine()
{
    delete Hero;
    enemies.clear();
    //очищаем память, за собой нужно убирать
}

int Engine::play(int number)
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Game", sf::Style::Fullscreen);
    //окно сформировали, сделали на полный экран
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Cross))
        window.setMouseCursor(cursor);
    //устанавливаем курсор-крестик (типа прицел)
    if (number != 1 && !MainMenu(window))
    {
        return 0;
    }
    float timerspaun = 0;//таймер для появления врагов
    float gunTimer = 0;//для контроля выстрелов гг
    float spaunlvl = 5000;//время нужное спауна
    float timerLVLup = 0;//повышаем уровень, со временем
    

    //запускаем меню
    if (number != 1 && !MainMenu(window))
    {
        return 0;
    }


    //Нужно реализовать вывод окна с картой и игроком
    while (window.isOpen() && !GameOver)
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

                Hero->draw(window);//рисуется герой-танк
            }
        window.display();
    }
    return 0;

}





int Engine::MainMenu(sf::RenderWindow& target)
{
    {
        sf::Texture menuTexturePlay, menuTextureQuit, menuBackground;
        menuTexturePlay.loadFromFile("images/Play.png");
        menuTextureQuit.loadFromFile("images/Quit.png");
        menuBackground.loadFromFile("images/jogaGame.png");
        sf::Sprite menuPlay(menuTexturePlay), menuQuit(menuTextureQuit), menuBg(menuBackground);
        bool isMenu = 1;
        int menuNum = 0;
        menuPlay.setPosition(100, 200);
        menuQuit.setPosition(100, 500);
        menuBg.setPosition(0, 0); //красивый background 1280х800px
        //////////////////////////////МЕНЮ///////////////////

        while (isMenu)
        {
            menuPlay.setColor(sf::Color::White);
            menuQuit.setColor(sf::Color::White);
            menuNum = 0;
            target.clear();

            if (sf::IntRect(100, 200, 310, 110).contains(sf::Mouse::getPosition())) { menuPlay.setColor(sf::Color::Blue); menuNum = 1; }
            if (sf::IntRect(100, 500, 310, 110).contains(sf::Mouse::getPosition())) { menuQuit.setColor(sf::Color::Blue); menuNum = 2; }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (menuNum == 1)
                {
                    isMenu = false;//если нажали первую кнопку, то выходим из меню
                    return 1;
                }
                if (menuNum == 2)
                {
                    isMenu = false;
                    return 0;
                }

            }
            //target = window
            target.draw(menuBg);
            target.draw(menuPlay);
            target.draw(menuQuit);
            target.display();
        }
        return 0;
    }
}
