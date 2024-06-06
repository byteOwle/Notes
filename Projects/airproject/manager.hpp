#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include "map.hpp"
#include "player.hpp"

enum Movements {
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    EXIT = 27
};

class Manager {
    public:
        Manager();
        Manager(std::string name, std::string shape);
        ~Manager();
        
        void start();
        void setPosition(int y, int x);
        bool movePlayer();

    private:
        Map _map;
        Player _player;

};

#endif