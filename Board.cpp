#include "Board.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

namespace ariel
{
    Board::Board()
    {
        board = {
			{'_','_'},
			{'_','_'}
			};
		maxC = 1;
        maxR = 1;
    }

	void addColumns(vector<vector<char>> &board, unsigned int c, unsigned int r){
		for(unsigned int i = 0; i < r + 1; i++){
				for(unsigned int j = 0; j < c - 1; j++){
					board.at(i).push_back('_');
				}
			}
	}

	void addRows(vector<vector<char>> &board, unsigned int c, unsigned int r){
		std::vector<char> temp(c, '_');	
		for(unsigned int i = 0; i < r; i++)
			board.emplace_back(temp);
	}

	void Board::post(unsigned int row, unsigned int column, Direction direction, std::string message)
	{
		//check if size is big enough
		unsigned int r = maxR;
		unsigned int c = maxC;
		if (direction == Direction::Horizontal)
		{
			if (row >= maxR)
				r = row + 1;
			if ((column + message.size()) >= maxC)
				c = column + message.size();
				
		}
		else
		{
			if (column >= maxC)
				c = column;
			if ((row + message.size()) >= maxR)
				r = row + message.size() +1;
		}

		if (r > maxR || c > maxC)
		{
			maxC = board.at(0).size() - 1;
			maxR = board.size() - 1;

			if(c >= maxC){
				addColumns(board, c - maxC, maxR);
			}

			if(r >= maxR)
			{	
				addRows(board, c, r- maxR);
			}
			maxR = r;
			maxC = c;		
		}

		//post after checking size
		if (direction == Direction::Horizontal)
		{
			for (unsigned int i = column; i < column + message.size(); i++)
			{
				board.at(row).at(i) = message.at(i - column);
			}
		}
		else
		{
			for (unsigned int i = row; i < row + message.size(); i++)
			{
				board.at(i).at(column) = message.at(i - row);
			}
		}

	}

	std::string Board::read(unsigned int row, unsigned int column, Direction direction, unsigned int length)
	{
		string mess;
		if (row > maxR || column > maxC){
			for(int i = 0; i < length; i++)
				mess += "_";
		}
		else
		{
			if (direction == Direction::Horizontal)
			{
				unsigned int len = min(length+column, maxC);
				for (unsigned int i = column; i < len; i++)
				{
					mess += board.at(row).at(i);
				}
				if(length+column > maxC){
					for(unsigned int i = 0; i < length+column - maxC; i++){
						mess += '_';
					}
				}
			}
			else
			{
				unsigned int len = min(length+row, maxR);
				for (unsigned int i = row; i < len; i++)
				{
					mess += board.at(i).at(column);
				}
				if(length+row > maxR){
					for(unsigned int i = 0; i < length+row - maxR; i++){
						mess += '_';
					}
				}
			}
		}
		return mess;
	}

	void Board::show()
	{
		for (unsigned int i = 0; i < board.size(); i++)
		{
			for (unsigned int j = 0; j < board[i].size(); j++)
			{
				cout << board.at(i).at(j) << " ";
			}
			cout << endl;
		}
	}
}
 