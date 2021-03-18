#pragma once
#include <string>
#include <iostream>
#include "Direction.hpp"

namespace ariel
{
    class Board
    {
    private:
        // vector
        // int maxH
        // int maxV
    public:
        Board(){}

        void post(unsigned int row, unsigned int col, Direction direct, std::string message);

        std::string read(unsigned int row, unsigned int col, Direction direct, unsigned int length);

        void show();

        ~Board(){}
    };
}
