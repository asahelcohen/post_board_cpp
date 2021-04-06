#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Direction.hpp"

namespace ariel
{
    class Board
    {
    private:
	    std::vector<std::vector<char>> board;
        unsigned int maxR;
        unsigned int maxC;
    public:
        Board();

        void post(unsigned int row, unsigned int col, Direction direct, std::string message);

        std::string read(unsigned int row, unsigned int col, Direction direct, unsigned int length);

        void show();
        
        ~Board(){};
    };
}
