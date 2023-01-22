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
#include <iomanip> // to change the color of the text output to the console.



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
	bool canPlaceShip(Ship* ship);
	void placeShip(Ship* ship);

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
	void printShipsBoard();
	void printShootingBoard();
	void savePlayer(string filename);
	void loadPlayer(string filename);
	//Overloading
	Player& operator=(const Player& other);
};

