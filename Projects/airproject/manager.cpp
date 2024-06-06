#include <iostream>
#include <conio.h>
#include "manager.hpp"

Manager::Manager()
{
}

Manager::Manager(std::string name, std::string shape)
{
}

Manager::~Manager()
{
}

bool Manager::movePlayer()
{
    auto [y, x] = _player.getPosition();
    int m = 0;
    // while (true)
    // {
    if (_getch() == 224)
    {
        switch (m = _getch())
        {
        case UP:
            std::cout << std::endl
                      << "Up" << std::endl; // key up
            setPosition(--y, x);
            break;
        case DOWN:
            std::cout << std::endl
                      << "Down" << std::endl; // key down
            setPosition(++y, x);
            break;
        case LEFT:
            std::cout << std::endl
                      << "Left" << std::endl; // key left
            setPosition(y, --x);
            break;
        case RIGHT:
            std::cout << std::endl
                      << "Right" << std::endl; // key right
            setPosition(y, ++x);
            break;
        
        case EXIT:
            std::cout << std::endl
                      << "EXIT" << std::endl; // key right
            return false;
            break;

        default:
            break;
        }
    }

    return true;
}

void Manager::setPosition(int y, int x)
{
    if (collisionDetect(_map, std::make_pair(y, x)))
    {
        auto [oldy, oldx] = _player.getPosition();

        _map.getMap()[oldy][oldx] = ' ';
        _map.getMap()[y][x] = _player.getShape();
        _player.setposition(std::make_pair(y, x));
    }
}

void Manager::start()
{

    _player.setName("readyplayerone");
    _player.setShape('r');

    auto [height, width] = _map.getDimensions();
    int x = (rand() % (width - 2)) + 1;

    while (!collisionDetect(_map, std::make_pair(height - 2, x)))
    {
        x = (rand() % (width - 1)) + 1;
    }

    setPosition(height - 2, x);
    _map.printMap();

    while (movePlayer())
    {
        _map.printMap();
        
        // if(_getch() == 'c') break;
    }
}
