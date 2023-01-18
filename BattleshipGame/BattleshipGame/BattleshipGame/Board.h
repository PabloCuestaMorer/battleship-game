/*****************************************************************//**
 * \file   Board.h
 * \brief  
 * 
 * \author pablo
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <iostream>

using namespace std;
class Board
{
private:
    char board[11][11];
    void fillBoard();

public:
    Board();
    void displayBoard();
};

