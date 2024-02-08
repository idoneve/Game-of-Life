#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "game_of_life.h"

using namespace std;

game_of_life::game_of_life(string filename)
{
    // Create a file input using the user's input
    fstream file_in(filename);
    if (!file_in)
    {
        // File not found
        throw(runtime_error("The file: \"" + filename + "\" could not found"));
    }
    if (!(file_in >> this->width_))
    {
        // Invalid file format
        throw(runtime_error("Invalid file format\nfile should have number of units in first line followed by starting cell positions using - as dead cells and * as live cells"));
    }
    // Pre Load Current with the "dead_cell" character as a square table
    this->current_ = string(this->width_ * this->width_, '-');
    string line;
    getline(file_in, line); // Skipping the end of the first line to get to the data
    // For all rows in the file
    for (int row = 0; row < this->width_; ++row)
    {
        getline(file_in, line);
        // For all Columns in the row
        for (int col = 0; col < this->width_; ++col)
        {
            if (line[col] == '*')
            {
                // Only updates the character if It needs to be
                this->current_[col + (row * this->width_)] = '*';
            }
        }
    }
}

void game_of_life::NextGen()
{
    string to = this->current_;
    for (int row = 0; row < this->width_; row++)
    {
        for (int col = 0; col < this->width_; col++)
        {
            int neighbors = 0;
            int curr_cell = col + (row * this->width_);

            // checks each adjacent cell of the current cell and counts how many are alive
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0) // skips over itself so it doesn't count it as a neighbor
                    {
                        continue;
                    }

                    // iterates through rows and columns by adding i and j to cooresponding row or column plus width
                    // to get rid of any negative moldulo calctulations then finds remainder to account for rap-around
                    if (this->current_[(col + this->width_ + i) % this->width_ + (((row + this->width_ + j) % this->width_) * this->width_)] == '*')
                    {
                        neighbors++;
                    }
                }
            }

            // uses the number of alive adjacent cells to figure out if the currenct cell should be alive or dead
            // in the next generation using the rules of the game of life
            if (neighbors < 2) // if less than 2 alive neighbors current cell should be dead
            {
                to[curr_cell] = '-';
            }
            else if (neighbors == 2) // if 2 alive neighbors then current cell stays the same either alive or dead
            {
                to[curr_cell] = to[curr_cell];
            }
            else if (neighbors == 3) // if 3 alive neighbors then current cell either stays alive or is revived
            {
                to[curr_cell] = '*';
            }
            else if (neighbors > 3) // if more than 3 alive neighbors then current cell either stays dead or is killed
            {
                to[curr_cell] = '-';
            }
        }
    }

    // update current to next generation and increase generation count
    this->current_ = to;
    this->generations_++;
}

void game_of_life::NextNGen(int n) // runs NextGen n times
{
    for (int i = 0; i < n; i++) // for loop does not run if user enter a number less than 1
    {
        game_of_life::NextGen();
    }
}

int game_of_life::GetGenerations()
{
    return this->generations_; // gets current count of generations
}

ostream &operator<<(ostream &os, const game_of_life &game)
{
    os << "Generation: " << game.generations_ << "\n";
    for (int row = 0; row < game.width_; row++)
    {
        for (int col = 0; col < game.width_; col++)
        {
            char curr = game.current_[col + (row * game.width_)]; // adds "width_" characters into os, cooresponding to a row

            if (curr == '*')
            {
                os << "\033[1;47m  \033[0m"; // change 47 to change color
            }
            else 
            {
                os << "\033[1;40m  \033[0m";
            }
        }

        os << "\n"; // adds a newline after each line of characters is added
    }

    return os;
}
