#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <map>

class Map {
    public:
        Map();
        Map(std::pair<int, int> dimensions);
        ~Map();
        
        const std::pair<int, int> getDimensions();
        
        void printMap();

        std::vector<std::vector<char>>& getMap();

    private:
        void createMap();
        void addObstacles();
        void addPathways();
        bool collisionDetect(std::pair<int, int> position);
        friend bool collisionDetect(Map& m, std::pair<int, int> position);
        
        std::vector<std::vector<char>> _map;
        std::map<std::pair<int, int>, int> _paths;
        std::pair<int, int> _dimensions;
        
};


#endif