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
#include <vector>
#include <fstream>
#include <random>	


#include "Ship.h"
#include "Carrier.h"
#include "Battleship.h"
#include "Submarine.h"
#include "PatrolBoat.h"
#include "Vessel.h"
#include "Board.h"


using namespace std;
class Player
{
private:
	string name;
	vector<Ship*> ships;
	int const ROWS = 10;
	int const COLS = 10;
	char board[10][10];
	// private methods
	bool canPlaceShip(int row, int col, int size, bool isHorizontal);
	void placeShip(int row, int col, int size, bool isHorizontal);

public:
	Player();
	// Getters/Setters
	string getName();
	void setName(string name);
	// methods
	void placeShips();
	void placeShipsRandomly();
	bool shoot(int x, int y);
	bool allSunk();
	void printBoard();
	void printShootingBoard();
	void savePlayer(string filename);
	void loadPlayer(string filename);
	//Overloading
	Player& operator=(const Player& other);
};

