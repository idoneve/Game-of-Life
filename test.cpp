#include <iostream>
#include "game_of_life.h"
using namespace std;

int main(int argc, char const *argv[])
{
    int generations = 100;
    game_of_life game("gamestarter.txt");
    
    system("clear");
    for(int i = 0; i < generations; i++)
    {
        cout << game;
        game.NextGen();

        usleep(1000000);
        system("clear");
    }

    return 0;
}
