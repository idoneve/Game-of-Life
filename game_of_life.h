#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

class game_of_life
{
    // Insert Data Member Variables here
    int width_;
    int generations_ = 0;
    std::string current_;

public:
    game_of_life() = delete;
    game_of_life(std::string filename);
    void NextGen();
    void NextNGen(int);
    int GetGenerations();
    friend std::ostream &operator<<(std::ostream &os, const game_of_life &game);
};
std::ostream &operator<<(std::ostream &os, const game_of_life &game);
#endif