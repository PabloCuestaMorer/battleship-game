/*****************************************************************//**
 * \file   Player.h
 * \brief
 *
 * \author pablo
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <string>
#include <iostream>
#include "Ship.h"
#include "Board.h"

using namespace std;
class Player
{
private:
	string name;
	Ship ships[5];
	Board shipsBoard;
	Board shotsBoard;
public:
	Player();
	string getName();
	void setName(string name);
	Board getShipsBoard();
	void setShipsBoard(Board b);
	Board getShotsBoard();
	void setShotsBoard(Board b);
};

