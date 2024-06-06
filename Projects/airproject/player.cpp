#include "player.hpp"

Player::Player() {
    _name = "player 1";
    _shape = 'o';
    _points = 0;
}

Player::Player(std::string name, char shape) {
    _name = name;
    _shape = shape;
    _points = 0;
}

Player::~Player() {

}

void Player::setName(std::string name) {
    _name = name;
}

void Player::setShape(char shape) {
    _shape = shape;
}

void Player::setposition(std::pair<int, int> position) {
    _position = position;
}

std::string Player::getName() const {
    return _name;
}

char Player::getShape() const {
    return _shape;
}

std::pair<int, int>& Player::getPosition() {
    return _position;
}