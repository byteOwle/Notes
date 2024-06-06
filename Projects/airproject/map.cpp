#include <algorithm>
#include <iostream>
#include <time.h>
#include <queue>
#include <string>
#include <random>
#include "map.hpp"

Map::Map()
{
    srand(time(NULL));
    _dimensions = std::make_pair(15, 15);
    // _paths = std::vector(_dimensions.first, std::vector<int>(_dimensions.second, 0));

    for (int y = 0; y < _dimensions.second; ++y)
    {

        for (int x = 0; x < _dimensions.first; ++x)
        {
            _paths[std::make_pair(y, x)] = 0;
        }
    }

    createMap();
    // addPathways();
    addPathways();
    addObstacles();
}

Map::Map(std::pair<int, int> dimensions)
{
    srand(time(NULL));
    _dimensions = dimensions;
    // _paths = std::vector(_dimensions.first, std::vector<int>(_dimensions.second, 0));

    createMap();
    addPathways();
    // addPathways();
    addObstacles();
}

Map::~Map()
{
    // delete[] _paths;
}

void Map::createMap()
{
    for (int y = 0; y < _dimensions.first; ++y)
    {

        std::vector<char> row;
        for (int x = 0; x < _dimensions.second; ++x)
        {
            if (y == 0 || y == _dimensions.first - 1)
            {
                row.push_back('-');
            }
            else if (x == 0 || x == _dimensions.second - 1)
            {
                row.push_back('|');
            }
            else
            {
                row.push_back(' ');
            }
        }

        _map.push_back(row);
    }
}

void Map::addObstacles()
{
    for (int y = 1; y < _dimensions.first - 1; ++y)
    {
        int nWallsLimit = 0;
        // printMap();
        for (int x = 1; x < _dimensions.second - 1; ++x)
        {
            if (collisionDetect(std::make_pair(y, x)))
            {
                ++nWallsLimit;
            }
        }

        int nWalls = nWallsLimit > 0 ? ((rand() % nWallsLimit) + 1) : 0;
        nWalls = nWalls > 5 ? std::ceil(_dimensions.second / 2) : nWalls;

        int n = 1;
        while (n <= nWalls && (y != 0 && y != _dimensions.first - 1))
        {
            int xwall = (rand() % _dimensions.second - 2) + 1;
            if (collisionDetect(std::make_pair(y, xwall)) && _paths[std::make_pair(y, xwall)] != 1)
            {
                _map[y][xwall] = 'X';
                ++n;
            }
        }
    }
}

void Map::addPathways()
{
    int height = _dimensions.first, width = _dimensions.second;

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, -1}, {0, 1}}; // up, left, right
    std::queue<std::pair<int, int>> path;
    std::random_device rd;
    std::mt19937 g(rd());

    // Initial position
    int xpos = (rand() % (width - 2)) + 1;
    while (!collisionDetect(std::make_pair(height - 2, xpos)))
    {
        xpos = (rand() % (width - 2)) + 1;
    }

    path.push({height - 2, xpos});
    auto [y, x] = path.front();
    _paths[std::make_pair(y, x)] = 1;

    int n = 2;
    while (!path.empty())
    {
        auto [y, x] = path.front();
        path.pop();

        std::shuffle(directions.begin(), directions.end(), g);

        for (auto [dy, dx] : directions)
        {
            int ny, nx;
            ny = dy + y;
            nx = dx + x;
            if (collisionDetect(std::make_pair(ny, nx)))
            {
                _paths[std::make_pair(y, x)] = 1;
                // _map[y][x] = 'p';
                path.push({ny, nx});
                ++n;

                break;
            }
        }

        if (y == 1)
            break;
    }
}

bool Map::collisionDetect(std::pair<int, int> position)
{
    return _map[position.first][position.second] == ' ';
}

bool collisionDetect(Map& m, std::pair<int, int> position)
{
    return m.collisionDetect(position);
}

void Map::printMap()
{
    for (std::vector<char> i : _map)
    {
        for (char k : i)
        {
            std::cout << k;
        }

        std::cout << std::endl;
    }
}

std::vector<std::vector<char>>& Map::getMap()
{
    return _map;
}

const std::pair<int, int> Map::getDimensions() {
    return _dimensions;
}