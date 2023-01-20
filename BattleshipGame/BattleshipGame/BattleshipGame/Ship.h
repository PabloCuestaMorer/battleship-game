/*****************************************************************//**
 * \file   Ship.h
 * \brief
 *
 * \author pablo
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <iostream>
#include <string>

using namespace std;
class Ship
{
protected:
	string name;
	int size;
	char symbol;
	char orientation;
	int x, y;
	bool isSunk;
public:
	Ship();
	string getName();
	void setName(string name);
	int getSize();
	void setSize(int size);
	char getSymbol();
	void setSymbol(char symbol);
	char getOrientation();
	void setOrientation(char orientation);
	char getX();
	void setX();
	char getY();
	void setY();
	bool getIsSunk();
	void setIsSunk(bool sunk);

	friend istream& operator>>(istream& input, Ship& ship);
};

