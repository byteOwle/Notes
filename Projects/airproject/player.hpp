#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    public:
        Player();
        Player(std::string name, char shape);
        ~Player();

        void setName(std::string name);
        void setShape(char shape);
        void setposition(std::pair<int, int> position);

        std::string getName() const;
        char getShape() const;
        std::pair<int, int>& getPosition();

    private:
        std::string _name;
        char _shape;
        int _points;
        std::pair<int, int> _position;
};

#endif