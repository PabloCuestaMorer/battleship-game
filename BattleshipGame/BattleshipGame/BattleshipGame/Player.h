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
#include "Carrier.h"
#include "Battleship.h"
#include "Submarine.h"
#include "PatrolBoat.h"
#include "Vessel.h"
#include "Board.h"
#include <vector>

using namespace std;
class Player
{
private:
	string name;
	vector<Ship*> ships;
	int const ROWS = 10;
	int const COLS = 10;
	char board[10][10];
	bool canPlaceShip(int row, int col, int size, bool isHorizontal);
	void placeShip(int row, int col, int size, bool isHorizontal);
public:
	Player();
	string getName();
	void setName(string name);

	void placeShips();
	bool shoot(int x, int y);
	bool allSunk();
	void printBoard();
};

